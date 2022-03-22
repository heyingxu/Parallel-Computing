#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>
#include"mpi.h"
using namespace std;
#define N 1000
  		
int adjust(int *data,int left,int right);
void QuickSort(int *data,int left,int right);
void para_QuickSort(int *data,int left,int right,int m,int id,int myid);
int exp2(int num);
int log2(int num);

int main(int argc,char *argv[])
{
  	int *data;
  	int myid, size, i, j, m;

  	MPI_Status status;
  	MPI_Init(&argc,&argv);
  	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(myid == 0)
  	{
  		data=(int *)malloc(N*sizeof(int));
  		srand(time(NULL));
  		printf("排序前 :");
  		for(i = 0;i < N; i++)
  		{
  			data[i] = rand() % 100000;
  			if(i<100)
				printf("%d ",data[i]);
  		}
		printf("\n");
  	}
  	m = log2(size);
  	para_QuickSort(data,0,N-1,m,0,myid);
  	if(myid == 0)
  	{
  		printf("排序后 :");
  		for(i = 0;i < N; i++)
  			if(i<100)
				printf("%d ",data[i]);
		printf("\n");
  	}
  	MPI_Finalize();
	return 0;
}

int adjust(int *data,int left,int right)
{
	int i = left;
	int j = right;
	int x = data[left];			
	while( i < j )
	{
		while( i < j && data[j] >= x )
			j--;
		if( i < j )
		{
			data[i] = data[j];
			i++;
		}
		while( i < j && data[i] < x)
			i++;
		if( i < j )
		{
			data[j] = data[i];
			j--;
		}
	}
	data[i] = x;
	return i;
}
void QuickSort(int *data,int left,int right)
{
  	int q;
  	if(left<right)
  	{
  		q=adjust(data,left,right);
  		QuickSort(data,left,q-1);
  		QuickSort(data,q+1,right);
  	}
}
  	
void para_QuickSort(int *data,int left,int right,int m,int id,int myid)
{
	int i, j, r, MyLength, *tmp;
  	MPI_Status status;
  	MyLength=-1;
	if(m==0)
  	{
  		if(myid==id)
  		QuickSort(data,left,right);
  		return;
  	}
  	if(myid==id)
  	{
  		r=adjust(data,left,right);
  		MyLength=right-r;
  		MPI_Send(&MyLength,1,MPI_INT,id+exp2(m-1),myid,MPI_COMM_WORLD);
  		if(MyLength!=0)
  			MPI_Send(data+r+1,MyLength,MPI_INT,id+exp2(m-1),myid,MPI_COMM_WORLD);
  	}
  	if(myid==id+exp2(m-1))
  	{
  		MPI_Recv(&MyLength,1,MPI_INT,id,id,MPI_COMM_WORLD,&status);
  		if(MyLength!=0)
  		{
  			tmp=(int *)malloc(MyLength*sizeof(int));
  			if(tmp==0) 
				printf("error!");
  			MPI_Recv(tmp,MyLength,MPI_INT,id,id,MPI_COMM_WORLD,&status);
  		}
  	}
  	j=r-1-left;
  	MPI_Bcast(&j,1,MPI_INT,id,MPI_COMM_WORLD);
  	if(j>0)
  		para_QuickSort(data,left,r-1,m-1,id,myid);
  	j=MyLength;
  	MPI_Bcast(&j,1,MPI_INT,id,MPI_COMM_WORLD);
  	if(j>0)
  		para_QuickSort(tmp,0,MyLength-1,m-1,id+exp2(m-1),myid);
  	if((myid==id+exp2(m-1)) && (MyLength!=0))
  		MPI_Send(tmp,MyLength,MPI_INT,id,id+exp2(m-1),MPI_COMM_WORLD);
  	if((myid==id) && (MyLength!=0))
  		MPI_Recv(data+r+1,MyLength,MPI_INT,id+exp2(m-1),id+exp2(m-1),MPI_COMM_WORLD,&status);
}
