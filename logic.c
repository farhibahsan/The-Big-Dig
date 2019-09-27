#include "logic.h"
#include <stdio.h>
#include <stdlib.h>

static int calcUndug(AppState appState) {
    int total = 25;
    for (int i = 0; i < 25; i++) {
        if (appState.cells[i].dug == DUG) {
            total--;
        }
    }

    return total;
}

//NEED TO IMPLEMENT CURSOR
void initializeAppState(AppState* appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it
    // should have when the app begins.
    srand(vBlankCounter);
    appState->notDug = 25;
    appState->gameOver = 0;
    for (int i = 0; i < 25; i++) {
        if (appState->notDug > 13) {
            appState->cells[i].dug = (rand() % 2);
            if (appState->cells[i].dug == DUG) {
                appState->notDug--;
            } else {
                appState->cells[i].dug = UNTOUCHED;
            }
        } else {
            appState->cells[i].dug = UNTOUCHED;
        }
    }

    appState->cursor.x = 85;
    appState->cursor.y = 5;
}

// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);


// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that VBlank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */

    AppState nextAppState = *currentAppState;

    if (KEY_DOWN(BUTTON_LEFT, keysPressedNow)) {
        nextAppState.cursor.x -= 3;
        if (nextAppState.cursor.x < XMIN) {
            nextAppState.cursor.x = XMIN;
        }

        if (nextAppState.cursor.x > XMAX) {
            nextAppState.cursor.x = XMAX;
        }
    }

    if (KEY_DOWN(BUTTON_RIGHT, keysPressedNow)) {
        nextAppState.cursor.x += 3;
        if (nextAppState.cursor.x < XMIN) {
            nextAppState.cursor.x = XMIN;
        }

        if (nextAppState.cursor.x > XMAX) {
            nextAppState.cursor.x = XMAX;
        }
    }

    if (KEY_DOWN(BUTTON_UP, keysPressedNow)) {
        nextAppState.cursor.y -= 3;
        if (nextAppState.cursor.y < YMIN) {
            nextAppState.cursor.y = YMIN;
        }

        if (nextAppState.cursor.y >= YMAX) {
            nextAppState.cursor.y = YMAX;
        }
    }

    if (KEY_DOWN(BUTTON_DOWN, keysPressedBefore)) {
        nextAppState.cursor.y += 3;
        if (nextAppState.cursor.y < YMIN) {
            nextAppState.cursor.y = YMIN;
        }

        if (nextAppState.cursor.y > YMAX) {
            nextAppState.cursor.y = YMAX;
        }
    }

    if (KEY_JUST_PRESSED(BUTTON_A, keysPressedNow, keysPressedBefore)) {
        int col = (currentAppState->cursor.x - 85) / 30;
        int row = (currentAppState->cursor.y - 5) / 30;
        int cellPick = row * 5 + col;

        if (cellPick == 0) {
            if (nextAppState.cells[cellPick].dug == DUG) {
                nextAppState.cells[cellPick].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick].dug = DUG;
            }

            if (nextAppState.cells[cellPick + 1].dug == DUG) {
                nextAppState.cells[cellPick + 1].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick + 1].dug = DUG;
            }

            if (nextAppState.cells[cellPick + 5].dug == DUG) {
                nextAppState.cells[cellPick + 5].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick + 5].dug = DUG;
            }
        } else if (cellPick == 4) {
            if (nextAppState.cells[cellPick].dug == DUG) {
                nextAppState.cells[cellPick].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick].dug = DUG;
            }

            if (nextAppState.cells[cellPick - 1].dug == DUG) {
                nextAppState.cells[cellPick - 1].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick - 1].dug = DUG;
            }

            if (nextAppState.cells[cellPick + 5].dug == DUG) {
                nextAppState.cells[cellPick + 5].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick + 5].dug = DUG;
            }
        } else if (cellPick == 20) {
            if (nextAppState.cells[cellPick].dug == DUG) {
                nextAppState.cells[cellPick].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick].dug = DUG;
            }

            if (nextAppState.cells[cellPick + 1].dug == DUG) {
                nextAppState.cells[cellPick + 1].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick + 1].dug = DUG;
            }

            if (nextAppState.cells[cellPick - 5].dug == DUG) {
                nextAppState.cells[cellPick - 5].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick - 5].dug = DUG;
            }
        } else if (cellPick == 24) {
            if (nextAppState.cells[cellPick].dug == DUG) {
                nextAppState.cells[cellPick].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick].dug = DUG;
            }

            if (nextAppState.cells[cellPick - 1].dug == DUG) {
                nextAppState.cells[cellPick - 1].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick - 1].dug = DUG;
            }

            if (nextAppState.cells[cellPick - 5].dug == DUG) {
                nextAppState.cells[cellPick - 5].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick - 5].dug = DUG;
            }
        } else if (cellPick < 4 && cellPick > 0) {
            if (nextAppState.cells[cellPick].dug == DUG) {
                nextAppState.cells[cellPick].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick].dug = DUG;
            }

            if (nextAppState.cells[cellPick + 1].dug == DUG) {
                nextAppState.cells[cellPick + 1].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick + 1].dug = DUG;
            }

            if (nextAppState.cells[cellPick - 1].dug == DUG) {
                nextAppState.cells[cellPick - 1].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick - 1].dug = DUG;
            }

            if (nextAppState.cells[cellPick + 5].dug == DUG) {
                nextAppState.cells[cellPick + 5].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick + 5].dug = DUG;
            }
        } else if (cellPick % 5 == 0) {
            if (nextAppState.cells[cellPick].dug == DUG) {
                nextAppState.cells[cellPick].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick].dug = DUG;
            }

            if (nextAppState.cells[cellPick + 5].dug == DUG) {
                nextAppState.cells[cellPick + 5].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick + 5].dug = DUG;
            }

            if (nextAppState.cells[cellPick - 5].dug == DUG) {
                nextAppState.cells[cellPick - 5].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick - 5].dug = DUG;
            }

            if (nextAppState.cells[cellPick + 1].dug == DUG) {
                nextAppState.cells[cellPick + 1].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick + 1].dug = DUG;
            }
        } else if (cellPick % 5 == 4) {
            if (nextAppState.cells[cellPick].dug == DUG) {
                nextAppState.cells[cellPick].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick].dug = DUG;
            }

            if (nextAppState.cells[cellPick + 5].dug == DUG) {
                nextAppState.cells[cellPick + 5].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick + 5].dug = DUG;
            }

            if (nextAppState.cells[cellPick - 5].dug == DUG) {
                nextAppState.cells[cellPick - 5].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick - 5].dug = DUG;
            }

            if (nextAppState.cells[cellPick - 1].dug == DUG) {
                nextAppState.cells[cellPick - 1].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick - 1].dug = DUG;
            }
        } else if (cellPick > 20 && cellPick < 24) {
            if (nextAppState.cells[cellPick].dug == DUG) {
                nextAppState.cells[cellPick].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick].dug = DUG;
            }

            if (nextAppState.cells[cellPick + 1].dug == DUG) {
                nextAppState.cells[cellPick + 1].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick + 1].dug = DUG;
            }

            if (nextAppState.cells[cellPick - 1].dug == DUG) {
                nextAppState.cells[cellPick - 1].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick - 1].dug = DUG;
            }

            if (nextAppState.cells[cellPick - 5].dug == DUG) {
                nextAppState.cells[cellPick - 5].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick - 5].dug = DUG;
            }
        } else {
            if (nextAppState.cells[cellPick].dug == DUG) {
                nextAppState.cells[cellPick].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick].dug = DUG;
            }

            if (nextAppState.cells[cellPick + 1].dug == DUG) {
                nextAppState.cells[cellPick + 1].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick + 1].dug = DUG;
            }

            if (nextAppState.cells[cellPick - 1].dug == DUG) {
                nextAppState.cells[cellPick - 1].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick - 1].dug = DUG;
            }

            if (nextAppState.cells[cellPick + 5].dug == DUG) {
                nextAppState.cells[cellPick + 5].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick + 5].dug = DUG;
            }

            if (nextAppState.cells[cellPick - 5].dug == DUG) {
                nextAppState.cells[cellPick - 5].dug = NOTDUG;
            } else {
                nextAppState.cells[cellPick - 5].dug = DUG;
            }
        }
    }

    nextAppState.notDug = calcUndug(nextAppState);
    if (nextAppState.notDug == 0) {
        nextAppState.gameOver = 1;
    }

    return nextAppState;
}
