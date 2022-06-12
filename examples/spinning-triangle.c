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
#include <unistd.h>

/* Spinning triangle animation */

#define ROTATE_DEGREES  30
#define SLEEP_MILIS     50

int main(void)
{
    izobata_init();

    /* To not look *completely* horrid, rotate the three points and draw the
     * sides between them */
    Point *p1 = new_point(13, 30);
    Point *p2 = new_point(10, 24);
    Point *p3 = new_point(16, 24);
    Polygon *tri = new_polygon();
    add_point_to_polygon(&tri, p1);
    add_point_to_polygon(&tri, p2);
    add_point_to_polygon(&tri, p3);

    while (1) {
        Polygon *outline = polygon_sides(tri);
        clearscr();
        draw_polygon(outline);
        render();
        usleep(1000 * SLEEP_MILIS);
        tri = rotate_polygon(tri, p1, ROTATE_DEGREES);
    }

    izobata_close();
    return 0;
}
