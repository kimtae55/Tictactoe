#include <iostream>

using namespace std;

// constants
#define ROW_SIZE 5
#define COL_SIZE 5

#define BLACK_TURN true
#define WHITE_TURN false

#define PIECE_EMPTY '.'
#define PIECE_BLACK '@'
#define PIECE_WHITE 'O'

#define WIN_NUM_PIECES 3

// prototype
void initBoard(char board[][COL_SIZE], int rowSize, int colSize);
void printBoard(char board[][COL_SIZE], int rowSize, int colSize);
bool validate(char board[][COL_SIZE], int rowSize, int colSize, int row, int col);
bool winCheck(char board[][COL_SIZE], int rowSize, int colSize, int row, int col);
int countLine(char board[][COL_SIZE], int rowSize, int colSize, int row, int col, int rowDir, int colDir);

int main() {

    char board[ROW_SIZE][COL_SIZE];
    
    initBoard(board, ROW_SIZE, COL_SIZE);
    printBoard(board, ROW_SIZE, COL_SIZE);
    cout << endl;
    
    int row = -1;
    int col = -1;
    bool turn = BLACK_TURN;
    
    // main (game) loop
    while (true) { // infinite loop
        
        // get the coord from the user.
        while (true) {
            // show the user a prompt to get the row index.
            cout << ((turn == BLACK_TURN)?"BLACK:":"WHITE:") << "row    : ";
            cin >> row;
            // show the user a prompt to get the column index.
            cout << ((turn == BLACK_TURN)?"BLACK:":"WHITE:") << "column : ";
            cin >> col;
            
            // validate the given coord
            if (validate(board, ROW_SIZE, COL_SIZE, row, col)) {
                break;
            }
            cout << endl << "error: not valid! try again!!!" << endl << endl;
        }
        
        board[row][col] = (turn == BLACK_TURN)?PIECE_BLACK:PIECE_WHITE;

        cout << endl;
        printBoard(board, ROW_SIZE, COL_SIZE);
        
        if (winCheck(board, ROW_SIZE, COL_SIZE, row, col)) {
            cout << "You won!" << endl;
            break;
        }
        
        turn = !turn;
    }
    cout << "Bye!" << endl;
    
    return 0;
}

bool winCheck(char board[][COL_SIZE], int rowSize, int colSize, int row, int col) {
    int dir[2][4] = {
        {0, -1, -1, -1}, // rowDirs
        {-1, 0, -1, 1}   // colDirs
    };
    // check all dirs
    for (int i = 0; i < 4; i++) {
        if (countLine(board, rowSize, colSize, row, col, dir[0][i], dir[1][i]) == WIN_NUM_PIECES) {
            return true;
        }
    }
    return false;

    /*
    int dir[2][4] = {{0, -1, -1, -1},{-1, 0, -1, 1}};
    // check all dirs
    for (int i = 0; i < 4; i++) {
        if (countLine(board, rowSize, colSize, row, col, dir[0][i], dir[1][i]) == WIN_NUM_PIECES) {
            return true;
        }
    }
    return false;
     */
}

int countLine(char board[][COL_SIZE], int rowSize, int colSize, int row, int col, int rowDir, int colDir) {
    int count = 1;
    
    for (int i = 0; i < 2; i++) {
        int curRow = row+rowDir;
        int curCol = col+colDir;
        while (true) { // a dir
            if (curRow < 0 || curRow >= rowSize || curCol < 0 || curCol >= colSize ||
                board[curRow][curCol] != board[row][col]) {
                break;
            }
            count++;
            curRow = curRow+rowDir;
            curCol = curCol+colDir;
        }
        rowDir = rowDir * -1;
        colDir = colDir * -1;
    }

    return count;
}

bool validate(char board[][COL_SIZE], int rowSize, int colSize, int row, int col) {
    return row >= 0 && row < ROW_SIZE && col >= 0 && col < COL_SIZE &&
        board[row][col] == PIECE_EMPTY;
}

void initBoard(char board[][COL_SIZE], int rowSize, int colSize) {
    // init the board.
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            board[i][j] = '.';
        }
    }
}

void printBoard(char board[][COL_SIZE], int rowSize, int colSize) {
    cout << "  ";
    for (int j = 0; j < colSize; j++) {
        cout << j;
    }
    cout << endl;

    cout << " +";
    for (int j = 0; j < colSize; j++) {
        cout << "-";
    }
    cout << "+" << endl;

    // print the board.
    for (int i = 0; i < rowSize; i++) {
        cout << i << "|";
        for (int j = 0; j < colSize; j++) {
            cout << board[i][j];
        }
        cout << "|" << i << endl;
    }

    cout << " +";
    for (int j = 0; j < colSize; j++) {
        cout << "-";
    }
    cout << "+" << endl;

    cout << "  ";
    for (int j = 0; j < colSize; j++) {
        cout << j;
    }
    cout << endl;
    
}
