#include <stdio.h>
#include <stdlib.h>

double* input_matrix(int *rows, int *columns, char *prompt) {
    printf("%s\n", prompt);
    
    printf("Enter number of rows: ");
    scanf("%d", rows);

    printf("Enter number of columns: ");
    scanf("%d", columns);

    double *matrix = (double *)malloc(*rows * *columns * sizeof(double));

    if(matrix == NULL) {
        return NULL;
    }

    printf("Enter elements:\n");
    for(int i = 0; i < *rows; i++) {
        for(int j = 0; j < *columns; j++) {
            scanf("%lf", &matrix[i * *columns + j]);
        }
    }
    
    return matrix;
}

int matrix_multiply(double *m1, int m1_rows, int m1_cols, double *m2, int m2_rows, int m2_cols, double *result) {
    if(m1_cols != m2_rows) {
        return 0;
    }

    for(int i = 0; i < m1_rows; i++) {
        for(int j = 0; j < m2_cols; j++) {
            result[i * m2_cols + j] = 0;
            for(int k = 0; k < m1_cols; k++) {
                result[i * m2_cols + j] += m1[i * m1_cols + k] * m2[k * m2_cols + j];
            }
        }
    }

    return 1;
}

void output_matrix(double *matrix, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("%lf ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

int main(void) {

    double *m1,*m2,*m3;
    int m1_rows,m1_columns,m2_rows,m2_columns;

    if (((m1 = input_matrix(&m1_rows,&m1_columns,"Matrix 1")) != NULL) &&
((m2 = input_matrix(&m2_rows,&m2_columns,"Matrix 2")) != NULL) &&
((m3 = malloc(m1_rows*m2_columns*sizeof(double))) != NULL)) {
        printf("Matrix 1\n");
        output_matrix(m1,m1_rows,m1_columns);
        printf("Matrix 2\n");
        output_matrix(m2,m2_rows,m2_columns);
        if (matrix_multiply(m1,m1_rows,m1_columns,m2,m2_rows,m2_columns,m3)) {
            printf("Product\n");
            output_matrix(m3,m1_rows,m2_columns);
            free(m1);
            free(m2);
            free(m3);
            return(0);
        } else {
            printf("Error in dimensions\n");
            free(m1);
            free(m2);
            free(m3);
            return(-1);
        }
    } else {
        free(m1);
        free(m2);
        free(m3);
        printf("Error allocating memory\n");
        return(-2);
    }
}

