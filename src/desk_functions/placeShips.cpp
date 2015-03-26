/*
 * Battleship, classic battleship game
 * Copyright (C) 2014-2015 Pavel Dolgov
 *
 * See the LICENSE file for terms of use.
 */

#include <cstdlib>

#include "Exception.hpp"
#include "placeShips.hpp"
#include "spaceForShip.hpp"

static bool getOneHalf() {
    return rand() <= (RAND_MAX / 2);
}

static Points findPlace(const GameDesk& desk,
                        int player, int length) {
    int square = desk.getWidth() * desk.getLength();
    int attempts = square * 10;
    for (int i = 0; i < attempts; i++) {
        bool horizontal = getOneHalf();
        int col1, col2, row1, row2;
        if (horizontal) {
            col1 = rand() % desk.getLength();
            col2 = col1;
            row1 = rand() % (desk.getWidth() - length);
            row2 = row1 + length - 1;
        } else {
            col1 = rand() % (desk.getLength() - length);
            col2 = col1 + length - 1;
            row1 = rand() % desk.getWidth();
            row2 = row1;
        }
        try {
            Points ship(Point(col1, row1),
                        Point(col2, row2));
            spaceForShip(desk, ship, player);
            return ship;
        } catch (...) {
        }
    }
    throw Exception("");
}

static void tryPlaceShips(GameController& controller,
                          const GameDesk& desk,
                          int player) {
    // length is ship_length
    for (int length = 5; length >= 2; length--) {
        for (int n = 0; n < 6 - length; n++) {
            Points ship = findPlace(desk, player, length);
            controller.setShip(player, ship);
        }
    }
}

void placeShips(GameController& controller,
                const GameDesk& desk, int player) {
    while (true) {
        try {
            tryPlaceShips(controller, desk, player);
            break;
        } catch (...) {
            controller.initialStateOfBoard();
        }
    }
}
