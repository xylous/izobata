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

/* Draw a filled triangle: initially white, then cyan, then red */

int main(void)
{
    izobata_init();

    Point *p1 = new_point(20, 30);
    Point *p2 = new_point(30, 20);
    Point *p3 = new_point(15, 15);
    Polygon *tri = triangle(p1, p2, p3);
    Polygon *filled = fill_polygon(tri);

    draw_polygon(filled);
    render();

    sleep(1);

    set_polygon_colour(filled, COLOR_CYAN);
    draw_polygon(filled);
    render();

    sleep(1);

    set_polygon_colour(filled, COLOR_RED);
    draw_polygon(filled);
    render();

    izobata_close();
    return 0;
}
