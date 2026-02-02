#ifndef MATRIXALGORITHMANALYSIS_H
#define MATRIXALGORITHMANALYSIS_H

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <map>
#include <functional>

#include "Matrix.h"
#include "StandardAlgorithm.h"
#include "DivideConquerAlgorithm.h"
#include "StrassenAlgorithm.h"

class MatrixAlgorithmAnalysis
{
public:
    const std::vector<int> SIZES = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};

    const int REPEATS = 3;

    std::vector<std::tuple<int, int, double, int>> results;

    const std::map<int, std::string> ALGORITHM_LEGEND = {
        {0, "Standard Algorithm"},
        {1, "Divide And Conquer"},
        {2, "Strassen Algorithm"},
    };

    void execute()
    {
        auto methods = getMultiplyMethods();
        auto dataset = getMatrixDataset();
        for (const auto &data : dataset)
        {
            for (const auto &[id, func] : methods)
            {
                for (int i = 0; i < REPEATS; ++i)
                {
                    double t = measureTime(func, data);
                    addStat(id, t, data.size, i);
                    std::cout << "Algo " << id << " Size " << data.size << " Time " << t << "s\n";
                }
            }
        }
        exportData();
    }

private:
    // ===================== ALGORITHMS =====================

    std::map<int, Multiply> getMultiplyMethods()
    {
        static StandardAlgorithm standard;
        static DivideConquerAlgorithm divideConquer;
        static StrassenAlgorithm strassen;

        return {
            {0, [&](const Matrix &A, const Matrix &B, int n)
             {
                 standard.multiply(A, B, n);
             }},
            {1, [&](const Matrix &A, const Matrix &B, int n)
             {
                 divideConquer.multiply(A, B, n);
             }},
            {2, [&](const Matrix &A, const Matrix &B, int n)
             {
                 strassen.multiply(A, B, n);
             }},
        };
    }
    // ===================== DATASETS =====================

    std::vector<AnalysisElement> getMatrixDataset()
    {
        std::vector<AnalysisElement> data;
        for (int size : SIZES)
        {
            auto A = generateRandomMatrix(size, size, 0, 100);
            auto B = generateRandomMatrix(size, size, 0, 100);
            data.push_back({A.size(), A, B});
        }
        return data;
    }

    // ===================== TIMING =====================
    // return seconds

    double measureTime(const Multiply &func, const AnalysisElement &data)
    {

        auto start = std::chrono::high_resolution_clock::now();
        func(data.A, data.B, data.size);
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(end - start).count();
    }

    double measureTime(const Multiply &func, const AnalysisElement &data, int repeats)
    {
        double total = 0.0;
        for (int i = 0; i < repeats; ++i)
        {
            auto start = std::chrono::high_resolution_clock::now();
            func(data.A, data.B, data.size);
            auto end = std::chrono::high_resolution_clock::now();
            total += std::chrono::duration<double>(end - start).count();
        }
        return total / repeats;
    }
    // ===================== UTILS =====================

    void addStat(int algorithm, double timeTaken, int size, int repeatNumber)
    {
        results.emplace_back(algorithm, size, timeTaken, repeatNumber);
    }

    int nextPowerOfTwo(int n)
    {
        int p = 1;
        // Double p until it’s ≥ n
        while (p < n)
        {
            p <<= 1;
        }
        return p;
    }

    Matrix generateRandomMatrix(int rows, int cols, double minVal, double maxVal)
    {
        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<double> dist(minVal, maxVal);

        int size = nextPowerOfTwo(std::max(rows, cols));

        Matrix m(size, std::vector<double>(size, 0.0));

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                // Generates a double with ~15–16 decimal digits of precision.
                m[i][j] = dist(gen);
            }
        }

        return m;
    }

    void exportData()
    {
        std::ofstream file("matrix_multiplication_comparison_cpp.csv");
        file << "Algorithm,Size,RepeatNumber,TimeSeconds,AlgorithmName\n";

        for (const auto &[algo, size, time, repeatNumber] : results)
            file << algo << "," << size << ","
                 << repeatNumber << "," << time << ","
                 << ALGORITHM_LEGEND.at(algo) << "\n";

        std::cout << "CSV exported successfully.\n";
    }
};

#endif