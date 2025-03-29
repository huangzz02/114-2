#include "matrix.h"
#include "inverse.h"
#include <vector>

Matrix::Matrix(int N, std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2){
    this->N = N;
    this->matrix1 = matrix1;
    this->matrix2 = matrix2;
}

std::vector<std::vector<int>> Matrix::add(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2){
    std::vector<std::vector<int>> result;
    for(int i = 0; i < N; i++){
        std::vector<int> row;
        for(int j = 0; j < N; j++){
            row.push_back(matrix1[i][j] + matrix2[i][j]);
        }
        result.push_back(row);
    }
    return result;
}

std::vector<std::vector<int>> Matrix::sub(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2){
    std::vector<std::vector<int>> result;
    for(int i = 0; i < N; i++){
        std::vector<int> row;
        for(int j = 0; j < N; j++){
            row.push_back(matrix1[i][j] - matrix2[i][j]);
        }
        result.push_back(row);
    }
    return result;
}

std::vector<std::vector<int>> Matrix::multipe(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2){
    std::vector<std::vector<int>> result;
    for(int i = 0; i < N; i++){
        std::vector<int> row;
        for(int j = 0; j < N; j++){
            row.push_back(matrix1[i][j] * matrix2[i][j]);
        }
        result.push_back(row);
    }
    return result;
}

std::vector<std::vector<int>> Matrix::divition(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2){
    Inverse inverse;
    std::vector<std::vector<int>> result = inverse.solve(matrix1, matrix2, N);
    return result;
}