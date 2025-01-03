// lifefunc.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lifefunc.h"

// function that creates the gameboard
void createBoard(char board[boardSize][boardSize]) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            board[i][j] = ' ';
        }
    }
}

// function that displays the gameboard
void displayBoard(char board[boardSize][boardSize]) {
    printf("+");
    for (int i = 0; i < boardSize; i++){
		printf("-");
	}
    printf("+\n");

    for (int i = 0; i < boardSize; i++) {
        printf("|");
        for (int j = 0; j < boardSize; j++) {
            printf("%c", board[i][j]);
        }
        printf("|\n");
    }

    printf("+");
    for (int i = 0; i < boardSize; i++){
		printf("-");
	}
    printf("+\n");
}

// function that adds a cell
void addCell(char board[boardSize][boardSize], int x, int y) {
    if (x >= 0 && x < boardSize && y >= 0 && y < boardSize) {
        board[x][y] = 'X';
    }
}

// function that removes a cell
void removeCell(char board[boardSize][boardSize], int x, int y) {
    if (x >= 0 && x < boardSize && y >= 0 && y < boardSize) {
        board[x][y] = ' ';
    }
}

// function that counts the neighbors of a cell
int countNeighbors(char board[boardSize][boardSize], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) { 
        for (int j = -1; j <= 1; j++) { // for loops check every surrounding coordinate
            if (!(i == 0 && j == 0)) {
                int neighborX = x + i, neighborY = y + j;
                if (neighborX >= 0 && neighborX < boardSize && neighborY >= 0 && neighborY < boardSize && board[neighborX][neighborY] == 'X') {
                    count++; // counting the number of neighbors
                }
            }
        }
    }
    return count;
}

// function that calculates the next generation
void nextGeneration(char board[boardSize][boardSize]){
    char tempBoard[boardSize][boardSize];
    createBoard(tempBoard);

	// checking if a live cell has 2 or 3 neighbors - if it does, the cell is placed into the temporary board, which is copied into the real board
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            int neighbors = countNeighbors(board, i, j);
            if (board[i][j] == 'X') {
                if (neighbors == 2 || neighbors == 3){
                    tempBoard[i][j] = 'X';
                }
            } 
			else {
                if (neighbors == 3){ // checking if a dead cell has 3 neighbirs - if it does, it becomes live
                    tempBoard[i][j] = 'X';
                }
            }
        }
    }

    // Copying the tempporary board back into the original board
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            board[i][j] = tempBoard[i][j];
        }
    }
}

// interactive mode – triggered when the program with no command line arguments
void interactiveMode(char board[boardSize][boardSize]) {
    displayBoard(board);

    char command;
    int x, y;

    while (1) {
        printf("Menu:\n a followed by two integers: add a new live cell at those coordinates\n r followed by two integers: remove a cell at those coordinates\n n: advance the simulation\n q: quit the program\n p: play the game continuously\nEnter command: ");
        scanf(" %c", &command);

        switch (command) {
            case 'a': // adding a new cell
                printf("Enter two integers:\n");
                scanf("%d %d", &x, &y);
                addCell(board, x, y);
                displayBoard(board);
                break;

            case 'r': // removing a cell
                printf("Enter two integers:\n");
                scanf("%d %d", &x, &y);
                removeCell(board, x, y);
                displayBoard(board);
                break;

            case 'n': // advancing the simulation
                nextGeneration(board);
                displayBoard(board);
                break;

            case 'p': // play game continuously
                while (1) {
                    system("clear");
                    displayBoard(board);
                    nextGeneration(board);
                    usleep(100000);
                }
                break;

            case 'q': // quit the program
                return;

            default:
                printf("Command not found\n");
        }
    }
}

// batch mode – triggered if the executable is followed by a data file
void batchMode(char board[boardSize][boardSize], const char *filename) {
    FILE *file = fopen(filename, "r"); // opening in the file
    if (file == NULL) {
        printf("Error: Could not find file %s\n", filename);
        exit(1);
    }

    // reading in the command and coordinates from the file
    char command;
    int x, y;
    while (fscanf(file, " %c", &command) == 1) {
        if (command == 'a') {
            fscanf(file, "%d %d", &x, &y);
            addCell(board, x, y);
        }
    }
    fclose(file);

    // play the game continuously
    while (1) {
        system("clear");
        displayBoard(board);
        nextGeneration(board);
        usleep(100000);
    }
}



  
