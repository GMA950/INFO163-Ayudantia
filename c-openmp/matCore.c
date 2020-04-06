#include <stdlib.h>
#include <stdio.h>

int main() {        
    const int TAM=5;
    int i,j,k;
     
    float matrix1[TAM][TAM];
    float matrix2[TAM][TAM];
    float matrix3[TAM][TAM];
      
    /* asignamos valores a las las matrices */
    for (i=0; i<TAM; i++) {
        for (j=0; j<TAM; j++) {
            matrix1[i][j]=(float)i+j;
            matrix2[i][j]=(float)i-j;
            matrix3[i][j]=(float)0;
        }
    }
 
    #pragma omp parallel for schedule (static) private (i, j, k) 
    for(i=0; i<TAM; i++) { 
      for(j=0; j<TAM; j++) {   
        for(k=0; k<TAM; k++) { 
          matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
        } 
      } 
    } 
     

    for (i=0; i<TAM; i++) {
        for (j=0; j<TAM; j++) {
            printf("|%f|",matrix3[i][j]);
        }
        printf("\n");
    }
    return 0;
}
