/*
 * Battleship, classic battleship game
 * Copyright (C) 2014-2015 Pavel Dolgov
 *
 * See the LICENSE file for terms of use.
 */

#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <vector>
#include <cstdlib>

/** Return random number from interval [0, end).
\param end End of interval (not included)
*/
unsigned int random(unsigned int end);

unsigned int randomWithUnequalChances(std::vector<int>&
                                      chances);

#endif
