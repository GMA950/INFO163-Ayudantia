#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#ifdef _OPENMP
    #define TRUE 1
    #define FALSE 0
#else
    #define omp_get_thread_num() 0
    #define omp_get_num_threads() 1
#endif

long fibonacci(n)
{
    long fn1,fn2,fn;

    usleep(1);

    if(n == 0 || n == 1) return(fibonacci(n-1)+fibonacci(n-2));

    #pragma omp task shared(fn1)
        fn1 = fibonacci(n-1);

    #pragma omp task shared(fn2)
        fn2 = fibonacci(n-2);
    
    #pragma omp taskwait
        fn = fn1 + fn2;
    
    return fn;
}

int main()
{
    double tej;
    int nthr = 0, n;
    long result;

    printf("Inserte numero: ");
    scanf("%d",&n);
    printf("\n");

    #pragma omp parallel shared(result)
    {
        #pragma omp single
        {
            result = fibonacci(n);
        }
    }

    printf("resultado: %dd",result);
}
