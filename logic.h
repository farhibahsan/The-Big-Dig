#ifndef LOGIC_H
#define LOGIC_H

#include "gba.h"

#define NONE 0
#define TOP 1
#define LEFT 2
#define BOTTOM 3
#define RIGHT 4
#define TOPLEFT 5
#define TOPRIGHT 6
#define BOTTOMLEFT 7
#define BOTTOMRIGHT 8
#define ONLYTOP 9
#define ONLYLEFT 10
#define ONLYBOTTOM 11
#define ONLYRIHGT 12
#define NOSIDES 13
#define TOPBOTTOM 14
#define LEFTRIGHT 15

#define DUG 0
#define NOTDUG 1
#define UNTOUCHED 2

#define CELLSIZE 30

typedef struct {
    int dug; // 0 if dug, 1 if not, 2 if untouched
    int connected; //for drawing different sized holes; 0 to draw all four walls, 1 to omit top, 2 to omit left, 3 for botom, 4 for right
    //5 for top and left, 6 for top and right, 7 for bottom and left, 8 for bottom and right, 9 to only have top, 10 for left, 11 for bottom
    //12 for right, 13 for no sides;
} Cell;

#define XMAX 215
#define XMIN 85
#define YMAX 135
#define YMIN 5

typedef struct {
    int x;
    int y;
} Cursor;

typedef struct {
    // Store whether or not the game is over in this member:
    int gameOver;
    Cell cells[25];
    int notDug;
    Cursor cursor;
    /*
    * TA-TODO: Add any logical elements you need to keep track of in your app.
    *
    * For example, for a Snake game, those could be:
    *
    * Snake snake;
    * Food foods[10];
    * int points;
    *
    */

} AppState;

/*
* TA-TODO: Add any additional structs that you need for your app.
*
* For example, for a Snake game, one could be:
*
* typedef struct {
*   int heading;
*   int length;
*   int x;
*   int y;
* } Snake;
*
*/

// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

// If you have anything else you need accessible from outside the logic.c
// file, you can add them here. You likely won't.

#endif
