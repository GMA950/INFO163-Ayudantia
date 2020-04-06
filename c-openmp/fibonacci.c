#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
/*
Secuencia de Fibonacci
if n < 2 : n
else:
    n(i) = n(i-1) + n(i-2)
*/

long fibonacci(int n)
{
    long fn1,fn2,fn; //n(i) -> fn, n(i-1)-> fn1, n(i-2)->fn2

    usleep(1);
    if(n < 2) return n;

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
    int nthr = 0; 
    long result, n;

    printf("Inserte numero: ");
    scanf("%d",&n);
    printf("\n");

    #pragma omp parallel
    {
        result = fibonacci(n);
    }

    printf("resultado: %ld",result);
}
