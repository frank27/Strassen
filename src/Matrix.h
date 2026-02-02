#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using Matrix = std::vector<std::vector<double>>;

struct AnalysisElement
{
    size_t size;
    Matrix A;
    Matrix B;
};

using Multiply = std::function<void(const Matrix &, const Matrix &, int)>;

struct Utils
{
    static void print(const Matrix &A, int n, const std::string &algoName)
    {
        std::cout << algoName << std::endl;
        std::cout << std::fixed << std::setprecision(8);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                std::cout << std::setw(20) << A[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif
