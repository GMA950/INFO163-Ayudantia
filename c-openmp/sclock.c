#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


main()
{
omp_lock_t C;

int count = 0;

#pragma omp parallel
{ 

     omp_init_lock(&C);

    
    omp_set_lock(&C); 
         count = count +1;
         printf("in lock, count: %d\n\n",count);
    omp_unset_lock(&C);
          printf("out of lock, count: %d\n\n",count);
   omp_destroy_lock(&C);

 }

printf("final, count: %d\n\n",count);

}


