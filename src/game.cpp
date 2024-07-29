#include "game.h"

Game::Game() {
    board = new Board(true);
}

Game::~Game() {
    delete board;
}

static bool checkmate(Board *b, Color turn) {
    Color oppositeColor;
    Player *opposition;
    if (turn == Color::BLACK) {
        opposition = b->getWhitePlayer();
        oppositeColor = Color::WHITE;
    } else {
        opposition = b->getBlackPlayer();
        oppositeColor = Color::BLACK;
    }
    // cannot be checkmated if you are not under check
    if (!opposition->getUnderCheck()) return false;

    // check that opposition has a move that lifts check
    Piece **pieces = opposition->getPieces();
    for (int i = 0; i < NUMPIECES; i++) {
        if (pieces[i] == nullptr) continue;
        std::vector<std::vector<int>> validMoves =
            pieces[i]->listValidMoves(b->getGrid());

        for (const auto &validMove : validMoves) {
            Board *boardCopy = b->clone();

            Player *oppCopy;
            if (turn == Color::BLACK) {
                oppCopy = boardCopy->getWhitePlayer();
            } else {
                oppCopy = boardCopy->getBlackPlayer();
            }

            Piece *p = oppCopy->getPieces()[i];
            int y = validMove[0];
            int x = validMove[1];
            boardCopy->makeMove(p->getY(), p->getX(), y, x, oppositeColor);
            if (!oppCopy->getUnderCheck()) {
                delete boardCopy;
                return false;
            }
            delete boardCopy;
        }
    }
    // delete b;
    return true;
}

void Game::startGame() {
    string move;

    int index = 0;
    while (true) {
        displayBoard();
        std::cout << "Enter a move (enter 'resign' to resign): " << std::endl;
        std::cout << "Format `{tile 1}-{tile 2}` (e.g e2-e4)" << std::endl;

        std::getline(std::cin, move);

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
        delete boardCopy;

        // check if game over
        // clone again to get the new move
        boardCopy = board->clone();
        bool over = checkmate(boardCopy, playerturn);
        if (over) {
            displayBoard();
            std::cout << "Checkmate." << std::endl;
            std::cout << (playerturn == Color::BLACK ? "Black " : "White ")
                      << "wins." << std::endl;
            delete boardCopy;
            break;
        }
        delete boardCopy;
        // this checks if it was invalid for any reason that doesn't require a
        // reversion in which case, no action is necessary as the move wouldn't
        // have been made
        if (res != 0) continue;

        // valid move so switch whose turn it is
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
