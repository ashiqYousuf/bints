#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "bint.h"

// Function to initialize a matrix of big integers
void initMatrix(bint matrix[][NUM_BLOCKS], size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            initBigInt(&matrix[i][j]);
        }
    }
}

// Function to print a matrix of big integers
void printMatrix(bint matrix[][NUM_BLOCKS], size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            printBigInt(&matrix[i][j]);
        }
    }
}

// Matrix multiplication function (big integers)
void multiplyMatrices(bint A[][NUM_BLOCKS], size_t A_rows, size_t A_cols,
                      bint B[][NUM_BLOCKS], size_t B_rows, size_t B_cols,
                      bint result[][NUM_BLOCKS]) {
    if (A_cols != B_rows) {
        printf("Matrix multiplication dimensions mismatch\n");
        exit(1);
    }

    // Initialize the result matrix
    initMatrix(result, A_rows, B_cols);

    // Perform the multiplication: C = A * B
    for (size_t i = 0; i < A_rows; ++i) {
        for (size_t j = 0; j < B_cols; ++j) {
            // Initialize result[i][j] to zero
            initBigInt(&result[i][j]);
            
            // Compute the dot product of the i-th row of A and the j-th column of B
            for (size_t k = 0; k < A_cols; ++k) {
                bint temp;
                multiplyBigInt(&A[i][k], &B[k][j], &temp); // A[i][k] * B[k][j]
                addBigInt(&result[i][j], &temp, &result[i][j]); // Add to the result
            }
        }
    }
}

int main() {
    bint n1, n2, sum, mul;

    char s1[100], s2[100];

    scanf("%s %s", s1, s2);
    parseBigIntFromHex(&n1, s1);
    parseBigIntFromHex(&n2, s2);

    printBigInt(&n1);
    printBigInt(&n2);

    addBigInt(&n1, &n2, &sum);
    printBigInt(&sum);

    multiplyBigInt(&n1, &n2, &mul);
    printBigInt(&mul);
    getHexFromBInt(&mul);

    return 0;
}
