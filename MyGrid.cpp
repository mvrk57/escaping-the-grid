#include "MyGrid.hpp"
#include <utility>
#include <cassert>
#include <algorithm>

// TODO Define all member functions:


// helping links:
// https://stackoverflow.com/questions/41087485/how-to-divide-class-in-c-into-hpp-and-cpp-files

// Default Constructor

// Constructor
MyGrid::MyGrid(size_t rows, size_t cols, const Tile &initialTile) {
    numberOfRows = rows;
    numberOfCols = cols;
    myGrid = new Tile*[rows];

    if(cols == 0 && rows == 0) {
        myGrid[rows] = new Tile[0];
    }

    for (size_t i = 0; i < rows; ++i) {
        myGrid[i] = new Tile[cols];
        // each i-th pointer is now pointing to dynamic array (size cols)
        // of actual Tile values
    }

    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            myGrid[row][col] = initialTile;
        }
    }
}


// Copy Constructor
// https://en.cppreference.com/w/cpp/language/copy_constructor
MyGrid::MyGrid(const MyGrid &other) {
    *this = other;
}


// Move Constructor
// https://en.cppreference.com/w/cpp/language/move_constructor
MyGrid::MyGrid(MyGrid &&other) noexcept {
    *this = std::move(other);
}

//// Destructor
//MyGrid::~MyGrid() {}


// Move Assignment Operator
MyGrid& MyGrid::operator=(MyGrid &&other) noexcept {

    if (&other == this)
        return *this;

    numberOfRows = other.numberOfRows;
    numberOfCols = other.numberOfCols;
    myGrid = other.myGrid;

    other.myGrid = nullptr;

    return *this;
}


// Copy Assignment Operator
// https://en.cppreference.com/w/cpp/language/copy_constructor
MyGrid& MyGrid::operator=(const MyGrid &other) {
    numberOfRows = other.numberOfRows;
    numberOfCols = other.numberOfCols;
    myGrid = other.myGrid;
    return *this;
}

// methods:

size_t MyGrid::rows() const { return numberOfRows; }

size_t MyGrid::cols() const { return numberOfCols; }

size_t MyGrid::size() const { return numberOfRows * numberOfCols; }


[[nodiscard]] bool MyGrid::validPosition(size_t row, size_t col) const noexcept {
    // ich glaube ich soll einfach prüfen ob das quasi ne outOfBoundException wirft
    // mit Hilfe meiner () operatoren
    return (myGrid[row][col] == Floor);
}

Tile& MyGrid::operator()(size_t row, size_t col) {
    return myGrid[row][col];
}

const Tile& MyGrid::operator()(size_t row, size_t col) const {
    return myGrid[row][col];
}

MyGrid MyGrid::read(std::istream &in) {

    size_t cols;
    size_t rows;
    char initialTileChar;

    in >> cols;
    in >> rows;
    in >> initialTileChar;

    return MyGrid(cols, rows, tile_from_char(initialTileChar));
}

std::ostream& operator<<(std::ostream &out, const MyGrid& grid) {
    return out << grid.myGrid;
}