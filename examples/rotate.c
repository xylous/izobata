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

/* Draw a triangle, wait one second, rotate it 180 degrees relative to its
 * bottom point */

int main(void)
{
    izobata_init();

    Point *p1 = new_point(13, 15);
    Point *p2 = new_point(10, 12);
    Point *p3 = new_point(16, 12);
    Polygon *tri = triangle(p1, p2, p3);

    draw_polygon(tri);
    render();

    sleep(1);
    clearscr();

    Polygon *rotated = rotate_polygon(tri, p1, 180);
    draw_polygon(rotated);
    render();

    izobata_close();
    return 0;
}
