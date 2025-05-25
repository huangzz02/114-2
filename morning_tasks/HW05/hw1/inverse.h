#ifndef INVERSE_H
#define INVERSE_H

#include <vector>

class Inverse{
    public:
        static std::vector<int> GaussianElimination(std::vector<std::vector<int>> matrixA, 
                                                    std::vector<int> matrixB, int N);
        std::vector<std::vector<int>> solve(std::vector<std::vector<int>> matrixA,
                                            std::vector<std::vector<int>> matrixB, int N);
};

#endif