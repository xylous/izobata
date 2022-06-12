# izobata

`izobata` is a library for rendering lines and polygons in a terminal, using
ncurses.

The name comes from the French *isobathe*, a term used to denote lines that link
points with the same depth on a map. Think: oceanology.

## Getting started

### Requirements

For building:

- GNU Make
- GCC

For running:

- ncurses

### Installation

Right now you can only install it manually. I'll get to making a package for
this library when it's in a more refined state.

Get the repository on your local system, `cd` into it, and run `make library`:

```
git clone https://github.com/xylous/izobata izobata
cd izobata
make library
```

If you want to look at programs using this libraries, check out the `examples/`
directory. You can run `make examples` to build all of them. They're put into
the `bin/` directory. Execute them to try them out!

If you run `make` with no targets, it would build both the library and the
examples.

The library file, `libizobata.a`, is statically linked. For now, you'll have to
copy both it and the header file (`src/izobata.h`) into your project, for
example:

```
mkdir -p myproject/include
cp /path/to/izobata/libizobata.a /path/to/izobata/src/izobata.h myproject/include
```

If you're in the project root directory, you'll have to compile with `gcc ...
-L./include -lizobata`. Yes, it's fairly tedious to get it up and running, just
because I haven't yet got to packaging it.

## Roadmap

- [x] initialise and close (ncurses) session, + clear screen
- [x] draw individual points
- [x] implement Bresenham algorithm for line rendering
- [x] create polygons with N sides
- [x] provide shortcuts for triangles, rectangles, circles
- [x] fill in polygons
    - [x] convex
    - [ ] concave
    - [ ] self-intersecting
- [x] translate points and polygons
- [x] rotate shapes by a certain number of degrees

## Contributing

Pull requests are welcome. For major changes, please open an issue first to
discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[GPLv3](./LICENSE)
