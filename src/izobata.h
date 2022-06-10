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

/**
 * Representation of a point at (x,y)
 */
typedef struct Point {
    int x;
    int y;
} Point;

extern Point *new_point(int x, int y);

/* For simplicity: a polygon is just a set of points */
typedef struct Polygon {
    Point **points;
    int len;
} Polygon;

extern Polygon *new_polygon(void);
extern void add_point_to_polygon(Polygon **pgn, Point *p);

/* Get a list of points on the given line */
extern Polygon *line_points(Point *a, Point *b);

/* Add all points in the polygon to the render buffer */
extern void draw_polygon(Polygon *pgn);

/* Link all points in a polygon, line-by-line */
extern void draw_polygon_sides(Polygon *pgn);

/* Initialise ncurses */
extern void izobata_init(void);
/* Close ncurses */
extern void izobata_close(void);

/* Add a point to the buffer */
extern void add_point(Point *p);
/* For debugging only: print the co-ordinates of a point to stdout */
extern void point_info(Point *p);
/* Put everything in the buffer on the screen */
extern void output_all(void);

#endif
