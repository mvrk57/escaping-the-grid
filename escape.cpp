#include <cstddef>
#include <cassert>
#include "MyGrid.hpp"
#include <tuple>

MyGrid bestSolution = MyGrid();
ssize_t bestSolutionPathLength = -1;

void checkGrid(MyGrid &grid, size_t rowStart, size_t colStart, ssize_t recursionDepth) {

    // there is no shorter path!
    if(recursionDepth >= bestSolutionPathLength && bestSolutionPathLength != -1) return;

    assert(grid(rowStart, colStart) == Floor);
    grid(rowStart, colStart) = Path;

    // if we reach the boarder - return
    if(rowStart == 0
       || colStart == 0
       || rowStart == grid.rows() - 1
       || colStart == grid.cols() - 1) {

        // store best found solution so far
        if(recursionDepth < bestSolutionPathLength || bestSolutionPathLength == -1) {
            bestSolutionPathLength = recursionDepth;
            bestSolution = grid;
        }
        grid(rowStart, colStart) = Floor;
        return;
    }

    // look right
    if(grid(rowStart, colStart + 1) == Floor) {
        checkGrid(grid, rowStart, colStart + 1, recursionDepth + 1);
    };

    // look left
    if(grid(rowStart, colStart - 1) == Floor) {
        checkGrid(grid, rowStart, colStart -1, recursionDepth + 1);
    }

    // look down
    if(grid(rowStart + 1, colStart) == Floor) {
        checkGrid(grid, rowStart + 1, colStart, recursionDepth + 1);
    }

    // look up
    if(grid(rowStart - 1, colStart) == Floor) {
        checkGrid(grid, rowStart - 1, colStart, recursionDepth + 1);
    }

    // change back current tile if no path to continue found
    grid(rowStart, colStart) = Floor;
    return;
}

// Feel free to define auxiliary functions here!
MyGrid escape(MyGrid grid) {
    assert(grid(1,1) == Floor); // Check that the initial tile is valid.

    bestSolutionPathLength = -1;
    checkGrid(grid, 1, 1, 0);

    // reached escape - print grid
    std::cout << bestSolution;

    return bestSolution;
}

