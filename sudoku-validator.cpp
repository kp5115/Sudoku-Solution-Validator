//
//  sudoku-validator.cpp
//  Sudoku-Solution-Validator
//  Created By: Ronak Shah & Karan Patel
//  180-C - Group 32
//

#include <pthread.h>
#include "sudoku-validator.hpp"

typedef struct {
    int row;
    int column;
    int (*sudoku)[9];
} parameters;

int result[27] = {0};

bool validateRow(parameters* params) {
    int grid[9] = {0};
    for (int i=0; i<9; i++) {
        int val = params->sudoku[params->row][i];
        if (val > 9 || grid[val-1] != 0)
            return false;
        else
            grid[val-1] = 1;
    }
    return true;
}

bool validateColumn(parameters* params) {
    int grid[9] = {0};
    for (int i=0; i<9; i++) {
        int val = params->sudoku[i][params->column];
        if (val > 9 || grid[val-1] != 0)
            return false;
        else
            grid[val-1] = 1;
    }
    return true;
}

bool validateGrid(parameters* params) {
    int grid[9] = {0};
    for (int i=params->row; i<params->row+3; i++) {
        for (int j=params->column; j<params->column+3; j++) {
            int val = params->sudoku[i][j];
            if (val > 9 || grid[val-1] != 0)
                return false;
            else
                grid[val-1] = 1;
        }
    }
    return true;
}

void *isRowValid(void* param) {
    parameters *params = (parameters*)param;
    if (validateRow(params))
        result[params->row] = 1;
    pthread_exit(NULL);
}

void *isColumnValid(void* param) {
    parameters *params = (parameters*)param;
    if (validateColumn(params))
        result[9 + params->column] = 1;
    pthread_exit(NULL);
}

void *isGridValid(void* param) {
    parameters *params = (parameters*)param;
    if (validateGrid(params))
        result[18 + params->row + params->column/3] = 1;
    pthread_exit(NULL);
}

bool validateSudokuSolution(int (*sudoku)[9]) {
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            parameters *data = (parameters *) new parameters;
            data->row = i;
            data->column = j;
            data->sudoku = sudoku;
            if (i%3 == 0 && j%3 == 0 && !validateGrid(data))
                return false;
            if (j == 0 && !validateRow(data))
                return false;
            if (i == 0 && !validateColumn(data))
                return false;
        }
    }
    return true;
}

bool validateSudokuSolutionThreaded(int (*sudoku)[9]) {
    pthread_t threads[27];
    int thread_index = 0;
    
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            parameters *data = (parameters *) new parameters;
            data->row = i;
            data->column = j;
            data->sudoku = sudoku;
            if (i%3 == 0 && j%3 == 0)
                pthread_create(&threads[thread_index++], NULL, isGridValid, data);
            if (j == 0)
                pthread_create(&threads[thread_index++], NULL, isRowValid, data);
            if (i == 0)
                pthread_create(&threads[thread_index++], NULL, isColumnValid, data);
        }
    }
    
    for (int i=0; i<27; i++)
        pthread_join(threads[i], NULL);
    
    for (int i=0; i<27; i++) {
        if (result[i] == 0)
            return false;
    }
    return true;
}
