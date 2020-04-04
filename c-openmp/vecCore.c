#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

int main() {        
    const int TAM=10;
    int i,j,k;
    float matrix[TAM][TAM];
    float vec[TAM];
    float matrixR[TAM];
      
    /* asignamos valores a las las matrices */
    for (i=0; i<TAM; i++) {
        for (j=0; j<TAM; j++) {
            matrix[i][j]=2.f;
            matrixR[i]=3.f;
            vec[i]=1.f;
        }
    }
 
    #pragma omp parallel for schedule (static,4) private (i, j, k) 
      for(i=0; i<TAM; i++) { 
        for(j=0; j<TAM; j++) {   
          for(k=0; k<TAM; k++){
            matrixR[i] = matrixR[i] * vec[k] *  matrix[k][j];
          } 
        } 
      } 
     
    for (i=0; i<TAM; i++) {
        for (j=0; j<TAM; j++) {
            
        }
        printf("|%f|",matrixR[i]);
        printf("\n");
    }
    
    return 0;
}
