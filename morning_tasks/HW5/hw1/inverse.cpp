#include "inverse.h"
#include <vector>

std::vector<int> Inverse::GaussianElimination(std::vector<std::vector<int>> matrixA, 
                                              std::vector<int> matrixB, int N) {
    for (int i = 0; i < N; i++) {
        int pivot = matrixA[i][i];

        for (int j = 0; j < N; j++) {
            matrixA[i][j] /= pivot;
        }
        matrixB[i] /= pivot;

        for (int j = 0; j < N; j++) {
            if (j != i) {
                int factor = matrixA[j][i];
                for (int k = 0; k < N; k++) {
                    matrixA[j][k] -= factor * matrixA[i][k];
                }
                matrixB[j] -= factor * matrixB[i];
            }
        }
    }

    return matrixB;
}

std::vector<std::vector<int>> Inverse::solve(std::vector<std::vector<int>> matrixA,
                                             std::vector<std::vector<int>> matrixB, int N) {
    std::vector<std::vector<int>> result = std::vector<std::vector<int>>(N, std::vector<int>(N, 0));

    for (int j = 0; j < N; j++) {
        std::vector<int> B_col(N);
        for (int i = 0; i < N; i++) {
            B_col[i] = matrixB[i][j];
        }

        std::vector<int> x = GaussianElimination(matrixA, B_col, N);
        // AC=B -> Ax=b (x, b are each column array)

        for (int i = 0; i < N; i++) {
            result[i][j] = x[i];
        }
    }

    return result;
}