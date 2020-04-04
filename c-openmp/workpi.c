#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 1e9;
double time,time2;

int main()
{

    
    printf("Start workshare parallel\n");
    double step,pi = 0.0,sum = 0.0;
    
    step = 1.0/(double)num_steps;
    time = omp_get_wtime();
    #pragma omp parallel 
    {
        int i;
        double x;
        #pragma omp for reduction(+:sum)
            for(i = 0; i < num_steps; ++i)
            {
                x = (i + 0.5)*step;
                sum = sum + 4.0/(1.0 + x*x);

            }
            
        sum *= step;
        #pragma omp critical
            pi += sum;
    }
    
    time2 = omp_get_wtime();
    printf("Result: %f\nFinish in %f\n",pi, time2-time);
    return 0;
}