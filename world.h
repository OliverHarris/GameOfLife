/**
 * Declares a class representing a 2d grid world for simulating a cellular automaton.
 * Rich documentation for the api and behaviour the World class can be found in world.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 952283
 * @date March, 2020
 */
#pragma once
#include "grid.h"
// Add the minimal number of includes you need in order to declare the class.
// #include ...

/**
 * Declare the structure of the World class for representing a 2d grid world.
 *
 * A World holds two equally sized Grid objects for the current state and next state.
 *      - These buffers should be swapped using std::swap after each update step.
 */
class World
{
private:
    Grid current;
    Grid next;
    int count_neighbours(const int x, const int y, const bool toroidal);

public:
    World();
    ~World();
    explicit World(const int size);
    World(const int width, const int height);
    World(const Grid &initial_state);
    int get_width() const;
    int get_height() const;
    int get_total_cells() const;
    int get_alive_cells() const;
    int get_dead_cells() const;
    const Grid get_state() const;
    void resize(const int square_size);
    void resize(const int new_width, const int new_height);
    void step(const bool toroidal = false);
    void advance(const int steps, const bool torodial = false);
};