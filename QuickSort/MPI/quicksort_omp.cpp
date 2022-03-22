#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#define N 30 

int* quicksort(int* Data,int left,int right);
int adjust(int* data,int left,int right);
int main()
{
	int *Data;
	Data=new int[N];
	srand(time(NULL));
	printf("排序前:");
	for(int i=0;i<N;i++)
	{
		Data[i]=rand()%100;
		printf("%d ",Data[i]);
        }
      printf("\n");
	omp_set_num_threads(2); 
	Data=quicksort(Data,0,N-1);
	printf("排序后:");
	for (int i=0;i<N;i++)
	{
		printf("%d ",Data[i]);
	}
	printf("\n");
}

int* quicksort(int* Data,int left,int right)
{
	int q;
	if(left<right)
	{
		q=adjust(Data,left,right);
            #pragma omp parallel 
		{
            	#pragma omp sections nowait
			{
                   	#pragma omp section
			      quicksort(Data,left,q-1);
              		#pragma omp section
			      quicksort(Data,q+1,right);
			}
		}
	}
	return Data;
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
