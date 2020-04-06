#include <stdlib.h>
#include <stdio.h>

void printMatrix(float *M, int elements, int width){
    for(int i = 0; i < elements; ++i){
        printf("%f ", M[i]);
        if((i+1)%width == 0 && i>0) printf("\n");
    }
}


int main() {        
    int width = 4; //matriz 4x4
    int size = width*width;
    int i,j,k;
     
    float *matrix1 = (float *)malloc(size*sizeof(float));
    float *matrix2 = (float *)malloc(size*sizeof(float));
    float *matrix3 = (float *)malloc(size*sizeof(float));
      
    /* asignamos valores a las las matrices */
    for (i=0; i<size; ++i) {
        matrix1[i]=(i+1)%5;
        matrix2[i]= matrix1[i];
        matrix3[i]=(float)0;
    }
 
    printf("\n");
    printMatrix(matrix1, size, width);
    printf("\n");
    printMatrix(matrix2, size, width);
    printf("\n");

    /*Calculo en paralelo*/
    #pragma omp parallel for schedule (static) private (i, j, k)
    for(i=0; i<width; ++i) { 
      for(j=0; j<width; ++j) {   
        for(k=0; k<width; ++k) { 
          matrix3[width*j+i] += matrix1[width*j + k] * matrix2[width*k+i];
        } 
      } 
    } 
    printf("\n"); 
    printMatrix(matrix3, size, width);
    printf("\n");
    return 0;
}
