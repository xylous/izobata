# API documentation

This file serves more as a rough glossary of all functions defined by `izobata`.
If you want to learn how they're used in practice, check the source files in the
`examples/` directory at the root of this project, e.g.
[rectangle.c](../examples/rectangle.c).

## Initialisation

Every app has to start and has to end at some point. `izobata_init()` and
`izobata_close()` are simple wrappers around ncurses, used to start and close
the session. For the time, they're unconfigurable.

## Data types

There are three simple data types: `Point`s, `Polygon`s, and `Vector`s, of which
the latter you won't be using. Note how every function dealing with data returns
and accepts pointers.

`Point *new_point(int x, int y)` - creates a `Point` at the provided co-ordinates

`Polygon *new_polygon(void)` - allocate space for a `Polygon`. Points are added
by calling the `void add_point_to_polygon(Polygon **pgn, Point *p)` method.

`Vector *new_vector(Point *from, Point *to)` - a `Vector` is defined in terms of
an origin point and a destination point. This way, the direction of the vector
is known, but also its magnitude, expressed as the length of the line segment
between the points. Think of it this way: were the vector applied to the origin,
the result would be the destination point.

## Printing to the screen

You have to initialise izobata before printing anything. Otherwise it won't
work.

The design philosophy was simple: every cell drawn needs to be available and
known to the program using the library. Thus, every function changing something
returns data, the program choosing how to use it.

Since `ncurses` has a "render buffer" of sorts, which is then flushed to the
screen by calling a function, izobata has the same features.

Unfortunately, for the time, points don't have a colour. Instead, when you
render anything to the screen, it prints a plain, monotone `#`.

`void draw_point(Point *p)` - add a point to the render buffer

`void draw_polygon(Polygon *pgn)` - add an entire polygon's points to the render buffer

`void render(void)` - output the render buffer to the screen

`void clearscr(void)` - clear both the render buffer and the screen

## Lines and shapes

You won't hardcode all of a polygon's points, it's too tedious. Instead, it's
far easier to add just the edges/corners and call functions to fill in the
sides.

You might find it funny, but, due to uninspired naming, a simple line between
two points counts as a `Polygon`.

`Polygon *line_points(Point *a, Point *b)` - return all points on the line
between two given points. Internally, it relies on Bresenham's line drawing
algorithm.

`Polygon *polygon_sides(Polygon *pgn)` - return all points obtained by linking
up the edges of the polygon, i.e. its sides.

`Polygon *fill_polygon(Polygon *pgn)` - fill the provided polygon. NOTE: doesn't
work on concave and self-intersecting shapes.

Next, shape-creating functions. Note how every shape has its sides contoured.

`Polygon *rectangle(Point *tl_corner, int length, int height)` - create a
rectangle, provided the location of the top-left corner, its length, and its
height.

`Polygon *triangle(Point *p1, Point *p2, Point *p3)` - create a trinagle

`Polygon *circle(Point *centre, int radius)` - create a circle. Internally, it
uses Bresenham's circle drawing algorithm.

## Polygon maths!

`int point_belongs_to_polygon(Point *p, Polygon *pgn)` - return true (1) if it
does, false (0) if it doesn't

`Polygon *polygon_intersect(Polygon *q, Polygon *t)` - return only the common
points in both polygons

`Polygon *polygon_union(Polygon *q, Polygon *t)` - return the set of all points
in both polygons

`Point *translate_point(Point *p, int dx, int dy)` - move the point by the given
delta x and delta y

`Point *translate_polygon(Polygon *pgn, int dx, int dy)` - move the entire
polygon by the given delta x and delta y

`Vector *rotate_vector(Vector *v, int alpha)` - rotate a vector `v` by `alpha`
degrees (NOT radians!), clockwise. Note how, since integers are used, magnitude
may be lost because of rounding.

`Polygon *rotate_polygon(Polygon *pgn, Point *pivot, int alpha)` - rotate a
polygon around a pivot point, by `alpha` degrees. What's been said about the
above function applies here, too.
