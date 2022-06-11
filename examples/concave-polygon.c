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

/* Try filling in a concave polygon */

int main(void)
{
    Point *p1 = new_point(1, 1);
    Point *p2 = new_point(1, 6);
    Point *p3 = new_point(11, 6);
    Point *p4 = new_point(6, 1);
    Point *p5 = new_point(6, 4);
    Polygon *pgn = new_polygon();
    add_point_to_polygon(&pgn, p1);
    add_point_to_polygon(&pgn, p2);
    add_point_to_polygon(&pgn, p3);
    add_point_to_polygon(&pgn, p4);
    add_point_to_polygon(&pgn, p5);

    izobata_init();

    /*draw_polygon(polygon_sides(pgn));*/
    draw_polygon(fill_polygon(pgn));
    output_all();

    izobata_close();

    return 0;
}
