/*
 * Battleship, classic battleship game
 * Copyright (C) 2014-2015 Pavel Dolgov
 *
 * See the LICENSE file for terms of use.
 */

#ifndef GET_SHIP_COORDINATES_HPP_
#define GET_SHIP_COORDINATES_HPP_

#include "Point.hpp"
#include "Exception.hpp"

// This function is static.
// Retunrns true if the neighbor is ship's item.
// Save neighbor's coordinate to p.
template<typename T>
bool nextNeighbor(Point& out, const T& desk,
                  Point p,
                  int player_number, bool direction) {
    if (direction) {
        if (p.row != desk.getWidth() - 1) {
            out.row = p.row + 1;
            out.col = p.col;
            if (desk.getCellState(p, player_number)) {
                return true;
            }
        } else if (p.col != 0) {
            out.col = p.col - 1;
            out.row = p.row;
            if (desk.getCellState(p, player_number)) {
                return true;
            }
        }
    } else {
        if (p.row != 0) {
            out.row = p.row - 1;
            out.col = p.col;
            if (desk.getCellState(p, player_number)) {
                return true;
            }
        } else if (p.col != desk.getLength() - 1) {
            out.col = p.col + 1;
            out.row = p.row;
            if (desk.getCellState(p, player_number)) {
                return true;
            }
        }
    }
    return false;
}

/** Get coordinates of ship. */
template<typename T>
Points getShipCoordinates(const T& desk, const Point& p,
                         int player_number) {
    Points out;
    out.p1 = p;
    out.p2 = p;
    while (nextNeighbor<T>(out.p1, desk, out.p1,
                           player_number, false)) {
    }
    while (nextNeighbor<T>(out.p2, desk, out.p2,
                           player_number, true)) {
    }
    return out;
}

#endif
