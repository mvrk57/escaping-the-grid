#include <cstddef>
#include <cassert>

// Feel free to include additional headers here!

#include "MyGrid.hpp"

int checkGrid(MyGrid &grid, size_t rowStart, size_t colStart) {

    assert(grid(rowStart, colStart) == Floor);
    grid(rowStart, colStart) = Path;

    if(rowStart == 0
       || colStart == 0
       || rowStart == grid.rows() - 1
       || colStart == grid.cols() - 1) {

        return 1;
    }

    // look right
    if(grid(rowStart, colStart + 1) == Floor) {
        int currentPathLength = checkGrid(grid, rowStart, colStart + 1);
        if(currentPathLength > 0) {
            return currentPathLength + 1;
        };
    };

    // look left
    if(grid(rowStart, colStart - 1) == Floor) {
        int currentPathLength = checkGrid(grid, rowStart, colStart -1);
        if(currentPathLength > 0) {
            return currentPathLength + 1;
        }
    }

    // look down
    if(grid(rowStart + 1, colStart) == Floor) {
        int currentPath = checkGrid(grid, rowStart + 1, colStart);
        if(currentPath > 0) {
            return currentPath + 1;
        }
    }

    // look up
    if(grid(rowStart - 1, colStart) == Floor) {
        int currentPath = checkGrid(grid, rowStart - 1, colStart);
        if(currentPath > 0) {
            return currentPath + 1;
        };
    }

    // change back current tile if no path to continue found
    grid(rowStart, colStart) = Floor;
    return 0;
}

// Feel free to define auxiliary functions here!
MyGrid escape(MyGrid grid) {
    assert(grid(1,1) == Floor); // Check that the initial tile is valid.

    // TODO implement some path finding algorithm find a correct path to an
    // exit tile, and then write that path to the grid.

    checkGrid(grid, 1, 1);

    // reached escape - print grid
    std::cout << grid;

    return grid;
}

