#include <iostream>
#include <string.h>

using namespace std;

typedef unsigned char byte_t;
#define checkString(a, b) strcmp(a, b) == 0
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b
#define MAX_CMD_LENGTH 100

enum Position {
    EMPTY = '0',
    FIRST_PLAYER = '1',
    SECOND_PLAYER = '2'
};
enum State {
    BOTH_PLAYERS_TIE,
    FIRST_PLAYER_WINS,
    SECOND_PLAYER_WINS,
};
byte_t** createMap(int n, int m);
void freeMemory(byte_t** arr, int n);
void printMap(byte_t** arr, int n, int m);
bool checkWinCond(byte_t** T, int N, int M, int K, char ActivePlayer);
bool checkHorizontalAxis(byte_t** T, int N, int M, int K, char ActivePlayer);
bool checkVerticalAxis(byte_t** T, int N, int M, int K, char ActivePlayer);
bool checkVerticalAxis(byte_t** T, int N, int M, int K, char ActivePlayer);
bool checkDiagonalsAxis(byte_t** T, int N, int M, int K, char ActivePlayer);
bool checkAntiDiagonalsAxis(byte_t** T, int N, int M, int K, char ActivePlayer);
void generateAllPositionMoves(byte_t** T, int N, int M, int K, char ActivePlayer);
int countPosMoves(byte_t** T, int N, int M);
void generateAllPositionMovesCutIfWin(byte_t** T, int N, int M, int K, char ActivePlayer);
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N = 0, M = 0, K;
    byte_t player;
    byte_t** T = NULL;
    char command[MAX_CMD_LENGTH];
    while (true) {
        cin >> command;
        if (feof(stdin) != 0) {
            break;
        }
        else if (checkString(command, "GEN_ALL_POS_MOV")) {
            cin >> N >> M >> K >> player;
            T = createMap(N, M);
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < M; x++) {
                    cin >> T[y][x];
                }
            } 
            generateAllPositionMoves(T, N, M, K, player);          
            freeMemory(T, N);
        }
        else if (checkString(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER")) {
            cin >> N >> M >> K >> player;
            T = createMap(N, M);
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < M; x++) {
                    cin >> T[y][x];
                }
            }
            generateAllPositionMovesCutIfWin(T, N, M, K, player);        
            freeMemory(T, N);
        }
    }  
    return 0;
}

//minimax pos gleb maxplayer
byte_t** createMap(int n, int m) {
    byte_t** arr = new byte_t *[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new byte_t[m];
    }
    return arr;
}

void freeMemory(byte_t** arr, int n) {
    if (arr) {
        for (int i = 0; i < n; i++) {
            if (arr[i]) {
                delete[] arr[i];
            }
        }
        delete[] arr;
    }
}

void printMap(byte_t** arr, int n, int m) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            cout << arr[y][x] << " ";
        }
        cout << endl;
    }
}

bool checkWinCond(byte_t** T, int N, int M, int K, char ActivePlayer) {
    return checkHorizontalAxis(T, N, M, K, ActivePlayer)
        || checkVerticalAxis(T, N, M, K, ActivePlayer)
        || checkDiagonalsAxis(T, N, M, K, ActivePlayer)
        || checkAntiDiagonalsAxis(T, N, M, K, ActivePlayer);
}
//poziom
bool checkHorizontalAxis(byte_t** T, int N, int M, int K, char ActivePlayer) {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x + K - 1 < M; x++) {
            if (T[y][x] == ActivePlayer) {
                int k = 0;
                for (k = 0; k < K; k++) {
                    if (T[y][x] != T[y][x + k]) {
                        break;
                    }
                    
                }
                if(k == K)
                    return true;
            }
        }
    }
    return false;
}
//pion
bool checkVerticalAxis(byte_t** T, int N, int M, int K, char ActivePlayer) {
    for (int y = 0; y + K - 1 < N; y++) {
        for (int x = 0; x < M; x++) {
            if (T[y][x] == ActivePlayer) {
                int k = 0;
                for (k = 0; k < K; k++) {
                    if (T[y][x] != T[y + k][x]) {
                        break;
                    }
                }
                if(k == K)
                    return true;
            }
        }
    }
    return false;
}

bool checkDiagonalsAxis(byte_t** T, int N, int M, int K, char ActivePlayer) {
    for (int y = 0; y + K - 1 < N; y++) {
        for (int x = 0; x + K - 1 < M; x++) {
            if (T[y][x] == ActivePlayer) {
                int k = 0;
                for (k = 0; k < K; k++) {
                    if (T[y][x] != T[y + k][x + k]) {
                        break;
                    }
                }
                if(k == K)
                    return true;
            }
        }
    }
    return false;
}

bool checkAntiDiagonalsAxis(byte_t** T, int N, int M, int K, char ActivePlayer) {
    for (int y = 0; y + K - 1 < N; y++) {
        for (int x = M - 1; x - K + 1 >= 0; x--) {
            if (T[y][x] == ActivePlayer) {
                int k = 0;
                for (k = 0; k < K; k++) {
                    if (T[y][x] != T[y + k][x - k]) {
                        break;
                    }
                }
                if(k == K)
                    return true;
            }
        }
    }
    return false;
}

int countPosMoves(byte_t** T, int N, int M) {
    int pos_moves = 0;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (T[y][x] == EMPTY)
                pos_moves++;
        }
    }
    return pos_moves;
}

void generateAllPositionMoves(byte_t** T, int N, int M, int K, char ActivePlayer) {
    if (checkWinCond(T, N, M, K, FIRST_PLAYER) || checkWinCond(T, N, M, K, SECOND_PLAYER)) {
        cout << 0 << endl;
        return;
    }
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

void generateAllPositionMovesCutIfWin(byte_t** T, int N, int M, int K, char ActivePlayer) {
    if (checkWinCond(T, N, M, K, FIRST_PLAYER) || checkWinCond(T, N, M, K, SECOND_PLAYER)) {
        cout << 0 << endl;
        return;
    }
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (T[y][x] == EMPTY) {
                T[y][x] = ActivePlayer;
                if (checkWinCond(T, N, M, K, ActivePlayer)) {
                    cout << 1<<endl;
                    printMap(T, N, M);
                    return;
                }
                T[y][x] = EMPTY;
            }
        }
    }
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
