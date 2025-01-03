// lifefunc.h

#ifndef LIFEFUNC_H
#define LIFEFUNC_H

#define boardSize 40

// function declarations
void createBoard(char board[boardSize][boardSize]);
void displayBoard(char board[boardSize][boardSize]);
void addCell(char board[boardSize][boardSize], int x, int y);
void removeCell(char board[boardSize][boardSize], int x, int y);
int countNeighbors(char board[boardSize][boardSize], int x, int y);
void nextGeneration(char board[boardSize][boardSize]);
void batchMode(char board[boardSize][boardSize], const char *filename);
void interactiveMode(char board[boardSize][boardSize]);

#endif


