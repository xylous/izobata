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

#include "izobata.h"
#include <stdlib.h>
#include <ncurses.h>

Point *new_point(int x, int y)
{
    Point *v = calloc(1, sizeof(Point));
    v->x = x;
    v->y = y;
    return v;
}

void izobata_init(void)
{
    initscr();
    noecho();
}

void izobata_close(void)
{
    getch();
    endwin();
}
