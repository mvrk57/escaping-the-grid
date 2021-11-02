#include "MyGrid.hpp"
#include <utility>
#include <cassert>
#include <algorithm>

// TODO Define all member functions:


// helping links:
// https://stackoverflow.com/questions/41087485/how-to-divide-class-in-c-into-hpp-and-cpp-files

// Default Constructor

//Constructor
MyGrid::MyGrid(size_t rows, size_t cols, const Tile &initialTile) {
    numberOfRows = rows;
    numberOfCols = cols;
    myGrid[numberOfRows][numberOfCols] = initialTile;
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


// Copy Assignment Operator
// https://en.cppreference.com/w/cpp/language/copy_constructor
MyGrid& MyGrid::operator=(const MyGrid &other) {
    this->numberOfRows = other.numberOfRows;
    this->numberOfCols = other.numberOfCols;
    this->myGrid = other.myGrid;
    return *this;
}

// methods:

size_t MyGrid::rows() const { return numberOfRows; }

size_t MyGrid::cols() const { return numberOfCols; }

size_t MyGrid::size() const { return numberOfRows * numberOfCols; }


[[nodiscard]] bool MyGrid::validPosition(size_t row, size_t col) const noexcept {
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
