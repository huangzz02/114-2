#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
private:
    int n;
    std::vector<std::vector<int>> matrix1;
    std::vector<std::vector<int>> matrix2;
public:
    Matrix(int n, std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2) : n(n), matrix1(matrix1), matrix2(matrix2) {}
    std::vector<std::vector<int>> add(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2);
    std::vector<std::vector<int>> sub(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2);  
    std::vector<std::vector<int>> multipe(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2);
};
    
#endif