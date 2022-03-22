#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<omp.h>
#include<time.h>

int main()
{
    long long int num_point,num_in_cycle = 0;
    double x,y,distance,pi;
    num_point = 1000000;
    srand(time(NULL));
    #pragma omp parallel for num_threads(4)
    for(long long int i = 0 ; i < num_point ; i++ )
    {
	    x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        distance = pow(x * x + y * y , 0.5 );
        if(distance <= 1)
	    num_in_cycle++;
    }
    pi = (double)num_in_cycle / num_point * 4;
    printf("pi = %lf\n",pi);
    return 0;
}
