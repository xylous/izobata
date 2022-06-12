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

/* Draw a rectangle, wait one second, and then translate it by (10,-10) */

int main(void)
{
    izobata_init();

    Point *tl = new_point(23, 41);
    Polygon *rect = rectangle(tl, 3, 6);

    draw_polygon(rect);
    render();

    sleep(1);

    Polygon *translated = translate_polygon(rect, 10, -10);
    draw_polygon(translated);
    render();

    izobata_close();
    return 0;
}
