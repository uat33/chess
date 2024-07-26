// util.h

#ifndef UTIL_H
#define UTIL_H

#include "piece.h"
#include "player.h"
int convertCors(int y, int x);
bool isUnderCheck(int kingY, int kingX, Player *opponent, Piece **grid);
#endif