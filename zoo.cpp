/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author 952283
 * @date March, 2020
 */
#include "zoo.h"
#include <fstream>
#include <stdexcept>
// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
Grid Zoo::glider()
{
    Grid g = Grid(3);
    g.set(1, 0, Cell::ALIVE);
    g.set(2, 1, Cell::ALIVE);
    g.set(2, 2, Cell::ALIVE);
    g.set(1, 2, Cell::ALIVE);
    g.set(0, 2, Cell::ALIVE);
    return g;
}
/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */
Grid Zoo::r_pentomino()
{
    Grid g = Grid(3);
    g.set(1, 0, Cell::ALIVE);
    g.set(2, 0, Cell::ALIVE);
    g.set(0, 1, Cell::ALIVE);
    g.set(1, 1, Cell::ALIVE);
    g.set(1, 2, Cell::ALIVE);
    return g;
}
/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 5x4 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */
Grid Zoo::light_weight_spaceship()
{
    Grid g = Grid(5, 4);
    g.set(1, 0, Cell::ALIVE);
    g.set(4, 0, Cell::ALIVE);
    g.set(0, 1, Cell::ALIVE);
    g.set(0, 2, Cell::ALIVE);
    g.set(4, 2, Cell::ALIVE);
    g.set(0, 3, Cell::ALIVE);
    g.set(1, 3, Cell::ALIVE);
    g.set(2, 3, Cell::ALIVE);
    g.set(3, 3, Cell::ALIVE);
    return g;
}
/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */
Grid Zoo::load_ascii(const std::string &path)
{
    std::ifstream file;
    file.open(path, std::ios::in);
    if (!file.is_open())
    {
        throw std::runtime_error("Couldn't open file");
    }
    int width, height;
    int x = 0, y = 0;
    Grid g;
    //First two will be the width and height
    file >> width;
    file >> height;
    if (width < 0 || height < 0)
    {
        file.close();
        throw std::runtime_error("Width or height is negative");
    }
    g = Grid(width, height);
    std::string line;
    getline(file, line);
    char c;
    while (getline(file, line) && y < height)
    {
        int ls = line.size();
        if (ls > width)
        {
            file.close();
            throw std::runtime_error("Line ends unexpectedly");
        }
        while (x < width)
        {
            try
            {
                c = line.at(x);
            }
            catch (const std::out_of_range &ex)
            {
                file.close();
                throw std::runtime_error("Line ends unexpectedly");
            }
            Cell answer;
            if (c == Cell::ALIVE)
            {
                answer = Cell::ALIVE;
            }
            else if (c == Cell::DEAD)
            {
                answer = Cell::DEAD;
            }
            else
            {
                file.close();
                throw std::runtime_error("Unknown character");
            }
            g.set(x, y, answer);
            x++;
        }
        y++;
        x = 0;
    }
    if (y != height)
    {
        file.close();
        throw std::runtime_error("Not enough lines to read");
    }

    file.close();
    return g;
}
/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_ascii(const std::string &path, const Grid &grid)
{
    std::ofstream file;
    file.open(path, std::ios::out);
    if (!file.is_open())
    {
        throw std::runtime_error("Width or height is negative");
    }

    file << grid.get_width() << " " << grid.get_height() << std::endl;
    for (int y = 0; y < grid.get_height(); y++)
    {
        for (int x = 0; x < grid.get_width(); x++)
        {
            file << char(grid.get(x, y));
        }
        file << std::endl;
    }
    file.close();
}
/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */
Grid Zoo::load_binary(const std::string &path)
{
    std::ifstream file;
    file.open(path, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Couldn't open file");
    }
    int width, height;
    file.seekg(0, std::ios::beg); //make sure we're at the start of the file
    file.read((char *)&width, 4);
    file.read((char *)&height, 4);

    Grid g = Grid(width, height);
    int x = 0;
    int y = 0;
    char c;
    int count = 0;
    while (file.get(c))
    {
        if (y < height) //don't read the padding
        {
            for (int i = 0; i < 8; i++)
            {
                if (x >= width)
                {
                    x = 0;
                    y++;
                }
                if (y < height)
                {
                    int answer = ((c >> i) & 1);
                    Cell val;
                    if (answer == 1)
                    {
                        val = Cell::ALIVE;
                    }
                    else
                    {
                        val = Cell::DEAD;
                    }
                    count++;
                    g.set(x, y, val);
                }
                x++;
            }
        }
    }
    if (count != g.get_total_cells())
    {
        file.close();
        throw std::runtime_error("Unexpected end of file");
    }

    file.close();
    return g;
}
/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_binary(const std::string &path, const Grid &grid)
{
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Couldn't open file");
    }
    int width = grid.get_width();
    int height = grid.get_height();

    file.write((char *)&width, 4);
    file.write((char *)&height, 4);
    char *buffer = new char;
    *buffer = 0;

    int size = 0;
    for (int y = 0; y < grid.get_height(); y++)
    {
        for (int x = 0; x < grid.get_width(); x++)
        {
            Cell val = grid.get(x, y);
            int anwr = 0;
            if (val == Cell::ALIVE)
            {
                anwr = 1;
            }

            *buffer |= anwr << size;

            size++;
            if (size > 7)
            {

                //write to file
                file.write(buffer, 1);
                size = 0;

                *buffer = 0; //reset
            }
        }
    }
    if (size > 0)
    {
        //write to file
        file.write(buffer, 1);
    }
    delete buffer;
    file.close();
}