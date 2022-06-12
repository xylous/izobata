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

#include "../src/izobata.h"

/* Draw a square in the top-left corner of the screen */

int main(void)
{
    izobata_init();
    Point *p1 = new_point(0, 0);
    Point *p2 = new_point(10, 0);
    Point *p3 = new_point(10, 10);
    Point *p4 = new_point(0, 10);
    Point *p5 = new_point(10, 20);
    Point *p6 = new_point(0, 20);

    Polygon *pgn1 = new_polygon();
    Polygon *pgn2 = new_polygon();
    add_point_to_polygon(&pgn1, p1);
    add_point_to_polygon(&pgn1, p2);
    add_point_to_polygon(&pgn1, p3);
    add_point_to_polygon(&pgn1, p4);
    add_point_to_polygon(&pgn2, p3);
    add_point_to_polygon(&pgn2, p4);
    add_point_to_polygon(&pgn2, p5);
    add_point_to_polygon(&pgn2, p6);

    Polygon *shape = polygon_union(polygon_sides(pgn2), polygon_sides(pgn1));
    draw_polygon(shape);
    render();

    izobata_close();

    return 0;
}
