# izobata

`izobata` is a library for rendering lines and polygons in a terminal, using
ncurses.

The name comes from the French *isobathe*, a term used to denote lines that link
points with the same depth on a map. Think: oceanology.

<!--
## Getting started

### Requirements

(What other software does this project depend on?)

### Installation

(How can anyone get this software running, provided they meet the requirements?)

### Usage

(How is this software used?)
-->

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
