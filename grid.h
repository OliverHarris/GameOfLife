/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 952283
 * @date March, 2020
 */
#pragma once
#include <vector>
#include <ostream>
// Add the minimal number of includes you need in order to declare the class.
// #include ...

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char
{
    DEAD = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid
{
private:
    int height;
    int width;
    std::vector<Cell> grid;
    int get_index(int x, int y) const;

public:
    Grid();
    Grid(int);
    Grid(int x, int y);
    int get_height() const;
    int get_width() const;
    int get_total_cells() const;
    int get_alive_cells() const;
    int get_dead_cells() const;
    void resize(int size);
    void resize(int x, int y);
    Cell get(int x, int y) const;
    void set(int x, int y, Cell value);
    Grid crop(int x0, int y0, int x1, int y1) const;
    void merge(Grid, int x0, int y0, bool alive_only = false);
    Grid rotate(int) const;
    Cell &operator()(int x, int y);
    const Cell &operator()(int x, int y) const;
    friend std::ostream &operator<<(std::ostream &os, const Grid &grid);
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.
};