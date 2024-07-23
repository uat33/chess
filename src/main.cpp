#include <iostream>

#include "../include/board.h"
int main(int argc, char const *argv[]) {
    Board *b = new Board();
    b->display();

    Color playerturn = Color::WHITE;
    std::string move;
    while (true) {
        std::cout << "Enter a move (enter 'resign' to resign): ";
        std::getline(std::cin, move);

        if (move == "resign") {
            break;
        }

        // Process or use the input as needed
        std::cout << "You entered: " << move << std::endl;

        if (playerturn == Color::WHITE) {
            playerturn = Color::WHITE;
        } else {
            playerturn = Color::BLACK;
        }
    }

    // TODO: make list valid moves logic for each
    // TODO: check if input is valid move
    // TODO: make logic for check and checkmate
    return 0;
}
