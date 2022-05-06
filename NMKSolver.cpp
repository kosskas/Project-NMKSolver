#include <iostream>
#include <string.h>

using namespace std;

#define checkString(a, b) strcmp(a, b) == 0
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b
#define MAX_CMD_LENGTH 100

enum Position {
    EMPTY,
    FIRST_PLAYER,
    SECOND_PLAYER
};
enum State {
    BOTH_PLAYERS_TIE,
    FIRST_PLAYER_WINS,
    SECOND_PLAYER_WINS
};
int** createMap(int n, int m);
void freeMemory(int** arr, int n);
void printMap(int** arr, int n, int m);
void generateAllPositionMoves(int** T, int N, int M, int K, int ActivePlayer);
int countPosMoves(int** T, int N, int M);
void generateAllMovesPrintWin(int** T, int N, int M, int K, int ActivePlayer);
bool checkWinCond(int** T, int N, int M, int K, int ActivePlayer, int y, int x);
int main() {
    int N = 0, M = 0, K, player;
    int** T = NULL;
    char command[MAX_CMD_LENGTH];
    while (true) {
        cin >> command;
        if (feof(stdin) != 0) {
            break;
        }
        if (checkString(command, "GEN_ALL_POS_MOV")) {
            cin >> N >> M >> K >> player;
            T = createMap(N, M);
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < M; x++) {
                    cin >> T[y][x];
                }
            }
            
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < M; x++) {
                    if(T[y][x] == player)
                        checkWinCond(T, N, M, K, player, y, x);
                }
            }
            
           // generateAllPositionMoves(T, N, M, K, player);

        }
    }
    freeMemory(T, N);
    return 0;
}

//minimax pos gleb maxplayer
int** createMap(int n, int m) {
    int** arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[m];
    }
    return arr;
}

void freeMemory(int** arr, int n) {
    if (arr) {
        for (int i = 0; i < n; i++) {
            if (arr[i])
                delete arr[i];
        }
        delete arr;
    }
}

void printMap(int** arr, int n, int m) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            cout << arr[y][x] << " ";
        }
        cout << endl;
    }
}

int countPosMoves(int** T, int N, int M) {
    int pos_moves = 0;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (T[y][x] == EMPTY)
                pos_moves++;
        }
    }
    return pos_moves;
}

void generateAllPositionMoves(int** T, int N, int M, int K, int ActivePlayer) {
    //sprawdzenie win
    int pos_moves = countPosMoves(T, N, M);
    cout << pos_moves << endl;
    if (pos_moves > 0) {
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < M; x++) {
                if (T[y][x] == EMPTY) {
                    T[y][x] = ActivePlayer;
                    printMap(T, N, M);
                    T[y][x] = EMPTY;
                }
            }
        }
    }
}

void generateAllMovesPrintWin(int** T, int N, int M, int K, int ActivePlayer) {
    int pos_moves = countPosMoves(T, N, M);
    cout << pos_moves << endl;
    if (pos_moves > 0) {
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < M; x++) {
                if (T[y][x] == EMPTY) {
                    T[y][x] = ActivePlayer;
                    printMap(T, N, M);
                    T[y][x] = EMPTY;
                }
            }
        }
    }
}

bool checkWinCond(int** T, int N, int M, int K, int ActivePlayer, int y, int x) {
    //poziom
    bool cond = false;
    cout << "\ndla " << y << " " << x << endl;
    ///wspolny licznik dla pion
    cout << "\nPION w dol\n";
    int k = 0;
    for (int i = y; i < N; i++) {
        if (k == K)
            return true;
        else if (T[y][x] == T[i][x])
            k++;
        else {
            k = 0;
            break;
        }
       // cout << T[i][x] << " ";
    }
   // cout << "\nPION w gore\n";
    for (int i = y; i >= 0; i--) {
        cout << T[i][x] << " ";
    }
    ///wspolny licznik dla poziom
    cout << "\nPOZIOM w prawo\n";
    for (int j = x; j < M; j++) {
        cout << T[y][j] << " ";
    }
    cout << "\nPOZIOM w lewo\n";
    for (int j = x; j >= 0; j--) {
        cout << T[y][j] << " ";
    }
    
    cout <<"\nSKOS W PRAWODOL"<< endl;
    for (int i = y, j = x; i < N && j < M; i++, j++) {  
        cout << T[i][j] << " ";
    }
    cout <<"\nSKOS W LEWOGORA"<< endl;
    for (int i = y, j = x; i >=0  && j >= 0; i--, j--) {

        cout << T[i][j] << " ";
    }

    cout << "\nSKOS W PRAWOGORA" << endl;
    for (int i = y, j = x; i >=0 && j < M; i--, j++) {
        cout << T[i][j] << " ";
    }
    cout << "\nSKOS W LEWODOL" << endl;
    for (int i = y, j = x; i < N && j >=0; i++, j--) {

        cout << T[i][j] << " ";
    }
    return false;
}