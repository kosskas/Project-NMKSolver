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
    SECOND_PLAYER_WINS,
};
int** createMap(int n, int m);
void freeMemory(int** arr, int n);
void printMap(int** arr, int n, int m);
void generateAllPositionMoves(int** T, int N, int M, int K, int ActivePlayer);
int countPosMoves(int** T, int N, int M);
void generateAllMovesPrintWin(int** T, int N, int M, int K, int ActivePlayer);
bool checkWinCond(int** T, int N, int M, int K, int ActivePlayer, int y, int x);
int checkMapIfWin(int** T, int N, int M, int K);
bool checkHorizontalAxis(int** T, int N, int M, int K, int y, int x);
bool checkVerticalAxis(int** T, int N, int M, int K, int y, int x);
bool checkVerticalAxis(int** T, int N, int M, int K,  int y, int x);
bool checkObliqueAxis(int** T, int N, int M, int K,  int y, int x);
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //skosy
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
            if (checkMapIfWin(T, N, M, K) == 0) {
                generateAllPositionMoves(T, N, M, K, player);
            }
            else
                cout << 0 << endl;

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

int checkMapIfWin(int** T, int N, int M, int K) {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (checkWinCond(T, N, M, K, FIRST_PLAYER, y, x))
                return FIRST_PLAYER_WINS;
            if (checkWinCond(T, N, M, K, SECOND_PLAYER, y, x))
                return SECOND_PLAYER_WINS;
        }
    }
    return 0;
}
void generateAllPositionMoves(int** T, int N, int M, int K, int ActivePlayer) {
    int pos_moves = countPosMoves(T, N, M);
    cout << pos_moves << endl;
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

bool checkHorizontalAxis(int** T, int N, int M, int K,int y, int x) {
    for (int j = x; j + K - 1 < M; j++) {
        for (int k = 0; k < K; k++) {
            if (T[y][j] != T[y][j+k]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool checkVerticalAxis(int** T, int N, int M, int K, int y, int x) {
    for (int i = y; i + K - 1 < N; i++) { 
        for (int k = 0; k < K; k++) {
            if (T[i][x] != T[i + k][x]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool checkObliqueAxis(int** T, int N, int M, int K, int y, int x) {
    for (int i = y, j = x; i + K - 1 < N && j + K - 1< M; i++, j++) {
        for (int k = 0; k < K; k++) {
            if (T[i][j] != T[i + k][j + k]) {
                return false;
            }
            cout << T[i + k][j + k];
        }
        cout << endl;

        return true;
    }   
    for (int i = y, j = x; i + K - 1< N && j - K + 1 >= 0; i++, j--) {
        for (int k = 0; k < K; k++) {
            if (T[i][j] != T[i + k][j - k]) {
                //return false;
            }
            cout << T[i + k][j - k];
        }
        cout << endl;
        return true;
    }      
    return false;
}

bool checkWinCond(int** T, int N, int M, int K, int ActivePlayer, int y, int x) {
    if (T[y][x] == ActivePlayer)
        return checkHorizontalAxis(T, N, M, K, y, x)
        || checkVerticalAxis(T, N, M, K, y, x)
        || checkObliqueAxis(T, N, M, K, y, x);
    else
        return false;
}