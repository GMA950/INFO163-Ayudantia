#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

void printVector(float *vector, int size){
  for(int i = 0; i < size; ++i){
    printf("%f ", vector[i]);
  }
  printf("\n\n");
}

int main() {        
    int TAM=10;
    int i;
    float vec1[TAM];
    float vec2[TAM];
    float result = 0;
    float temp = 0;
      
    /* asignamos valores a las las matrices */
    for (i=0; i<TAM; i++) {
        vec1[i]=i%8;
        vec2[i]=i%8+1;
    }

    printVector(vec1, TAM);
    printVector(vec2, TAM);

    #pragma omp parallel for schedule(static,4) private (i) 
      for(i=0; i<TAM; i++){
            result += vec1[i] * vec2[i];
      }
     
    printf("result: %f\n", result);
    
    return 0;
}
