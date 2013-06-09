#include <stdlib.h>
#include <stdio.h>

#define BOARDMAX 400
#define ALIVE    'X'
#define DEAD     ' '

char grid[22][22];

/* struct to hold info for each cell.
 * alive variable can be either be 1 to signify life or 0 to signify death. */
struct cell { 
    int x;
    int y;
    int alive;
} *cells[1000], *cp;

int cellp = 0;

/* generate pseudo-random num in range (min, max) */
int rand_range(unsigned int min, unsigned int max)
{
    int base_random = rand(); 
    if (RAND_MAX == base_random) 
        return rand_range(min, max);
     int range   = max - min,
     remainder   = RAND_MAX % range,
     bucket      = RAND_MAX / range;
            
     if (base_random < RAND_MAX - remainder) 
         return min + base_random/bucket;
     else 
         return rand_range(min, max);
}

void initcell(int x, int y, int alive)
{
    cp = (struct cell *)malloc(sizeof(struct cell));
    cp->x = x;
    cp->y = y;
    cp->alive = alive;
    cells[cellp++] = cp;
}

void randomize_grid(void)
{
    int x, y, lim, c;

    for (x = 1; x < 21; ++x) {
        lim = rand_range(1, 7);
        for (c = 0; c < lim; ++c) {
            y = rand_range(1, 20);
            if (grid[x][y] != ALIVE) {
                grid[x][y] = ALIVE;
                initcell(x, y, 1);
            }
        }
    }
    for (x = 1; x < 21; ++x) {
        for (y = 1; y < 21; ++y)
            if (grid[x][y] != ALIVE) {
                grid[x][y] = DEAD;
                initcell(x, y, 0);
            }
    }
    /* pad board with whitespace */
    y = 0;
    for (x = 0; x < 22; ++x)
        grid[x][y] = DEAD;
    y = 21;
    for (x = 0; x < 22; ++x)
        grid[x][y] = DEAD;
    x = 0;
    for (y = 0; y < 22; ++y)
        grid[x][y] = DEAD;
    x = 21;
    for (y = 0; y < 22; ++y)
        grid[x][y] = DEAD;
}
/* check the 8 adjacent cells for life and increment count if life exists.
 * the coordinates of the 8 adjacent cells in relation to the passed 
 * x,y coordinates can be represented by the following list:
 * [ [x+1, y+1], [x+1, y], [x+1, y-1], [x, y-1], [x, y+1], [x-1, y-1],
 *   [x-1, y+1], [x-1, y] ]
 */
int check_alive(struct cell *p)
{
    int count, tempx, tempy;
    count = 0;
    int y = p->y;
    tempx = p->x+1;
    if (grid[tempx][y+1] == ALIVE)
        count++;
    if (grid[tempx][y] == ALIVE)
        count++;
    if (grid[tempx][y-1] == ALIVE)
        count++;
    tempx--;
    if (grid[tempx][y-1] == ALIVE)
        count++;
    if (grid[tempx][y+1] == ALIVE)
        count++;
    tempx--;
    if (grid[tempx][y-1] == ALIVE)
        count++;
    if (grid[tempx][y] == ALIVE)
        count++;
    if (grid[tempx][y+1] == ALIVE)
        count++;

    if (p->alive == 0 && count == 3)
        return 1;
    else if (p->alive == 1 && count == 3 || count == 2)
        return 1;
    else 
        return 0;

}

void scan_board(void)
{
    int i;

    for (i = 0; i < BOARDMAX; ++i) 
        cells[i]->alive = (check_alive(cells[i])) ? 1 : 0;
}

void print_board(void)
{
    int i;

    for (i = 0; i < BOARDMAX; ++i) 
        grid[cells[i]->x][cells[i]->y] = (cells[i]->alive) ? ALIVE : DEAD;
    
    int x, y;
    
    for (x = 0; x < 22; ++x) { 
        printf("\n");
        for (y = 0; y < 22; ++y)
            putchar(grid[x][y]);
    }
}

int main(void)
{
    int x, y;

    randomize_grid();

    while (1) {
        scan_board();
        print_board();
    }
    return 0;
}




