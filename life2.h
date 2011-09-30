// life2.h
#ifndef __LIFE2_H__
#define __LIFE2_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Used to seed random number generator.

// Initialize the board(s) and associated variables.
void lifeInit(int nrow, int ncol);

// Randomly populate the current board with the specified
// percentage of alive Cells.
void lifePopulateRandom(float percent);

// Return the number of Cell that are alive in the current board.
int lifeNumAlive(void);

// Apply the Life rules to update the status of each Cell.
void lifeStep(void);

// Free the memory associated with all the Cells.
void lifeDestroy(void);

// Print the current life board.
void lifePrint(void);

// Print the number of neighbors each Cell has.
void lifePrintNeighbors(void);

// Shift the status of all the Cells left one grid position (with
// appropriate wrapping).
void lifeShiftLeft(void);

// Shift the status of all the Cells "up" one grid position (with
// appropriate wrapping).  Note that the Cells are actually moved to
// the row with a lower index.
void lifeShiftUp(void);

// Shift the status of all the Cells "down" one grid position (with
// appropriate wrapping).  Note that the Cells are actually moved to
// the row with a higher index.
void lifeShiftDown(void);

// Shift the status of all the Cells right one grid position (with
// appropriate wrapping).
void lifeShiftRight(void);

#endif // __LIFE2_H__