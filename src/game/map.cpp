//
// Created by holly on 24/03/24.
//

#include "map.h"
#include <iostream>

extern bool debugOutput;
Map::Map(const int rows, const int columns) : rows(rows), columns(columns) {
    map.resize(rows, std::vector<short>(columns, 0));
}

bool Map::isValidPosition(const int row, const int column) const {
    return row >= 0 && row < rows && column >= 0 && column < columns;
}

short Map::getValue(const int row, const int column) const {
    if (isValidPosition(row, column)) {
        return map[row][column];
    }return -1;
}
void Map::setValue(int row, int column, short value) {
    if (isValidPosition(row, column)) {
        map[row][column] = value;
    } else if (debugOutput) {
        {std::cout << "Attempt to access map tile outside of map\n";}
    }
}


int Map::getColumns() {return columns;}
int Map::getRows() {return rows;}

void Map::setColumns(int columns) {this->columns = columns;}
void Map::setRows(int rows) {this->rows = rows;}





