/* Copyright (c) 2022 xylous <xylous.e@gmail.com>
 *
 * This file is part of izobata.
 * izobata is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * izobata is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * izobata.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "izobata.h"
#include <stdlib.h>
#include <ncurses.h>

Point *new_point(int x, int y)
{
    Point *v = calloc(1, sizeof(Point));
    v->x = x;
    v->y = y;
    return v;
}

Polygon *new_polygon(void)
{
    Polygon *pgn = calloc(1, sizeof(Polygon));
    pgn->points = NULL;
    pgn->len = 0;
    return pgn;
}

void point_info(Point *p)
{
    if (p)
        printf("(x=%d,y=%d)\n", p->x, p->y);
}

void add_point_to_polygon(Polygon **pgn, Point *p)
{
    int len = (*pgn)->len;
    Point **tmp = realloc((*pgn)->points, (len + 2) * sizeof(Point *));
    if (tmp == NULL) {
        return;
    } else {
        (*pgn)->points = tmp;
    }
    (*pgn)->points[len] = p;
    (*pgn)->points[len+1] = NULL;
    (*pgn)->len += 1;
}

void izobata_init(void)
{
    initscr();
    noecho();
}

void izobata_close(void)
{
    getch();
    endwin();
}

void add_point(Point *p)
{
    move(p->y, p->x);
    printw("#");
}

void output_all(void)
{
    refresh();
}
