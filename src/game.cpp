#include "game.h"

Game::Game() {
    board = new Board(true);
}

Game::~Game() {
    delete board;
}

bool checkmate(Board *b, Color turn) {
    Player *current;
    Player *opposition;
    if (turn == Color::BLACK) {
        current = b->getBlackPlayer();
        opposition = b->getWhitePlayer();
    } else {
        opposition = b->getBlackPlayer();
        current = b->getWhitePlayer();
    }

    if (!opposition->getUnderCheck()) return false;
    // check that opposition has a move that lifts check

    Piece **pieces = opposition->getPieces();
    for (int i = 0; i < 16; i++) {
        if (pieces[i] == nullptr) continue;
        std::vector<std::vector<int>> p1 =
            pieces[i]->listValidMoves(b->getGrid());

        for (int j = 0; j < p1.size(); j++) {
            Board *boardCopy = b->clone();

            Player *currentCopy;
            Player *oppCopy;
            if (turn == Color::BLACK) {
                currentCopy = boardCopy->getBlackPlayer();
                oppCopy = boardCopy->getWhitePlayer();
            } else {
                oppCopy = boardCopy->getBlackPlayer();
                currentCopy = boardCopy->getWhitePlayer();
            }

            Piece *p = oppCopy->getPieces()[i];
            Piece **grid = boardCopy->getGrid();
            int y = p1[j][0];
            int x = p1[j][1];

            p->makeMove(y, x, grid);
            if (!oppCopy->isUnderCheck(boardCopy->getGrid(), currentCopy)) {
                boardCopy->display(turn);
                // delete b;
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
    std::vector<std::string> moves = {
        "e2-e4", "d7-d5", "g1-f3", "d8-d6", "f1-b5", "c7-c6",
        "e1-h1", "g8-f6", "c2-c4", "g7-g5", "c4-c5", "f8-h6",
        "c5-d6", "h8-g8", "b1-c3", "g8-h8", "a2-a3", "e8-h8"};
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
