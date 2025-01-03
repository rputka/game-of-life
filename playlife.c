// playlife.c
//
// Ryan Putka
// Fundamentals of Computing
// November 5, 2024
//
// This program will simulate Conway's Game of Life

#include <stdio.h>
#include "lifefunc.h"

 // command line arguments
int main(int argc, char *argv[]) {
    char board[boardSize][boardSize];
    createBoard(board);

    if (argc == 1) { // if executable not followed by a data file, interactive mode played
        interactiveMode(board);
    } else if (argc == 2) {
        batchMode(board, argv[1]); // if executable followed by a data file, batch mode is triggered
    } else {
        printf("Error: Too many arguments\n");
        return 1;
    }

    return 0;
}

