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
 * Create a moving ball of given radius. If it collides with the edges of the
 * terminal, it bounces.
 */

#include "../src/izobata.h"
#include <curses.h>
#include <unistd.h>

#define FRAME_DURATION_MILIS    300
#define BALL_RADIUS     3

int main(void)
{
    izobata_init();
    Point *c = new_point(40, 20);

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int xmod = 1, ymod = 1;
    while (1) {
        Polygon *circ = circle(c, BALL_RADIUS);
        add_point_to_polygon(&circ, c);

        clearscr();
        draw_polygon(circ);
        output_all();

        /* Switch the direction if we collide with the edge */
        if (c->x == BALL_RADIUS || c->x == cols - BALL_RADIUS) {
            xmod *= -1;
        }
        if (c->y == BALL_RADIUS || c->y == rows - BALL_RADIUS) {
            ymod *= -1;
        }
        c->x += xmod;
        c->y += ymod;
        usleep(100 * FRAME_DURATION_MILIS);
    }

    izobata_close();
    return 0;
}
