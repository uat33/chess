#include "game.h"

Game::Game() {
    board = new Board(true);
}

Game::~Game() {
    delete board;
}

static void displayClone(Board *b, Color c) {
    b->display(c);
}
void Game::startGame() {
    std::string move;

    std::vector<string> moves = {
        "e2-e4", "d7-d5", "e4-d5", "d8-d5", "a2-a3", "d5-e4", "g1-f3", "e1-e2",
        "f1-e2", "a7-a6", "g1-f3", "a6-a5", "e1-h1", "b8-c6", "f1-e1", "c8-g4",
        "e2-b5", "e8-a8", "e1-e4", "g4-f3", "b2-b4", "g8-f6", "b4-a5", "h7-h6",
        "a5-a6", "h6-h5", "a6-a7", "h5-h4", "a7-a8"};
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
        boardCopy = board->clone();

        int res = processMove(move);
        if (res == -2 || res == -3) {
            delete board;
            board = boardCopy;
            continue;
        }
        delete boardCopy;
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
