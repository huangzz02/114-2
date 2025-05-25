#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix{
    private:
        int N;
        std::vector<std::vector<int>> matrix1;
        std::vector<std::vector<int>> matrix2;
    public:
        Matrix(int N, std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2);
        std::vector<std::vector<int>> add(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2);
        std::vector<std::vector<int>> sub(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2);  
        std::vector<std::vector<int>> multipe(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2);
        std::vector<std::vector<int>> divition(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2);
};

#endif