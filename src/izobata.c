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
#include <math.h>

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

/* Return 1 if the given point belongs to the polygon, and 0 if it doesn't */
int point_belongs_to_polygon(Point *p, Polygon *pgn)
{
    for (int i = 0; i < pgn->len; i++) {
        if (p->x == pgn->points[i]->x && p->y == pgn->points[i]->y) {
            return 1;
        }
    }
    return 0;
}

/**
 * Bruteforce. Not a good approach, but it works.
 */
Polygon *polygon_intersect(Polygon *q, Polygon *t)
{
    Polygon *pgn = new_polygon();
    for (int i = 0; i < q->len; i++) {
        if (point_belongs_to_polygon(q->points[i], t)) {
            add_point_to_polygon(&pgn, q->points[i]);
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

/* Brutely compute the eight next points in the outline of the circle */
Polygon *circle_layer(Point *c, int x, int y)
{
    Polygon *layer = new_polygon();
    Point *p1 = new_point(c->x + x, c->y + y);
    Point *p2 = new_point(c->x - x, c->y + y);
    Point *p3 = new_point(c->x + x, c->y - y);
    Point *p4 = new_point(c->x - x, c->y - y);
    Point *p5 = new_point(c->x + y, c->y + x);
    Point *p6 = new_point(c->x - y, c->y + x);
    Point *p7 = new_point(c->x + y, c->y - x);
    Point *p8 = new_point(c->x - y, c->y - x);

    add_point_to_polygon(&layer, p1);
    add_point_to_polygon(&layer, p2);
    add_point_to_polygon(&layer, p3);
    add_point_to_polygon(&layer, p4);
    add_point_to_polygon(&layer, p5);
    add_point_to_polygon(&layer, p6);
    add_point_to_polygon(&layer, p7);
    add_point_to_polygon(&layer, p8);

    return layer;
}

/* Unfortunately it doesn't look like a circle, because of the terminal width
 * and height. */
Polygon *circle(Point *c, int r)
{
    int d = 3 - 2 * r;
    int x = 0;
    int y = r;
    Polygon *circ = new_polygon();

    while (x <= y) {
        Polygon *layer = circle_layer(c, x, y);
        circ = polygon_union(circ, layer);

        x++;

        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }

    return circ;
}

Polygon *line_edges(Polygon *line)
{
    Polygon *edges = new_polygon();
    Point *last = line->points[0];

    /* The first point in the line is always an edge */
    add_point_to_polygon(&edges, line->points[0]);
    /* A point is an edge if there's a gap between it and the next one; but this
     * also means the next one is an edge, too */
    for (int i = 0; i < line->len - 1; i++) {
        if (line->points[i+1]->x != line->points[i]->x + 1) {
            if (line->points[i] != last) {
                add_point_to_polygon(&edges, line->points[i]);
            }
            add_point_to_polygon(&edges, line->points[i+1]);
            last = line->points[i+1];
        }
    }
    /* The last point is always an edge */
    add_point_to_polygon(&edges, line->points[line->len-1]);

    return edges;
}

/* Implement scanline algorithm for filling in a polygon */
Polygon *fill_polygon(Polygon *pgn)
{
    Polygon *filled = new_polygon();

    int ymin, ymax = 0;
    int xmin, xmax = 0;

    getmaxyx(stdscr, ymin, xmin);

    for (int i = 0; i < pgn->len; i++) {
        if (pgn->points[i]->y > ymax) {
            ymax = pgn->points[i]->y;
        } else if (ymin > pgn->points[i]->y) {
            ymin = pgn->points[i]->y;
        }
        if (pgn->points[i]->x > xmax) {
            xmax = pgn->points[i]->x;
        } else if (xmin > pgn->points[i]->x) {
            xmin = pgn->points[i]->x;
        }
    }

    /* Scan every line and get the intersections. Add everything in-between
     * them, including the points that were intersected. */
    for (int y = ymax; y >= ymin; y--) {
        Point *start = new_point(xmin, y);
        Point *end = new_point(xmax, y);
        Polygon *line = line_points(start, end);
        Polygon *intersections = polygon_intersect(line, pgn);
        Polygon *scanline = line_edges(intersections);

        int parity = 1;
        for (int i = 0; i < scanline->len - 1; i++) {
            /* Don't falsely switch parity on consecutive points */
            if (scanline->points[i]->x + 1 == scanline->points[i+1]->x) {
                parity = 1;
            }
            if (parity == 0) {
                parity = 1;
            } else {
                for (int x = scanline->points[i]->x; x <= scanline->points[i+1]->x; x++) {
                    Point *p = new_point(x, y);
                    add_point_to_polygon(&filled, p);
                }
                parity = 0;
            }
        }
        /* Some edges might have a single point. Don't miss it */
        if (scanline->len == 1) {
            Point *p = new_point(scanline->points[0]->x, y);
            add_point_to_polygon(&filled, p);
        }
    }

    return filled;
}

Point *translate_point(Point *p, int dx, int dy)
{
    return new_point(p->x + dx, p->y + dy);
}

Polygon *translate_polygon(Polygon *pgn, int dx, int dy)
{
    Polygon *translated = new_polygon();
    for (int i = 0; i < pgn->len; i++) {
        add_point_to_polygon(&translated, translate_point(pgn->points[i], dx, dy));
    }
    return translated;
}

Vector *new_vector(Point *from, Point *to)
{
    Vector *v = calloc(1, sizeof(Vector));
    v->from = from;
    v->to = to;
    return v;
}

Vector *rotate_vector(Vector *v, int alpha)
{
    /* sin() and cos() assume the angle is in radians */
    double pi = acos(-1);
    double angle = (double) alpha / 180.0 * pi;

    int dx = v->from->x;
    int dy = v->from->y;
    int x = v->to->x - dx;
    int y = v->to->y - dy;

    /* other than that, it's just maths */
    int xnew = dx + x * cos(angle) - y * sin(angle);
    int ynew = dy + x * sin(angle) + y * cos(angle);

    Point *new = new_point(xnew, ynew);
    Vector *nv = new_vector(v->from, new);

    return nv;
}
