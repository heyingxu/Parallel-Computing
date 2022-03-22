#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#define N 20
#define count 2
int main()
{
    int a[N][N],b[N][N],c[N][N];
    int i,j,k;
    for(i =  0 ; i < N ; i++ )
	    for(j = 0 ; j < N ; j++){
	        a[i][j] =  rand() % 10;
	        b[i][j] =  rand() % 10;
	        c[i][j] =  0;
	}
    #pragma omp parallel for num_threads(count)
	    for(i = 0 ; i < N ;i++ )
		for(j = 0 ; j < N ;j++)
		    for(k = 0 ; k < N ; k++)
			c[i][j] += a[i][k] * b[k][j];
    FILE *fp;
    fp = fopen("resule_omp.txt","w");
    for(i = 0 ;i < N ;i++ ){
	for(j = 0; j < N ;j++){
	   fprintf(fp,"%d ",c[i][j]);	
        }
	fprintf(fp,"\n");
    }
    fclose(fp);
    return 0;
}
