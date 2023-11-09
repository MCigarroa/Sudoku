#include <iostream>
#include <math.h>

const int BOARD_SIZE = 4;

bool solve(int board[BOARD_SIZE][BOARD_SIZE], int cellNumber);
bool isValid(int board[BOARD_SIZE][BOARD_SIZE], int row, int column, int number);
void printBoard(int board[BOARD_SIZE][BOARD_SIZE]);

int main() {
    int board[BOARD_SIZE][BOARD_SIZE] = {
            { 2, 0, 0, 0 },
            { 0, 1, 0, 2 },
            { 0, 0, 3, 0 },
            { 0, 0, 0, 4 },
    };
    if (solve(board, 0)) {
        printBoard(board);
    } else {
        std::cout << "No solution" << std::endl;
    }

    return 0;
}
bool solve(int board[BOARD_SIZE][BOARD_SIZE], int cellNumber) {
    if (cellNumber == BOARD_SIZE * BOARD_SIZE) return true;

    int row = cellNumber / BOARD_SIZE;
    int column = cellNumber % BOARD_SIZE;

    if (board[row][column] != 0) { // Skip pre-placed
        return solve(board, cellNumber + 1);
    }

    for (int number = 1; number <= BOARD_SIZE; number++) {
        if (isValid(board, row, column, number)) {
            board[row][column] = number;
            if (solve(board, cellNumber + 1)) return true;
            board[row][column] = 0;
        }
    }
    return false;
}
bool isValid(int board[BOARD_SIZE][BOARD_SIZE], int row, int column, int number) {
    if (board[row][column] != 0) return false;
    // check row
    for (int c = 0; c < BOARD_SIZE; c++) {
        if (board[row][c] == number) return false;
    }
    // check column
    for (int r = 0; r < BOARD_SIZE; r++) {
        if (board[r][column] == number) return false;
    }
    // check the box
    int boxSize = (int) sqrt(BOARD_SIZE);
    int boxRowStart = row - row % boxSize;
    int boxColStart = column - column % boxSize;
    for (int r = boxRowStart; r < boxRowStart + boxSize; r++) {
        for (int c = boxColStart; c < boxColStart + boxSize; c++) {
            if (board[r][c] == number) return false;
        }
    }
    return true;
}
void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int r   = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            std::cout << " " << board[r][c] << " ";
        }
        std::cout << std::endl;
    }
}