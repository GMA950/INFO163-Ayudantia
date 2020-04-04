#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


main()
{

int count;

#pragma omp parallel
{
    #pragma omp atomic 
            count = count +1;  
}
printf("count: %d\n\n",count);
}
