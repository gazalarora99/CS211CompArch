#include <stdio.h>
#include <stdlib.h>
char **matrix;

char** allocate_matrix(int, int);
void free_matrix(char**, int);
void free_matrix(char **matrix, int r){
  for(int i = 0; i <r; i++){
    free(matrix[i]);
  }
  free(matrix);
}
char** allocate_matrix(int rows, int cols){

  char** ret_val = malloc(rows * sizeof(char*));
  for(int i = 0; i< rows; i++){
    ret_val[i] = malloc(cols * sizeof(char));
  }
  return ret_val;
}

int main(int argc, char** argv)
{

  if(argc!=2){
    printf("insufficient arguments");
    exit(0);
  }

  FILE* fp = fopen(argv[1],"r");
  if(fp==NULL){
    printf("error");
    exit(0);
  }

  matrix = allocate_matrix(16,16);
  for(int i=0;i<16;i++)
    {
      for(int j=0;j<16;j++)
	{
          fscanf(fp, "%c\t",&matrix[i][j]);
        }
    }



  char arr[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  int arr2[16];
  for (int m = 0; m <16; m++){
    arr2[m] = 0;                                                                                                                                                                                                                             \

  }

  for(int i=0;i<16;i++)
    {
      for(int j=0;j<16;j++)
        {
          if(matrix[i][j]=='-'){
            for(int l = 0; l < 16; l++){
              for(int k = 0; k<16; k++){
                if(matrix[i][k]==arr[l]){
                  arr2[l]=1;
                }
                if(matrix[k][j]==arr[l]){
                  arr2[l]=1;
                }
              }
	      int x = (i/4)*4;
	      int y = (j/4)*4;
	      for(int m = 0; m < 4; m++){
		for(int n = 0; n < 4; n++){
		  if(matrix[m+x][n+y]==arr[l]){
		    arr2[l]=1;
		  }
		}
	      }
              //              printf("printing arr2 for matrix [%d][%d]: %d\n",i,j,arr2[l]);                                                                                                                                                  
              if(arr2[l]==0){
                matrix[i][j]=arr[l];
                arr2[l]=1;
              }

            }
            for(int m = 0; m <16; m++){                                                                                                                                                                                                      \

              arr2[m] = 0;                                                                                                                                                                                                                   \

            }
          }
        }
    }

  int rowSum = 0;
  int colSum = 0;

  int gridSum = 0;

  for(int i=0;i<16;i++)
    {
      for(int j=0;j<16;j++)
        {

	  for(int k = 0; k<16; k++){
	    if(matrix[i][k]=='0')      rowSum+=0;
	    else if(matrix[i][k]=='1') rowSum+=1;
	    else if(matrix[i][k]=='2') rowSum+=2;
	    else if(matrix[i][k]=='3') rowSum+=3;
	    else if(matrix[i][k]=='4') rowSum+=4;
	    else if(matrix[i][k]=='5') rowSum+=5;
	    else if(matrix[i][k]=='6') rowSum+=6;
	    else if(matrix[i][k]=='7') rowSum+=7;
	    else if(matrix[i][k]=='8') rowSum+=8;
	    else if(matrix[i][k]=='9') rowSum+=9;
	    else if(matrix[i][k]=='A') rowSum+=10;
	    else if(matrix[i][k]=='B') rowSum+=11;
	    else if(matrix[i][k]=='C') rowSum+=12;
	    else if(matrix[i][k]=='D') rowSum+=13;
	    else if(matrix[i][k]=='E') rowSum+=14;
	    else if(matrix[i][k]=='F') rowSum+=15;
	  }
	  for(int k = 0; k<16; k++){
	    if(matrix[k][j]=='0')      colSum+=0;
	    else if(matrix[k][j]=='1') colSum+=1;
	    else if(matrix[k][j]=='2') colSum+=2;
	    else if(matrix[k][j]=='3') colSum+=3;
	    else if(matrix[k][j]=='4') colSum+=4;
	    else if(matrix[k][j]=='5') colSum+=5;
	    else if(matrix[k][j]=='6') colSum+=6;
	    else if(matrix[k][j]=='7') colSum+=7;
	    else if(matrix[k][j]=='8') colSum+=8;
	    else if(matrix[k][j]=='9') colSum+=9;
	    else if(matrix[k][j]=='A') colSum+=10;
	    else if(matrix[k][j]=='B') colSum+=11;
	    else if(matrix[k][j]=='C') colSum+=12;
	    else if(matrix[k][j]=='D') colSum+=13;
	    else if(matrix[k][j]=='E') colSum+=14;
	    else if(matrix[k][j]=='F') colSum+=15;
	  }
	  int x = (i/4)*4;
	  int y = (j/4)*4;
	  for(int m = 0; m < 4; m++){
	    for(int n = 0; n < 4; n++){
	      if(matrix[m+x][n+y]=='0')       gridSum+=0;
	      else if (matrix[m+x][n+y]=='1') gridSum+=1;
	      else if (matrix[m+x][n+y]=='2') gridSum+=2;
	      else if (matrix[m+x][n+y]=='3') gridSum+=3;
	      else if (matrix[m+x][n+y]=='4') gridSum+=4;
	      else if (matrix[m+x][n+y]=='5') gridSum+=5;
	      else if (matrix[m+x][n+y]=='6') gridSum+=6;
	      else if (matrix[m+x][n+y]=='7') gridSum+=7;
	      else if (matrix[m+x][n+y]=='8') gridSum+=8;
	      else if (matrix[m+x][n+y]=='9') gridSum+=9;
	      else if (matrix[m+x][n+y]=='A') gridSum+=10;
	      else if (matrix[m+x][n+y]=='B') gridSum+=11;
	      else if (matrix[m+x][n+y]=='C') gridSum+=12;
	      else if (matrix[m+x][n+y]=='D') gridSum+=13;
	      else if (matrix[m+x][n+y]=='E') gridSum+=14;
	      else if (matrix[m+x][n+y]=='F') gridSum+=15;
	    }
	  }
	  if(rowSum!=120 || colSum!=120 || gridSum!=120){
	    // if(rowSum!=120 || colSum!=120 ){                                                                                                                                                                                          
	    printf("no-solution");
	    fclose(fp);
	    free_matrix(matrix,16);
	    return 0;
	  }


	  rowSum=0;
	  colSum=0;
	  gridSum=0;

	  //            for(int m = 0; m <16; m++){                                                                                                                                                                                      \
                                                                                                                                                                                                                                              

        }
    }



  // printf("\n");                                                                                                                                                                                                                            
  //  printf("solution %d\n", isValid(matrix));                                                                                                                                                                                               
  for(int i=0;i<16;i++)
    {
      for(int j=0;j<16;j++)
        {
          printf("%c\t",matrix[i][j]);

        }
      printf("\n");
    }

  // printf("solution %d\n", isValid(matrix));                                                                                                                                                                                                

  fclose(fp);
  free_matrix(matrix,16);
  return 0;
}



