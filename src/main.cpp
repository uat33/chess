#include <iostream>

#include "../include/game.h"
int main(int argc, char const *argv[]) {
    Game *game = new Game();
    game->startGame();

    delete game;
    return 0;
}
