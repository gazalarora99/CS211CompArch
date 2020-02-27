#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>


unsigned long int counter = 0, write = 0, read =  0, hit = 0, miss = 0,preread = 0,prehit = 0,premiss = 0,prewrite=0;

struct CacheBlock{
  int valid;
  size_t tag;
  unsigned long int time;
  unsigned long int lru;
};

struct CacheBlock **cache;
struct CacheBlock **precache;
int power2(int n);
int get_SI(size_t address,int blockbits,int setbits);
void allocate_matrix(int rows,int cols);
void free_matrix(struct CacheBlock **cache1, int r);
size_t get_tag(size_t address,int blockbits,int setbits);
void setValidBitsToZero(struct CacheBlock **cache1, int setsize, int assoc);
int check_hit(struct CacheBlock **cache1,size_t tagadd,int si,int blocks);
void apply_fifo(struct CacheBlock **cache1, size_t tagadd, int blocks, int si);
void apply_lru(struct CacheBlock **cache1, size_t tagadd, int blocks, int si);
int blocks_full(struct CacheBlock **cache1,int blocks, int si);
void write_to_cache(struct CacheBlock **cache1, size_t tagadd, char poli, int blocks, int si);
void apply_fifo(struct CacheBlock **cache1, size_t tagadd, int blocks, int si);

void setValidBitsToZero(struct CacheBlock **cache1, int setsize, int blocks){
  for (int i = 0; i < setsize; i++){
    //       struct CacheBlock **ptr = &cache[i];
    for (int j = 0; j < blocks; j++){
      // struct CacheBlock **ptr = &cache[i][j];
      cache1[i][j].valid = 0;
      cache1[i][j].time = 0;
      cache1[i][j].lru = 0;
    }
  }
  }


void apply_lru(struct CacheBlock **cache1, size_t tagadd, int blocks, int si){
  unsigned long int lt = cache1[si][0].lru;
  int lt_pos = 0;
  for (int i = 0; i < blocks; i++){
    if(lt>cache1[si][i].lru){
      lt = cache1[si][i].lru; //least time
      lt_pos = i; //least index
    }
  }
  cache1[si][lt_pos].tag = tagadd;                                                                                 
  cache1[si][lt_pos].valid = 1;
  cache1[si][lt_pos].time = 1;
  cache1[si][lt_pos].lru = counter;

}


void apply_fifo(struct CacheBlock **cache1, size_t tagadd, int blocks, int si){
  
  for(int i = 0; i < blocks-1; i++){ //move all elements to one lower index
    cache1[si][i].tag = cache1[si][i+1].tag;
    cache1[si][i].time = cache1[si][i+1].time;
    cache1[si][i].lru = cache1[si][i+1].lru;
    cache1[si][i].valid = cache1[si][i+1].valid;
  }
  cache1[si][blocks-1].tag = tagadd;//inserted at last position
  cache1[si][blocks-1].valid = 1;
  cache1[si][blocks-1].time = 1;
  cache1[si][blocks-1].lru = counter;
}

int check_hit(struct CacheBlock **cache1,size_t tagadd, int si,int blocks){
  int result = 0;
  for (int i = 0; i < blocks; i++){
    if(cache1[si][i].tag == tagadd){
      result = 1;
      cache1[si][i].time++;
      cache1[si][i].lru = counter;
      break; //break as soon as it hits
    }

  }
  return result;
}

int blocks_full(struct CacheBlock **cache1,int blocks, int si){
  int result = -1;
  for(int i = 0; i < blocks; i++){
    if(cache1[si][i].valid==0){
      result = i;
      break; //finds first empty block and breaks
    }
  }
  return result;
}

void write_to_cache(struct CacheBlock **cache1, size_t tagadd, char poli, int blocks, int si){
  int empty_spot = blocks_full(cache1,blocks,si);
  if(empty_spot != -1){
    cache1[si][empty_spot].tag = tagadd;
    cache1[si][empty_spot].valid = 1; 
    cache1[si][empty_spot].lru = counter;
    cache1[si][empty_spot].time++;
  }
  else if (empty_spot == -1){
    if(poli == 'f') {apply_fifo(cache1,tagadd,blocks,si);}
    else if (poli == 'l') {apply_lru(cache1,tagadd,blocks,si);}

  }
}


int get_SI(size_t address,int blockbits,int setbits){

  int mask = (1<<setbits)-1;
  int setindex = (address>>blockbits)&mask;

  return setindex;


}

size_t get_tag(size_t address,int blockbits,int setbits){

  
  size_t tag_address = address>>(blockbits+setbits);

  return tag_address;


}

