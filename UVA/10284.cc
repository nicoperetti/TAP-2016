#define ALL(v) v.begin(), v.end()
#define BOARD_N 8
#define NOT_ATTACKED '0'
#define ATTACKED '1'
#define FEN_DELIM '/'
#define toDigit(c) c - '0'
#define BLACK 'b'
#define WHITE 'w'

#include <cstdio>
#include <array>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

array<array<char, BOARD_N>, BOARD_N> fen_to_board(string fen) {
    array<array<char, BOARD_N>, BOARD_N> board;
    // Initialize board, not attacked
    for (int i=0; i < BOARD_N; i++) {
        for (int j=0; j < BOARD_N; j++) {
            board[i][j] = NOT_ATTACKED;
        }
    }

    // Fen to array of rows
    array<string, 8> fen_array;
    stringstream ss(fen);
    string item;
    for (int i=0; i < BOARD_N; i++) {
        getline(ss, item, FEN_DELIM);
        fen_array[i] = item;
    }

    // Fen to board
    int board_row = 0;
    int board_column = 0;
    for(string& row: fen_array) {
        for(char& c: row) {
            if (isdigit(c)) {
                int blank = toDigit(c);
                board_column += blank;
            } else {
                board[board_row][board_column] = c;
                board_column++;
            }
        }
        board_column = 0;
        board_row++;
    }
    return board;
}

bool empty_square(char square) {
    return (isdigit(square));
}

bool in_range(int i, int j) {
    return (i >= 0 && i < BOARD_N) && (j >= 0 && j < BOARD_N);
}

bool inside_and_empty(array<array<char, BOARD_N>, BOARD_N> &board, int i, int j) {
    bool result = false;
    if (in_range(i,j)) {
        result = empty_square(board[i][j]);
    }
    return result;
}

void attack_vertical(array<array<char, BOARD_N>, BOARD_N> &board, int i, int j) {
    int pos_i;
    int pos_j = j;
    int offsets[2] = {-1, 1};
    for (auto offset: offsets) {
        pos_i = i + offset;
        while (inside_and_empty(board, pos_i, pos_j)) {
            board[pos_i][pos_j] = ATTACKED;
            pos_i += offset;
        }
    }
}

void attack_horizontal(array<array<char, BOARD_N>, BOARD_N> &board, int i, int j) {
    int pos_i = i;
    int pos_j;
    int offsets[2] = {-1 , 1};
    for (auto offset: offsets) {
        pos_j = j + offset;
        while (inside_and_empty(board, pos_i, pos_j)) {
            board[pos_i][pos_j] = ATTACKED;
            pos_j += offset;
        }
    }
}

void attack_diagonal(array<array<char, BOARD_N>, BOARD_N> &board, int i, int j) {
    int pos_i;
    int pos_j;
    int offsets[4][2] = { {1,1}, {-1,1}, {1, -1}, {-1,-1} };
    for (auto offset: offsets) {
        pos_i = i + offset[0];
        pos_j = j + offset[1];
        while (inside_and_empty(board, pos_i, pos_j)) {
            board[pos_i][pos_j] = ATTACKED;
            pos_i += offset[0];
            pos_j += offset[1];
        }
    }
}

void rook_attack(array<array<char, BOARD_N>, BOARD_N> &board, int i, int j) {
    attack_vertical(board, i, j);
    attack_horizontal(board, i, j);
}

void knight_attack(array<array<char, BOARD_N>, BOARD_N> &board, int i, int j) {
    array<int, 2> despl = {1,2};
    int offsets[4][2] = { {1,1}, {-1, 1}, {1, -1}, {-1, -1} };
    int pos_i, pos_j;
    do {
        for (auto offset: offsets) {
            pos_i = i + despl[0] * offset[0];
            pos_j = j + despl[1] * offset[1];
            if (inside_and_empty(board, pos_i, pos_j)) {
                board[pos_i][pos_j] = ATTACKED;
            }
        }
    } while (next_permutation(ALL(despl)));
}

void bishop_attack(array<array<char, BOARD_N>, BOARD_N> &board, int i, int j) {
    attack_diagonal(board, i, j);
}

void queen_attack(array<array<char, BOARD_N>, BOARD_N> &board, int i, int j) {
    attack_vertical(board, i, j);
    attack_horizontal(board, i, j);
    attack_diagonal(board, i, j);

}

void king_attack(array<array<char, BOARD_N>, BOARD_N> &board, int i, int j) {
    int pos_i, pos_j;
    for (int offset_i =- 1; offset_i <= 1; offset_i++) {
        for (int offset_j = -1; offset_j <= 1; offset_j++) {
            pos_i = i + offset_i;
            pos_j = j + offset_j;
            if (inside_and_empty(board, pos_i, pos_j)) {
                board[pos_i][pos_j] = ATTACKED;
            }
        }
    }
}

void pawn_attack(array<array<char, BOARD_N>, BOARD_N> &board, int i, int j, char color) {
    int direction = 1;  // 1 is for black, -1 for white.
    if (color == WHITE) {
        direction = -1;
    }
    int pos_i = i + direction;
    int pos_j;
    int offsets[2] = {1, -1};
    // one diagonal on x+offset, y+direction
    for (auto offset: offsets) {
        pos_j = j + offset;
        if (inside_and_empty(board, pos_i, pos_j)) {
            board[pos_i][pos_j] = ATTACKED;
        }
    }
}

void attacked_board(array<array<char, BOARD_N>, BOARD_N> &board) {
    char square;
    for (int i=0; i<BOARD_N; i++) {
        for (int j=0; j<BOARD_N; j++) {
            square = board[i][j];
            if (!empty_square(square)) {
                switch (square) {
                    case 'r':
                    case 'R':
                        rook_attack(board, i, j);
                        break;
                    case 'n':
                    case 'N':
                        knight_attack(board, i, j);
                        break;
                    case 'b':
                    case 'B':
                        bishop_attack(board, i, j);
                        break;
                    case 'q':
                    case 'Q':
                        queen_attack(board, i, j);
                        break;
                    case 'k':
                    case 'K':
                        king_attack(board, i, j);
                        break;
                    case 'p':
                        pawn_attack(board, i, j, BLACK);
                        break;
                    case 'P':
                        pawn_attack(board, i, j, WHITE);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void print_board(array<array<char, BOARD_N>, BOARD_N> &board) {
    for (auto row: board) {
        for (char& c: row) {
            printf("%c ", c);
        }
        printf("\n");
    }
}

int main() {
    char f[100];  // 100 is enough. 8*8 + 7 = 71 is max.
    string fen;  // f to string.
    array<array<char, BOARD_N>, BOARD_N> board;
    int not_attacked_squares;
    while(scanf("%s", f) != EOF) {
        not_attacked_squares = 0;
        fen = string(f);
        board = fen_to_board(fen);
        attacked_board(board);
        for (int i=0; i < BOARD_N; i++) {
            for (int j=0; j < BOARD_N; j++) {
                if (board[i][j] == NOT_ATTACKED) {
                    not_attacked_squares++;
                }
            }
        }
        printf("%d\n", not_attacked_squares);
    }
}

