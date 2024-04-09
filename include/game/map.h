//
// Created by holly on 24/03/24.
//

#ifndef MAP_H
#define MAP_H
#include <vector>


class Map {
    int rows;
    int columns;

    bool isValidPosition(int row, int column) const;

public:
    std::vector<std::vector<short>> map;

    Map(int rows, int columns);

    void setValue(int row, int column, short value);
    [[nodiscard]] short getValue(int row, int column) const;

    int getRows();
    int getColumns();
    void setRows(int rows);
    void setColumns(int columns);
};



#endif //MAP_H
