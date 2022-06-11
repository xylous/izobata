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

/**
 * Render a moving triangle. At the end, all points have moved and it becomes a
 * right triangle.
 */

#include "../src/izobata.h"
#include <unistd.h>

int main(void)
{
    izobata_init();

    Point *p1 = new_point(2, 4);
    Point *p2 = new_point(20, 10);
    Point *p3 = new_point(8, 29);
    Polygon *pgn = new_polygon();
    add_point_to_polygon(&pgn, p1);
    add_point_to_polygon(&pgn, p2);
    add_point_to_polygon(&pgn, p3);

    for (int i = 0; i < 38; i++) {
        clearscr();
        draw_polygon(polygon_sides(pgn));
        output_all();
        p1->x++;
        if (i % 2 == 0) {
            p1->y++;
            p3->y--;
            p2->x++;
        }
        usleep(1000 * 200);
    }

    izobata_close();
    return 0;
}
