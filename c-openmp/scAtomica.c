#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

int count = 0;

#pragma omp parallel
{
    #pragma omp atomic 
            count = count +1; // +, -, ++var, --var, var++, var-- 
}
printf("count: %d\n\n",count);
}
