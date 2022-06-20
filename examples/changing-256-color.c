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
#include <stdio.h>
#include <unistd.h>

/* Render a rectangle which goes through each of the 256 colors every 100ms */

int main(void)
{
    izobata_init();
    if (max_colors() < 256) {
        printf("Sorry, your terminal doesn't support 256 colors\n");
        return 1;
    }

    Point *tl = new_point(10, 20);
    Polygon *rect = fill_polygon(rectangle(tl, 20, 10));

    for (int color = 0; color < 256; color++) {
        clearscr();
        set_polygon_colour(rect, color);
        draw_polygon(rect);
        render();
        usleep(1000 * 100);
    }

    izobata_close();

    return 0;
}
