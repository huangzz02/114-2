#include "matrix.h"

#include <vector>

std::vector<std::vector<int>> Matrix::add(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2){
    std::vector<std::vector<int>> result;
    for(int i = 0; i < n; i++){
        std::vector<int> row;
        for(int j = 0; j < n; j++){
            row.push_back(matrix1[i][j] + matrix2[i][j]);
        }
        result.push_back(row);
    }
    return result;
}

std::vector<std::vector<int>> Matrix::sub(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2){
    std::vector<std::vector<int>> result;
    for(int i = 0; i < n; i++){
        std::vector<int> row;
        for(int j = 0; j < n; j++){
            row.push_back(matrix1[i][j] - matrix2[i][j]);
        }
        result.push_back(row);
    }
    return result;
}

std::vector<std::vector<int>> Matrix::multipe(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2){
    std::vector<std::vector<int>> result;
    for(int i = 0; i < n; i++){
        std::vector<int> row;
        for(int j = 0; j < n; j++){
            int sum = 0;
            for(int k = 0; k < n; k++){
                sum += matrix1[i][k] * matrix2[k][j];
            }
            row.push_back(sum);
        }
        result.push_back(row);
    }
    return result;
}