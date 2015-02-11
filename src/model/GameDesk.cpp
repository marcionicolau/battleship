/*
 * Battleship, classic battleship game
 * Copyright (C) 2014-2015 Pavel Dolgov
 *
 * See the LICENSE file for terms of use.
 */

#include "GameDesk.hpp"

/* get global coordinate from horizontal and
   vertical coordinates
*/
static int getIndex(const Point& point, int width) {
    bool less = ((point.col < 0) || (point.row < 0));
    bool greater = ((point.col >= length_) || (poit.row >=
                     width_));
    if (less || greater) {
        throw Exception("Model: index of cell in some "
                        "argument's of GameDesk's methods "
                        "is out of range.");
    }
    int index = point.col * width + point.row;
    return index;
}

void GameDesk::setCellState(const Point& point,
                            bool state,
                            int player_number) {
    int index = getIndex(point, width_);
    if (player_number == 1) {
        player1_desk_[index].is_ship = state;
    } else if (player_number == 2) {
        player2_desk_[index].is_ship = state;
    } else {
        throw Exception("Received invalid player_number "
                        "argument in setCellState method "
                        "of GameDesk. It must be 1 or 2.");
    }
}

bool GameDesk::getCellState(const Point& point,
                            int player_number) const {
    int index = getIndex(point, width_);
    if (player_number == 1) {
        return player1_desk_[index].is_ship;
    } else if (player_number == 2) {
        return player2_desk_[index].is_ship;
    } else {
        throw Exception("Received invalid player_number "
                        "argument in getCellState method "
                        "of GameDesk. It must be 1 or 2.");
    }
}

void GameDesk::setFlooding(const Point& point,
                           bool is_sunken,
                           int player_number) {
    int index = getIndex(point, width_);
    if (player_number == 1) {
        player1_desk_[index].is_sunken_ship = is_sunken;
    } else if (player_number == 2) {
        player2_desk_[index].is_sunken_ship = is_sunken;
    } else {
        throw Exception("Received invalid player_number "
                        "argument in setFlooding method "
                        "of GameDesk. It must be 1 or 2.");
    }
}

bool GameDesk::getFlooding(const Point& point,
                           int player_number) const {
    int index = getIndex(point, width_);
    if (player_number == 1) {
        return player1_desk_[index].is_sunken_ship;
    } else if (player_number == 2) {
        return player2_desk_[index].is_sunken_ship;
    } else {
        throw Exception("Received invalid player_number "
                        "argument in getFlooding method "
                        "of GameDesk. It must be 1 or 2.");
    }
}

void GameDesk::setVisibility(const Point& point,
                             bool is_visible,
                             int player_number) {
    int index = getIndex(point, width_);
    if (player_number == 1) {
        player1_desk_[index].is_visible = is_visible;
    } else if (player_number == 2) {
        player2_desk_[index].is_visible = is_visible;
    } else {
        throw Exception("Received invalid player_number "
                        "argument in setVisibility method "
                        "of GameDesk. It must be 1 or 2.");
    }
}

bool GameDesk::getVisibility(const Point& point,
                             int player_number) const {
    int index = getIndex(point, width_);
    if (player_number == 1) {
        return player1_desk_[index].is_visible;
    } else if (player_number == 2) {
        return player2_desk_[index].is_visible;
    } else {
        throw Exception("Received invalid player_number "
                        "argument in getVisibility method "
                        "of GameDesk. It must be 1 or 2.");
    }
}

void GameDesk::resize(int width, int length) {
    const int min_width = 8;
    const int max_width = 20;
    const int min_length = 8;
    const int max_length = 20;
    if ((width < min_width) || (width > max_width)) {
        throw Exception("width of desk is out of "
                        "allowable range");
    } else if ((length < min_length) || (length >
                max_length)) {
        throw Exception("length of desk is out of "
                        "allowable range");
    }
    int square = width * length;
    player1_desk_.resize(square);
    player2_desk_.resize(square);
    width_ = width;
    length_ = length;
}

int GameDesk::getWidth() const {
    return width_;
}

int GameDesk::getLength() const {
    return length_;
}
