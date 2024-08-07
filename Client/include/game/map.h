//
// Created by holly on 24/03/24.
//

#ifndef MAP_H
#define MAP_H
#include <vector>


class Map {
    int rows;
    int columns;
    int tileSize = 15;
    std::vector<std::vector<short>> map;

    bool isValidPosition(int row, int column) const;

public:

    Map(int rows, int columns);

    void setValue(int row, int column, short value);
    [[nodiscard]] short getValue(int row, int column) const;

    int getRows() const;
    int getColumns() const;
    int getTileSize() const;
    [[nodiscard]] const std::vector<std::vector<short>> &getMap() const;

    void setRows(int rows);
    void setColumns(int columns);
    void setTileSize(int tileSize);
};



#endif //MAP_H
