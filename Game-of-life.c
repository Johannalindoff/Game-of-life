/*
 * Programmeringsteknik med C och Matlab
 * Fall 19
 * Assignment 3

 * File:         ou3.c
 * Description:  A simple implementation of Conway's Game of Life.
 * Author:       Johanna Lindoff
 * CS username:  id19jlf
 * Date:         2019-10-22
 * Input:        Choice of initial configuration and then instruction to step
 *               or exit.
 * Output:       Prints the game field in each step.
 * Limitations:  No validation of input.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Constants, representation of states */
#define ALIVE 'X'
#define DEAD '.'

/* Declaration of data structure */
typedef struct{
    char current;
    char next;
} cell;

/* Declaration of functions */
void initField(const int rows, const int cols, cell field[rows][cols]);
void loadGlider(const int rows, const int cols, cell field[rows][cols]);
void loadSemaphore(const int rows, const int cols, cell field[rows][cols]);
void loadRandom(const int rows, const int cols, cell field[rows][cols]);
void loadCustom(const int rows, const int cols, cell field[rows][cols]);
void printField(const int rows, const int cols, cell field[rows][cols]);
void printMenu();
char readChoice (void);
void nextGeneration (const int rows, const int cols, cell field[rows][cols]);
void checkNeighbors (const int rows, const int cols, cell field[rows][cols], const int x, const int y);


/* Function:    main
 * Description: Start and run games, interact with the user.
 * Input:       About what initial structure and whether to step or exit.
 * Output:      Information to the user, and the game field in each step.
 */

int main(void) {

    int rows = 20;
    int cols = 20;
    char choice;
    cell field[rows][cols];

    srand(time(NULL));

    initField(rows, cols, field);

    do {
        printField(rows, cols, field);
        printMenu();
        choice = readChoice ();
        if (choice == '\n') {
            nextGeneration (rows, cols, field);
        }
    } while (choice == '\n');
    return 0;
}


/* Function:    initField
 * Description: Initialize all the cells to dead, then asks the user about
 *              which structure to load, and finally load the structure.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void initField(const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            field[r][c].current = DEAD;
        }
    }

    printf("Select field spec to load ([G]lider, [S]emaphore, [R]andom ");
    printf("or [C]ustom): ");

    int ch = getchar();

	/* Ignore following newline */
    if (ch != '\n') {
        getchar();
    }

    switch (ch) {
        case 'g':
        case 'G':
            loadGlider(rows, cols, field);
            break;
        case 's':
        case 'S':
            loadSemaphore(rows, cols, field);
            break;
        case 'r':
        case 'R':
            loadRandom(rows, cols, field);
            break;
        case 'c':
        case 'C':
        default:
            loadCustom(rows, cols, field);
            break;
    }
}


/* Function:    loadGlider
 * Description: Inserts a glider into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadGlider(const int rows, const int cols, cell field[rows][cols]) {

    field[0][1].current = ALIVE;
    field[1][2].current = ALIVE;
    field[2][0].current = ALIVE;
    field[2][1].current = ALIVE;
    field[2][2].current = ALIVE;
}


/* Function:    loadSemaphore
 * Description: Inserts a semaphore into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadSemaphore(const int rows, const int cols, cell field[rows][cols]) {

    field[8][1].current = ALIVE;
    field[8][2].current = ALIVE;
    field[8][3].current = ALIVE;
}


/* Function:    loadRandom
 * Description: Inserts a random structure into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated. There is a 50 % chance that a cell
 *              is alive.
 */

void loadRandom(const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            if (rand()%2 == 1) {
                field[r][c].current = ALIVE;
            }
            else {
                field[r][c].current = DEAD;
            }
        }
    }
}


/* Function:    loadCustom
 * Description: Lets the user specify a structure that then is inserted into
 *              the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void loadCustom(const int rows, const int cols, cell field[rows][cols]) {

    printf("Give custom format string: ");
    do {
        int r, c;
        scanf("%d,%d", &r, &c);
        field[r][c].current = ALIVE;
    } while (getchar() != '\n');
}


/* Function:    printField
 * Description: The function prints the gamefield.
 * Input:       The field array and its size.
 * Output:      Prints the updated field to the screen.
 */
void printField(const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            printf("%c ", field[r][c].current);
        }
        printf("\n");
    }
}


/* Function:    printMenu
 * Description: The menu repeats as long as the user press enter.
 *              If the user press any other key the program will stop.
 * Input:
 * Output:      The menu is printed to the screen.
 */
void printMenu() {

    printf("Select one of the following options:\n");
    printf("\t(enter)\tStep\n");
    printf("\t(any)\tExit\n");
}


/* Function:    readChoice
 * Description: The function register which key the user presses.
 * Input:
 * Output:      Returns a value to the variable "choice" in the main function.
 */
char readChoice (void) {

    return getchar();
}


/* Function:    nextGeneration
 * Description: Updates the upcoming gamefield based on the previous neighbours.
 * Input:       The field array and its size.
 * Output:      A updated version of the field.
 */
void nextGeneration (const int rows, const int cols, cell field[rows][cols]) {

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            checkNeighbors (rows, cols, field, c, r);
        }
    }

    for (int r = 0 ; r < rows ; r++) {
        for (int c = 0 ; c < cols ; c++) {
            field[r][c].current = field[r][c].next;
        }
    }
}


/* Function:    checkNeighbors
 * Description: The function checks if the neighbors are dead or alive.
 * Input:       The field array, the arrays size and x- and y-coordinates.
 * Output:      A updated version of the upcoming version of neighbors.
 */
void checkNeighbors (const int rows, const int cols, cell field[rows][cols],
                    const int x, const int y) {

    int numberOfNeighbors = 0;

    for (int r = y-1 ; r <= y+1 ; r++) {
        for (int c = x-1 ; c <= x+1 ; c++) {
            if (field[r][c].current == ALIVE && r >= 0 && r < rows &&
                c >= 0 && c < cols && !(r == y && c == x)) {
                numberOfNeighbors += 1;
            }
        }
    }

    if (field[y][x].current == ALIVE) {
        if (numberOfNeighbors < 2 || numberOfNeighbors > 3) {
            field[y][x].next = DEAD;
        }
        else {
            field[y][x].next = ALIVE;
        }
    }
    else {
        if (numberOfNeighbors == 3) {
            field[y][x].next = ALIVE;
        }
        else {
            field[y][x].next = DEAD;
        }
    }
}
