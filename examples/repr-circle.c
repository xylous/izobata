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
#include <stdio.h>

/* Draw a filled circle and change its representation character and re-render
 * several times */

int main(void)
{
    izobata_init();

    Point *c = new_point(20, 20);
    Polygon *circ = circle(c, 5);
    Polygon *filled = fill_polygon(circ);

    draw_polygon(filled);
    render();
    sleep(1);

    set_polygon_repr(filled, 'c');
    draw_polygon(filled);
    render();
    sleep(1);

    set_polygon_repr(filled, '@');
    draw_polygon(filled);
    render();
    sleep(1);

    izobata_close();
    return 0;
}
