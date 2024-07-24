#include <iostream>

#include "../include/board.h"
int main(int argc, char const *argv[]) {
    Board *b = new Board();

    Color playerturn = Color::WHITE;
    std::string move;
    while (true) {
        b->display(playerturn);

        std::cout << "Enter a move (enter 'resign' to resign): " << std::endl;
        std::cout << "Format `{tile 1}-{tile 2}` (e.g e2-e4)" << std::endl;
        std::getline(std::cin, move);

        if (move == "resign") {
            break;
        }

        int result = b->processMove(move, playerturn);
        if (result == -2) {
            std::cout << "Invalid notation." << std::endl;
            continue;
        }
        if (result == -1) {
            std::cout << "Invalid move." << std::endl;
        }
        if (playerturn == Color::WHITE) {
            playerturn = Color::BLACK;
        } else {
            playerturn = Color::WHITE;
        }
    }

    // TODO: make list valid moves logic for each
    // TODO: check if input is valid move
    // TODO: make logic for check and checkmate
    return 0;
}
