#include <cstdio>
#include <new>
#include <algorithm>

#define ROCK 'R'
#define PAPER 'P'
#define SCISSOR 'S'


using namespace std;


void scan_matrix(char** m, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scanf(" %c", &m[i][j]);
        }
    }
}

void print_matrix(char** m, int rows, int columns) {
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            printf("%c", m[i][j]);
        }
        printf("\n");
    }
}

void allocate_matrix(char** &m, int rows, int columns) {
    m = new char* [rows];
    for (int i = 0; i < rows; i++) {
        m[i] = new char[columns];
    }
}

// copy the content of m1 to m2
void copy_matrix(char** &m1, char** &m2, int rows, int columns) {
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++) {
            m2[i][j] = m1[i][j];
        }
    }
}

// returns wether a wins to b
bool win(char a, char b) {
    bool result = false;
    if (a == ROCK && b == SCISSOR) {
        result = true;
    } else if (a == PAPER && b == ROCK) {
        result = true;
    } else if (a == SCISSOR && b == PAPER) {
        result = true;
    }
    return result;
}

// returns if (i,j) is in range.
bool in_range(int i, int j, int rows, int columns) {
    return (i>=0 && i < rows) && (j>=0 && j<columns);
}

void war(char** &today, char** &tomorrow, int rows, int columns) {
    copy_matrix(today, tomorrow, rows, columns);
    int offsets[4][2] { {0,1}, {0,-1}, {1,0}, {-1,0} };
    int pos_i;
    int pos_j;
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            for (auto offset: offsets) {
                pos_i = i + offset[0];
                pos_j = j + offset[1];
                if (in_range(pos_i, pos_j, rows, columns)) {
                    if (win(today[i][j], today[pos_i][pos_j])) {
                        tomorrow[pos_i][pos_j] = today[i][j];
                    }
                }
            }
        }
    }
    swap(today, tomorrow);
}


int main() {
    int tc;  // test cases
    int rows, columns, days;
    scanf("%d", &tc);
    while (tc--) {
        scanf("%d %d %d", &rows, &columns, &days);
        char** today;
        char** tomorrow;
        // allocate matrix
        allocate_matrix(today, rows, columns);
        allocate_matrix(tomorrow, rows, columns);
        // input matrix
        scan_matrix(today, rows, columns);

        while(days--) {
            war(today, tomorrow, rows, columns);
        }

        print_matrix(today, rows, columns);
        // si quedan mas test cases, dejar linea en blanco
        if (tc) {
            printf("\n");
        }

        // deallocate space
        delete[] today;
        delete[] tomorrow;
    }
}
