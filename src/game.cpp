#include "game.h"

Game::Game() {
    board = new Board(true);
}

Game::~Game() {
    delete board;
}

void Game::startGame() {
    string move;
    std::vector<string> moves = {"c2-c3", "f7-f6", "e2-e3", "g7-g5", "d1-h5"};
    int index = 0;
    while (true) {
        displayBoard();
        std::cout << "Enter a move (enter 'resign' to resign): " << std::endl;
        std::cout << "Format `{tile 1}-{tile 2}` (e.g e2-e4)" << std::endl;

        if (index < moves.size()) {
            move = moves[index++];
        } else {
            std::getline(std::cin, move);
        }

        if (move == "resign") {
            break;
        }
        // clone the board so it can be reverted
        boardCopy = board->clone();

        int res = processMove(move);
        if (res == -2 || res == -3) {
            // delete the board with the move (which is invalid)
            delete board;
            // revert it
            board = boardCopy;
            continue;
        }
        // otherwise delete the copy
        // check if game over
        displayBoard();

        delete boardCopy;
        // this checks if it was invalid for any reason that doesn't require a
        // reversion in which case, no action is necessary as the move wouldn't
        // have been made
        if (res != 0) continue;

        if (playerturn == Color::WHITE) {
            playerturn = Color::BLACK;
        } else {
            playerturn = Color::WHITE;
        }
    }
}

void Game::displayBoard() const {
    board->display(playerturn);
}

int Game::processMove(const string &move) {
    int result = board->processMove(move, playerturn);

    if (result == -5) {
        std::cout << "Invalid notation." << std::endl;
    } else if (result == -4) {
        std::cout << "Invalid move. You don't have a piece there." << std::endl;
    } else if (result == -3) {
        std::cout << "Invalid move. King is under check." << std::endl;
    } else if (result == -2) {
        std::cout << "Invalid move. King would be in check." << std::endl;
    } else if (result == -1) {
        std::cout << "Invalid move." << std::endl;
    }

    return result;
}