void  allocate_matrix(int rows,int cols){

 cache = malloc(rows * sizeof(struct CacheBlock*));
  for( int i = 0; i < rows; i++){
    cache[i] = malloc(cols * sizeof(struct CacheBlock));
  }

  precache = malloc(rows * sizeof(struct CacheBlock*));
  for( int i = 0; i < rows; i++){
    precache[i] = malloc(cols * sizeof(struct CacheBlock));
  }

 
  
}

void free_matrix(struct CacheBlock **cache1,int r){
  for(int i = 0; i < r; i++){
    free(cache1[i]);
  }
  free(cache1);
}


int power2(int n){
  if (n==0) return 0;
  if(ceil(log2(n))==floor(log2(n))) return 1;
  else return 0;

}



int main(int argc, char** argv){
  if(argc!=7){
    printf("insufficient arguments");
    exit(0);
  }

  //input arguments and assign variables
  int cachesize  = atoi(argv[1]);
  if(power2(cachesize)==0){printf("error");
    return 0;}
  int blocksize = atoi(argv[2]);
  if(power2(blocksize)==0){printf("error");
    return 0;}
  int prefetchsize = atoi(argv[5]);
  char policy;
  int assoc;
  int setsize;
  if(argv[3][0]=='f'){
    policy = 'f';
  }
  else if(argv[3][0]=='l'){
    policy = 'l';
  }
    FILE* fp;
    fp = fopen(argv[6],"r");
    if(fp==NULL){
      printf("error");
      return 0;
    }
    //setting associativity as 1, full, or n
  if(argv[4][0]=='d'){
    assoc = 1;
    setsize = cachesize/blocksize;
  }
  else if(argv[4][5]!=':'){
    setsize = 1;
    assoc = cachesize/blocksize;
  }
  else
  {
    sscanf(argv[4],"assoc:%d",&assoc);
    if(power2(assoc)==0){printf("error");
      return 0;}
    setsize = cachesize/blocksize/assoc;
  }
  int sb = log2(setsize);
  int bob = log2(blocksize);
  // printf("%d + %d  + %c + %d + %d + %d + %d + %d + %d\n ", cachesize, blocksize, policy, assoc, prefetchsize, setsize, sb, bob, tagbits);

  allocate_matrix(setsize,assoc);
   setValidBitsToZero(cache,setsize,assoc);
   setValidBitsToZero(precache,setsize,assoc);
  size_t add;
  char rw;
  

  while(!feof(fp)){

    fscanf(fp,"%c %zx\n",&rw, &add);
    if(rw=='#'){ break; }
    counter++;    //    printf("%c %zx\n",rw,add);
   int si = get_SI(add,bob,sb);
   size_t tagof = get_tag(add,bob,sb);

   // printf("%zx %d \n",tagof,si);
  int hit_or_miss =  check_hit(cache,tagof,si,assoc);
  if(hit_or_miss==1){
    hit++;
    if(rw=='W'){ write++; }
  }
  else if (hit_or_miss==0){
    miss++;
    if(rw=='W'){
      write++;
      read++;
    }
    else if (rw=='R'){
      read++;
    }
    write_to_cache(cache,tagof,policy,assoc,si);
  }
  //prefetch cache
  int pre_hit_or_miss = check_hit(precache,tagof,si,assoc);
  if(pre_hit_or_miss==1){
    prehit++;
    if(rw=='W'){ prewrite++; }
  }
  else if (pre_hit_or_miss==0){
    premiss++;
    if(rw=='W'){
      prewrite++;
      preread++;
    }
    else if (rw=='R'){
      preread++;
    }
    write_to_cache(precache,tagof,policy,assoc,si);
    size_t prefetch_address = add;
    for(int i = 0; i < prefetchsize; i++){
      prefetch_address = prefetch_address + blocksize;
      counter++;
    int p_si = get_SI(prefetch_address,bob,sb);
      size_t pretag = get_tag(prefetch_address,bob,sb);
      if(check_hit(precache,pretag,p_si,assoc)==0){
	preread++;
	write_to_cache(precache,pretag,policy,assoc,p_si);
      }
    }
  }


  }//end of while loop
  //  printf("counter %d \n",counter);

  // printf("misses d \n hits %d \n reads %d \n writes %d \n", miss,hit,read,write);
  printf("no-prefetch\n");
  printf("Memory reads: %lu\n", read);
  printf("Memory writes: %lu\n", write);
  printf("Cache hits: %lu\n", hit);
  printf("Cache misses: %lu\n", miss);
  printf("with-prefetch\n");
  printf("Memory reads: %lu\n", preread);
  printf("Memory writes: %lu\n", prewrite);
  printf("Cache hits: %lu\n", prehit);
  printf("Cache misses: %lu\n", premiss);
 free_matrix(cache, setsize);
 free_matrix(precache,setsize);
 return 0;
}
