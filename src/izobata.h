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

#ifndef IZOBATA_H
#define IZOBATA_H

/* Initialise ncurses */
extern void izobata_init(void);
/* Close ncurses */
extern void izobata_close(void);
/* Clear both the screen and the render buffer */
extern void clearscr(void);

/* Representation of a point at (x,y) */
typedef struct Point {
    int x;
    int y;
} Point;

/* For simplicity: a polygon is just a set of points */
typedef struct Polygon {
    Point **points;
    int len;
} Polygon;

/**
 * A Vector is represented as an origin point and a destination point. This is
 * its direction; its magnitude is determined by the distance between these two
 * points.
 */
typedef struct Vector {
    Point *from;
    Point *to;
} Vector;

extern Point *new_point(int x, int y);
extern Polygon *new_polygon(void);
extern Vector *new_vector(Point *from, Point *to);

/* Add a point to the buffer */
extern void add_point(Point *p);
/* Add all points in the polygon to the render buffer */
extern void draw_polygon(Polygon *pgn);
/* Put everything in the buffer on the screen */
extern void output_all(void);

extern void add_point_to_polygon(Polygon **pgn, Point *p);

/* Get a list of points on the given line */
extern Polygon *line_points(Point *a, Point *b);

/* Link all points in a polygon, line-by-line */
extern Polygon *polygon_sides(Polygon *pgn);

/* Return the set of points that are common to both polygons */
extern Polygon *polygon_intersect(Polygon *q, Polygon *t);
/* Return all points in both polygons */
extern Polygon *polygon_union(Polygon *q, Polygon *t);

/**
 * Return the outline of a rectangle, knowing its top left corner, its length
 * and its height
 */
extern Polygon *rectangle(Point *tl_corner, int length, int height);
extern Polygon *triangle(Point *p1, Point *p2, Point *p3);
extern Polygon *circle(Point *centre, int radius);

/* Return the set of all points that are inside the polygon */
extern Polygon *fill_polygon(Polygon *pgn);

/* Move the given point by delta x and delta y */
extern Point *translate_point(Point *p, int dx, int dy);
/* Move an entire polygon by delta x and delta y */
extern Polygon *translate_polygon(Polygon *pgn, int dx, int dy);

/* Rotate a vector clockwise RELATIVE TO ITS ORIGIN POINT */
extern Vector *rotate_vector(Vector *v, int alpha);

/* Rotate a polygon around a pivot point */
extern Polygon *rotate_polygon(Polygon *pgn, Point *pivot, int alpha);

#endif
