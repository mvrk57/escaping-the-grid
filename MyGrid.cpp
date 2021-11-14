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

    // fill is not working with unique_ptr so use loop
    // std::fill(myGrid[0][0], myGrid[rows][cols], &initialTile);

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

    other.numberOfRows = 0;
    other.numberOfCols = 0;
    other.myGrid = nullptr;

    return *this;
}


// Copy Assignment Operator
// https://en.cppreference.com/w/cpp/language/copy_constructor
MyGrid& MyGrid::operator=(const MyGrid &other) {

    if(this == &other) {
        return *this;
    }

    numberOfRows = other.numberOfRows;
    numberOfCols = other.numberOfCols;
    myGrid = new Tile*[numberOfRows];

    if(numberOfRows == 0 && numberOfCols == 0) {
        myGrid[numberOfRows] = new Tile[0];
    }

    for (size_t i = 0; i < numberOfRows; ++i) {
        myGrid[i] = new Tile[numberOfCols];
        // each i-th pointer is now pointing to dynamic array (size cols)
        // of actual Tile values
    }

    for(size_t row = 0; row < numberOfRows; row ++) {
        for(size_t col = 0; col < numberOfCols; col ++) {
            myGrid[row][col] = other(row, col);
        }
    }

    return *this;
}

// methods:

size_t MyGrid::rows() const { return numberOfRows; }

size_t MyGrid::cols() const { return numberOfCols; }

size_t MyGrid::size() const { return numberOfRows * numberOfCols; }


[[nodiscard]] bool MyGrid::validPosition(size_t row, size_t col) const noexcept {
    return row < numberOfRows && col < numberOfCols;
}

Tile& MyGrid::operator()(size_t row, size_t col) {

    if (validPosition(row, col)) return myGrid[row][col];
    throw std::out_of_range("index is out of range");

}

const Tile& MyGrid::operator()(size_t row, size_t col) const {
    return myGrid[row][col];
}

MyGrid MyGrid::read(std::istream &in) {

    size_t rows, cols;
    std::string lineTiles;

    in >> rows >> cols;

    MyGrid myGrid = MyGrid(rows, cols, Wall);

    for(size_t row = 0; row < rows; row ++){
        in >> lineTiles;
        for (size_t col = 0; col < cols; col++) {
            myGrid(row, col) = tile_from_char(lineTiles[col]);
        }

    }

    return myGrid;
}

std::ostream& operator<<(std::ostream &out, const MyGrid& grid) {
    out << grid.numberOfRows << "\n" << grid.numberOfCols << "\n";

    for(size_t i = 0; i < grid.numberOfRows; i++) {
        for(size_t j = 0; j < grid.numberOfCols; j++) {
            out << char_from_tile(grid.myGrid[i][j]);
        }
        out << "\n";
    }

    return out;
}