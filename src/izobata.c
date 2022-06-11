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
#include <string.h>
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

/**
 * Use the Bresenham algorithm to get all points on a line
 *
 * Inspiration: https://github.com/SagarGaniga/computer-graphics/
 */
Polygon *line_points(Point *a, Point *b)
{
    Polygon *line = new_polygon();

    int dx = b->x - a->x;
    int dy = b->y - a->y;

    /* determine the direction we're going on the axes: positive or negative? */
    int sx = (dx >= 0) ? 1 : (-1);
    int sy = (dy >= 0) ? 1 : (-1);

    /* Swap X and Y axes for better performance */
    int swapped = 0;
    if (abs(dy) > abs(dx)) {
        int tdx = dx;
        dx = dy;
        dy = tdx;

        swapped = 1;
    }

    int p = 2 * abs(dy) - abs(dx);
    int x = a->x;
    int y = a->y;

    for (int i = 0; i <= abs(dx); i++) {
        Point *point = new_point(x, y);
        add_point_to_polygon(&line, point);

        if (p < 0) {
            if (!swapped) {
                x += sx;
            } else {
                y += sy;
            }
        } else {
            x += sx;
            y += sy;
            p -= 2 * abs(dx);
        }
        p += 2 * abs(dy);
    }

    return line;
}

void draw_polygon(Polygon *pgn)
{
    for (int i = 0; i < pgn->len; i++) {
        add_point(pgn->points[i]);
    }
}

Polygon *polygon_sides(Polygon *pgn)
{
    Polygon *t = new_polygon();
    /* Unite the current side and the next one */
    /* Note how it doesn't work for pgn->len = 1, i.e. a single point */
    for (int i = 0; i < pgn->len - 1; i++) {
        Polygon *line = line_points(pgn->points[i], pgn->points[i+1]);
        t = polygon_union(polygon_union(t, pgn), line);
    }
    /* Unite the first and last side */
    if (pgn->len > 2) {
        Polygon *line = line_points(pgn->points[0], pgn->points[pgn->len-1]);
        t = polygon_union(polygon_union(t, pgn), line);
    }
    return t;
}

/**
 * Bruteforce. Not a good approach, but it works.
 */
Polygon *polygon_intersect(Polygon *q, Polygon *t)
{
    Polygon *pgn = new_polygon();
    for (int i = 0; i < q->len; i++) {
        for (int j = 0; j < t->len; j++) {
            if (q->points[i] == t->points[j]) {
                add_point_to_polygon(&pgn, q->points[i]);
            }
        }
    }
    return pgn;
}

/**
 * Use memcpy, don't just iterate over everything
 */
Polygon *polygon_union(Polygon *q, Polygon *t)
{
    Polygon *pgn = new_polygon();
    pgn->len = q->len + t->len;
    Point **tmp = realloc(pgn->points, (pgn->len + 1) * sizeof(Point *));
    if (tmp == NULL) {
        return pgn;
    } else {
        pgn->points = tmp;
    }
    memcpy(pgn->points, q->points, q->len * sizeof(Point *));
    memcpy(pgn->points + q->len, t->points, t->len * sizeof(Point *));
    return pgn;
}

void clearscr(void)
{
    clear();
}

Polygon *rectangle(Point *tl_corner, int length, int height)
{
    Polygon *rectangle = new_polygon();
    int tl_x = tl_corner->x;
    int tl_y = tl_corner->y;

    Point *p1 = new_point(tl_x + length, tl_y);
    Point *p2 = new_point(tl_x + length, tl_y + height);
    Point *p3 = new_point(tl_x, tl_y + height);
    add_point_to_polygon(&rectangle, tl_corner);
    add_point_to_polygon(&rectangle, p1);
    add_point_to_polygon(&rectangle, p2);
    add_point_to_polygon(&rectangle, p3);

    return polygon_sides(rectangle);
}

Polygon *triangle(Point *p1, Point *p2, Point *p3)
{
    Polygon *triangle = new_polygon();

    add_point_to_polygon(&triangle, p1);
    add_point_to_polygon(&triangle, p2);
    add_point_to_polygon(&triangle, p3);

    return polygon_sides(triangle);
}
