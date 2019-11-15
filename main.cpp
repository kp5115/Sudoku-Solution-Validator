//
//  main.cpp
//  Sudoku-Solution-Validator
//  Created By: Ronak Shah & Karan Patel
//  180-C - Group 32
//

#include <iostream>
#include <chrono>
#include "sudoku-validator.hpp"
using namespace std;
using namespace std::chrono;

int main() {
    int a[9][9] = {
        {6, 2, 4, 5, 3, 9, 1, 8, 7},
        {5, 1, 9, 7, 2, 8, 6, 3, 4},
        {8, 3, 7, 6, 1, 4, 2, 9, 5},
        {1, 4, 3, 8, 6, 5, 7, 2, 9},
        {9, 5, 8, 2, 4, 7, 3, 6, 1},
        {7, 6, 2, 3, 9, 1, 4, 5, 8},
        {3, 7, 1, 9, 5, 6, 8, 4, 2},
        {4, 9, 6, 1, 8, 2, 5, 7, 3},
        {2, 8, 5, 4, 7, 3, 9, 1, 6}
    };
    int (*sp)[9] = a;
    
    cout << "----------Single Thread Approach----------\n\n";
    high_resolution_clock::time_point start_time = high_resolution_clock::now();
    bool validFlag = validateSudokuSolution(sp);
    high_resolution_clock::time_point end_time = high_resolution_clock::now();
    microseconds duration = duration_cast<microseconds>(end_time - start_time);
    if (validFlag)
        cout << "Valid Sudoku Solution\n";
    else
        cout << "Invalid Sudoku Solution\n";
    cout << "Time Taken: " << duration.count() << " μs\n\n";
    
    cout << "----------Multi Thread Approach----------\n\n";
    start_time = high_resolution_clock::now();
    bool validFlagThreaded = validateSudokuSolutionThreaded(sp);
    end_time = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end_time - start_time);
    if (validFlagThreaded)
        cout << "Valid Sudoku Solution\n";
    else
        cout << "Invalid Sudoku Solution\n";
    cout << "Time Taken: " << duration.count() << " μs\n\n";
    
    return 0;
}
