//
// Created by holly on 16/07/24.
//

#ifndef TUNNELFLAGREMAKE_DEBUGFUNCTIONS_H
#define TUNNELFLAGREMAKE_DEBUGFUNCTIONS_H
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include "game/game.h"

// This file is just here to dump functions that would otherwise clutter main.cpp

// Debug functions for testing map ----
short generateRandomValue() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<short> dist(0, 1); // Adjust range as needed
    return dist(gen);
}
void randomizeMapValues(Map& map) {
    for (int row = 0; row < map.getRows(); ++row) {
        for (int col = 0; col < map.getColumns(); ++col) {
            if ((col == 0 || col == map.getColumns() - 1) || (row == 0 || row == map.getRows() - 1)){
                map.setValue(row, col, 1);
            }else{
                map.setValue(row, col, generateRandomValue());
            }
        }
    }
}


#endif //TUNNELFLAGREMAKE_DEBUGFUNCTIONS_H
