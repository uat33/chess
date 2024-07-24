#include "../include/board.h"

Board::Board() {
    white = new Player(Color::WHITE);
    black = new Player(Color::BLACK);

    Piece **whitePieces = white->getPieces();
    Piece **blackPieces = black->getPieces();

    int y, x, index;
    for (int i = 0; i < NUMPIECES; i++) {
        y = whitePieces[i]->getY();
        x = whitePieces[i]->getX();
        index = convertCors(y, x);
        grid[index] = whitePieces[i];

        y = blackPieces[i]->getY();
        x = blackPieces[i]->getX();
        index = convertCors(y, x);
        grid[index] = blackPieces[i];
    }

    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            int index = convertCors(i, j);
            grid[index] = nullptr;
        }
    }
}

Board::~Board() {
    delete white;
    delete black;
}

static void printHorizontalLine() {
    int length = 32;
    std::cout << "   ";
    for (int i = 0; i < length; ++i) {
        std::cout << "\u2500";  // Unicode character for horizontal line (─)
    }
    std::cout << std::endl;
}

void Board::display(Color playerturn) const {
    if (playerturn == Color::WHITE) {
        printHorizontalLine();
        for (int i = 0; i < DIMENSION; i++) {
            std::cout << 8 - i << " |";
            for (int j = 0; j < DIMENSION; j++) {
                int index = convertCors(i, j);

                if (grid[index] == nullptr) {
                    std::cout << "   |";
                } else {
                    grid[index]->display(grid[index]->getColor());
                }
            }
            std::cout << std::endl;
            printHorizontalLine();
        }
        std::cout << "    a   b   c   d   e   f   g   h" << std::endl;

    } else {
        printHorizontalLine();
        for (int i = DIMENSION - 1; i >= 0; i--) {
            std::cout << 8 - i << " |";
            for (int j = DIMENSION - 1; j >= 0; j--) {
                int index = convertCors(i, j);

                if (grid[index] == nullptr) {
                    std::cout << "   |";
                } else {
                    grid[index]->display(grid[index]->getColor());
                }
            }
            std::cout << std::endl;
            printHorizontalLine();
        }
        std::cout << "    h   g   f   e   d   c   b   a" << std::endl;
    }
}

int Board::processMove(const string &s, Color playerturn) {
    if (s.length() != 5) return -2;
    if (s[2] != '-') return -2;
    char file1 = std::tolower(s[0]);
    char file2 = std::tolower(s[3]);
    char row1 = s[1];
    char row2 = s[4];
    if (file1 < 'a' || file1 > 'h') return -2;
    if (file2 < 'a' || file2 > 'h') return -2;
    if (row1 < '1' || row1 > '8') return -2;
    if (row2 < '1' || row2 > '8') return -2;

    int y1 = 8 - (row1 - '0');
    int x1 = file1 - 'a';
    int y2 = 8 - (row2 - '0');
    int x2 = file2 - 'a';

    std::cout << y1 << " " << x1 << " " << y2 << " " << x2 << std::endl;
    int index = convertCors(y1, x1);
    bool res = grid[index]->movePiece(y2, x2, grid);
    if (!res) return -1;
    return 0;
}
