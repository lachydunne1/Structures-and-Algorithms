#include <stdint.h>
#include <math.h>
#include "nrutil.h"

/*
    Matrix Operations: All matrix operations defined below will convert matrices into 1D
    in order to compute the desired outcome.
*/


// brief: set all matrix elements to 0.
void matrix_zero(int16_t *matrix, uint8_t elements){

    for (uint8_t i = 0; i < elements; i++){
        //derefence matrix pointer, and iterate through matrix using pointer 
        //arithmetic
        *(matrix+i) = 0;
    }
}

//brief: use indexing to print all elements of a two-dimensional array.
void matrix_print(int16_t *matrix, uint8_t *dim){
    for (uint8_t i = 0; i<dim[0]; i++){

        for (uint8_t j = 0; j<dim[1]; j++){
            printf("% 6d ", matrix[i * dim[1] + j]);
        }
        printf("\n");
    }
}

//brief: calculate matrix dimensions and sum elements. elements must be of the 
//same dimensions. Can also use indexing here, may be useful to do so for consistency.
void matrix_sum(int16_t* m_A, uint8_t* size_M, int16_t*  m_B, int16_t* output){

    for (uint8_t i = 0; i<(size_M[0] * size_M[1]); i++)
        output[i] = m_B[i] + m_A[i];
    
}


void matrix_add(int16_t* m_A, uint8_t* size_A, int k, int16_t* output){

    for(uint8_t i = 0; i<(size_A[0]*size_A[1]); i++)
        output[i] = m_A[i] + k;
}

void matrix_scale(int16_t* m_A, uint8_t* size_A, int16_t k, int16_t* output){

    for(uint8_t i = 0; i<(m_A[0] * m_A[1]); i++)
        output[i] = m_A[i] * k;

}

void matrix_mul(uint16_t *A, uint8_t dims_A[], uint16_t *B, uint8_t dims_B[], uint16_t *result){
    uint8_t rA = dims_A[0];
    uint8_t cA  = dims_A[1];
    uint8_t cB = dims_B[1];

    
    for (uint8_t i = 0; i < rA; i++) {
        for (uint8_t j = 0; j < cA; j++) {

            //initialize element as zero
            *(result + i * cB + j) = 0;
            for (uint8_t k = 0; k < cA; k++) {
                //use indexing to dereference pointers to element as dot product value.
                *(result + i * cB + j) += (*(A + i *  + k)) * (*(B + k * cB+ j));
            }
        }

    }
}

void transpose_square_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            // Swap matrix[i][j] and matrix[j][i]
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

#define TOL 1.0e-15

/*

    Advanced Linear Algebra algorithms in C:
    (see Numerical Recipes in C page 47)

    The following algorithms may come in useful when programming
    embedded systems to solve systems of equations. 


*/

void lu_dcmp(float **a, int n, int *indx, float *d){

    int i,imax,j,k;
    float big,dum,sum,temp;
    float *vv; //"stores implicit scaling of each row"

    vv= vector(1,n);
    *d=1.0;

    for (i=1; i<=n; i++){
        big = 0.0;
        for (j=1; j<=n; j++)

            if ((temp = fabs(a[i][j])) > big)
                big = temp;

        if (big== 0.0) nerror("Singular matrix in routine ludcmp");
        vv[i]=1.0/big;

    }
    for (j=1; j<=n; j++){
        for (i=1; i<j; i++){
            sum = a[i][j];
            
            for (k=1; k<i; k++) 
                sum -= a[i][k]*a[k][j];
            a[i][j] = sum;
        }

        big = 0.0;
        for (i=j; i<=n; i++){
            sum=a[i][j];

            for(k=1;k<j;k++)
                sum -= a[i][k]*a[k][j];
            a[i][j]=sum;
            if ( (dum= vv[i]*fabs(sum)) >= big){
                /* Is the figure of merit for the pivot better than the best so far?*/
                big = dum;
                imax = i;
            }
            /* Do we need to interchange rows?*/
            if (j!=imax){
                /* YES: */
                for (k=1; k<=n; k++){
                    dum=a[imax][k];
                    a[imax][k] = a[j][k];
                    a[j][k] = dum;
                }
                *d=-(*d);
                vv[imax]=vv[j];

            }
            indx[j]=imax;
            if (a[j][j] == 0.0) a[j][j] = TOL;
            /* If the pivot element is zero the matrix is singular, (at least
            to the precision of the algorithm). For some applications on singular matrices
            it is desirable to substitute TOL for zero.*/
            if (j != n){
                dum = 1.0/(a[j][j]);
                for (i=j+1;i<=n;i++) 
                    a[i][j] *= TOL;
            }

        }
        free_vector(vv,1,n);
    }

}

/* Forward substitution and backsubstitution */

void lubskb(float **a, int n, int *indx, float b[]){

    int i, ii=0, ip, j;

    float sum;


    /* When ii is set to a positive value, it will become the
    index of the first nonvanishing element b. We now complete
    forward substitution*/
    for (i=1; i<=n; i++){
        ip = indx[i];
        sum = b[ip];
        b[ip] = b[i];
        if (ii)
            for (j = ii; j<= i-1; j++) sum -=a[i][j]*b[j];
        else if (sum) ii =i;
        b[i] = sum;
    }
    /* Perform back substitution */
    for (i=n; i>=1; i--){
        sum=b[i]; 
        for (j=i+1; j<=n; j++) sum -= a[i][j]*b[j];
        /* Store component of solution in vector*/
        b[i] =sum/a[i][i];
    }
}