#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<mpi.h>

int main( int argc ,char** argv)
{
    long long int num_point,num_in_cycle = 0;
    long long int temp_num,total_num;
    num_point = 1000000;
    int myid,size;
    MPI_Init(&argc , &argv);
    MPI_Comm_size(MPI_COMM_WORLD , &size);
    MPI_Comm_rank(MPI_COMM_WORLD , &myid);
    
    temp_num = num_point / size;
    double x,y,distance;
    srand(time(NULL));
    for(long long int i = 0 ; i < temp_num ; i++ )
    {
	x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        //x = 2*x -1;
        //y = 2*y -1;
        distance = pow(x*x + y*y,0.5) ;
	if(distance <= 1)
	    num_in_cycle += 1;
    }
    MPI_Reduce(&num_in_cycle,&total_num,1,MPI_LONG_LONG,MPI_SUM,0,MPI_COMM_WORLD);
    if(myid == 0)
    {
	double pi = (double)total_num / num_point * 4 ;
        printf("pi = %lf\n",pi);
    }
    MPI_Finalize();
    return 0;
}
