#include<stdio.h>
#include<stdlib.h>

double** allocate_matrix(int, int);
void free_matrix(double**, int);
void print_matrix(int, int, double**);
double** multiply_matrices(double**, int, int, double**, int, int);
double** invert_matrix(double**, int);

double** invert_matrix(double **X, int n){
  double **result;
  result = allocate_matrix(n,n);
  for(int i = 0 ; i < n; i++){
    for(int j = 0; j < n; j++){
      if(i!=j){ result[i][j] = 0;}
      else result[i][j] = 1 ;
    }
  }
  double divisor1, divisor2;
  for(int k = 0; k<n ; k++){
    for(int l = k; l < n; l++){
      if(k==l && X[l][k] != 1){
	if(X[l][k] != 0){
	  divisor1 = X[l][k];
	  for(int m = 0; m < n; m++){
	    X[l][m] = X[l][m]/divisor1;
	    result[l][m] = result[l][m]/divisor1;
	  }
	}
      }
      else if(k!=l && X[l][k]!=0){
	divisor2 = X[l][k];
	for(int m = 0; m < n; m++){
	  X[l][m] = X[l][m]- (divisor2*X[k][m]);
			      result[l][m] = result[l][m] - (divisor2*result[k][m]);
	}
      }
    }
  }

  for(int k = n-1; k> -1; k--){
    for(int l = k; l >-1; l--){
      if(k==l && X[l][k]!=1){
	divisor1 = X[l][k];
	X[l][k] = X[l][k] / divisor1;
	result[l][k] = result[l][k]/divisor1;
      }
      else if (l!=k && X[l][k] != 0){
	divisor1 = X[l][k];
	for(int m = 0; m < n; m++){
          X[l][m] = X[l][m] - (X[k][m])*divisor1;
	  result[l][m] = result[l][m] - (result[k][m])*divisor1;
        }
      }
    }
  }
  return result;
}

double** multiply_matrices(double **X1, int r1, int c1, double **X2, int r2, int c2){
  if(c1!=r2){
    return NULL;
 }
  else{
    double **result;
    result = allocate_matrix(r1,c2);
    for(int i = 0 ; i < r1; i++){
      for(int j = 0; j < c2; j++){
	result[i][j] = 0;

      }
    }
    
    for(int i = 0 ; i < r1; i++){
      for(int j = 0; j < c2; j++){
	for(int m = 0; m < c1; m++){
	  result[i][j] += X1[i][m] * X2[m][j];
	}
   
      }
    }

    return result;
  }

}
void free_matrix(double **matrix, int r){
  for(int i = 0; i < r; i++){
    free(matrix[i]);
  }
  free(matrix);
}

double** allocate_matrix(int rows, int cols){

  double** ret_val = malloc(rows * sizeof(double*));
  for(int i = 0; i< rows; i++){
    ret_val[i] = malloc(cols * sizeof(double));
  }
  return ret_val;
}

void print_matrix(int r, int c, double **mat){
  for(int i = 0 ; i < r; i++){
    for(int j = 0; j < c; j++){
      printf("%lf\t",mat[i][j]);
    }
    printf("\n");
  }

}

int main(int argc, char** argv)
{

  if(argc!=3){
    printf("insufficient arguments");
    exit(0);
  }

  FILE* train = fopen(argv[1],"r");
  if(train==NULL){
    printf("error");
    exit(0);
  }
  FILE* test = fopen(argv[2],"r");
  if(test==NULL){
    printf("error");
    exit(0);
  }

  /* k is number of attributes, p is size of the array with house prices, y is the array of house prices)*/
  int k,p,h;
  fscanf(train,"%d/n",&k);
  fscanf(train,"%d/n",&p);
  fscanf(test,"%d/n",&h);
  double **y;
  double **matrix,**t, **transp;
  matrix = allocate_matrix(p,(k+1));
  y = allocate_matrix(p,1);
  t = allocate_matrix(h,(k+1));
  /*  w = allocate_matrix((k+1),1);*/
  transp = allocate_matrix((k+1),p);
 
  for(int i=0;i<p;i++)
    {
      matrix[i][0]=1.0;
      for(int j=1;j<k+1;j++)
        {
          fscanf(train, "%lf,",&matrix[i][j]);
        }
      fscanf(train, "%lf\n",&y[i][0]);
 
    }

     for(int i=0;i<h;i++)
		       {
			 t[i][0]=1.0;
			 for(int j=1;j<k+1;j++)
			   {
			     fscanf(test, "%lf,",&t[i][j]);
			   }
			 fscanf(train, "\n");

		       }
     for(int i = 0; i < (k+1); i++){
       for(int j = 0; j < p ; j++){
	 transp[i][j] = matrix[j][i];
       }
     }
     
     double **XX = multiply_matrices(transp,(k+1),p,matrix,p, (k+1));
     double **inverted = invert_matrix(XX,(k+1));
     double **XXX  = multiply_matrices(inverted,(k+1),(k+1),transp, (k+1),p);
     double **w = multiply_matrices(XXX,(k+1),p,y,p,1);
     double **final = multiply_matrices(t,h,(k+1),w,(k+1),1);

     for(int i = 0; i < h; i++){
       double value = final[i][0];
       printf("%0.0lf\n", value);
     }

     /* print_matrix(h,1,final);
                   print_matrix(p,1, y);
		     print_matrix(p, (k+1),matrix);
		     print_matrix(h,(k+1),t);*/
		     fclose(train); 
		     fclose(test);
		     free_matrix(final,h);
		     free_matrix(w,(k+1));
		     free_matrix(XXX,(k+1));  
		     free_matrix(inverted,(k+1));
		     free_matrix(XX,(k+1));		     

		    
		     free_matrix(transp,(k+1));
		    
		     free_matrix(matrix,p);
		     free_matrix(t,h);
		     free_matrix(y,p);
		     return 0;
   }
