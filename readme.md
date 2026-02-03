Comparison between Standard and Strassen’s Algorithm for Matrix Multiplication.

This project features a C++ backend managed by CMake and a Python-based data visualization component. The project includes an automated build-and-run script for a seamless development workflow.
📋 Prerequisites

Before you begin, ensure you have the following installed:
System Tools

    C++ Compiler (GCC, Clang, or MSVC)

    CMake (version 3.10 or higher)

    Make (for Unix environments)

Python Environment

The visualization script requires Python 3 and the following libraries:

    pandas

    matplotlib

🚀 How to Build and Run

I have provided a bash script to automate the compilation and execution process. The script handles CMake configuration, building, and automatically locates the generated executable.
Using the Automation Script

    Give the script execution permissions:
Bash

chmod +x build.sh

Run the script by passing the project directory as an argument:
Bash

    ./build.sh .

📊 Data Visualization

The project includes a Python script graph.py to visualize the data output from the C++ application.

Usage:
After running the C++ executable (its generates a data file .csv), run:
Bash

python graph.py