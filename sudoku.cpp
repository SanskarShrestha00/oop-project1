#include <iostream>

class Sudoku {
private:
    static const int SIZE = 6;
    int** grid;

public:
    Sudoku(int initial_grid[SIZE][SIZE]) {
        // Allocate memory for the grid
        grid = new int*[SIZE];
        for (int i = 0; i < SIZE; i++) {
            grid[i] = new int[SIZE];
        }

        // Initialize the grid with the given initial values
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                grid[i][j] = initial_grid[i][j];
            }
        }
    }

    ~Sudoku() {
        // Deallocate the memory
        for (int i = 0; i < SIZE; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    void printGrid() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    bool isSafe(int row, int col, int num) {
        // Check if 'num' is not in current row and current column
        for (int x = 0; x < SIZE; x++) {
            if (grid[row][x] == num || grid[x][col] == num) {
                return false;
            }
        }

        // Check if 'num' is not in current 2x3 sub-grid
        int startRow = row - row % 2, startCol = col - col % 3;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i + startRow][j + startCol] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    bool findEmptyLocation(int &row, int &col) {
        for (row = 0; row < SIZE; row++) {
            for (col = 0; col < SIZE; col++) {
                if (grid[row][col] == 0) {
                    return true;
                }
            }
        }
        return false;
    }

    bool solveSudoku() {
        int row, col;
        if (!findEmptyLocation(row, col)) {
            return true; // success, no empty space left
        }

        for (int num = 1; num <= SIZE; num++) {
            if (isSafe(row, col, num)) {
                grid[row][col] = num;
                if (solveSudoku()) {
                    return true;
                }
                grid[row][col] = 0; // failure, undo & try again
            }
        }
        return false; // triggers backtracking
    }
};

int main() {
    int initial_grid[6][6] = {
        {0, 0, 0, 1, 0, 4},
        {0, 0, 6, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 5, 6},
        {0, 0, 0, 0, 0, 0},
        {2, 0, 3, 5, 0, 0}
    };

    Sudoku sudoku(initial_grid);

    if (sudoku.solveSudoku()) {
        std::cout << "Solved Sudoku grid:" << std::endl;
        sudoku.printGrid();
    } else {
        std::cout << "No solution exists for the given Sudoku grid." << std::endl;
    }

    return 0;
}
