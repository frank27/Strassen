cmake_minimum_required(VERSION 3.5)

project(MultiplyAnalysis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (project_sources
    src/main.cpp
    src/MatrixAlgorithmAnalysis.h
    src/StandardAlgorithm.h
    src/Matrix.h
    src/StrassenAlgorithm.h
    src/DivideConquerAlgorithm.h
)

add_executable(MultiplyAnalysis ${project_sources})

