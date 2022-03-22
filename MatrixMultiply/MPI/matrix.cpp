#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mpi.h>
#define N 10

int main(int argv,char* argc[])
{
    int a[N][N],b[N][N],c[N][N];
    int myid,size,num_row;
    int i,j,k;
    MPI_Status status;
    srand(time(NULL));
    for(i = 0 ; i < N ; i++ )
	for(j = 0 ; j < N ;j++ ){
	    a[i][j] = rand() % 10;
	    b[i][j] = rand() % 10;
	    c[i][j] = 0;
	}

    MPI_Init( &argv , &argc );
    MPI_Comm_rank( MPI_COMM_WORLD, &myid );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    num_row = N / size;
    int remain = N % size;
    for(k = 0; k< N ;k++)
    	for(i = myid*num_row ; i < (myid + 1)*num_row; i++ )
	    for(j=0 ; j< N; j++)
		c[i][k] += a[i][j] * b[j][k];
    if(remain != 0)
    {
	for(k = 0; k< N ;k++)
	for(i = N-remain;i < N;i++)
	    for(j = 0;j < N;j++)
	        c[i][k] += a[i][j] * b[j][k];
    }
    if(myid > 0)
    {
	int row = myid * num_row;
	MPI_Send(&c[row][0],num_row*N,MPI_FLOAT,0,99,MPI_COMM_WORLD);
	if(myid == 1)
	    if(remain != 0)
	        MPI_Send(&c[N-remain][0],num_row*N,MPI_FLOAT,0,99,MPI_COMM_WORLD);
    }
    
    if(myid == 0)
    {
	for(i = size -1;i >=  1; i-- )
	{
	    int row = i * num_row;
	    MPI_Recv(&c[row][0],num_row*N,MPI_FLOAT,i,99,MPI_COMM_WORLD,&status);
	    if(i == 1)
		  MPI_Recv(&c[N-remain][0],num_row*N,MPI_FLOAT,i,99,MPI_COMM_WORLD,&status);

        }
        for(i = 0 ; i < N ; i++ )
        {
            for(j = 0 ; j < N ;j++)
	        printf("%d ",c[i][j]);
	    printf("\n");
        }
    }
    MPI_Finalize();
    return 0;
}
