#include <iostream>
#include <string.h>

using namespace std;

typedef unsigned char byte_t;

#define checkString(a, b) (strcmp(a, b) == 0)
#define MAX_CMD_LENGTH 100
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

enum Position {
    EMPTY = '0',
    FIRST_PLAYER = '1',
    SECOND_PLAYER = '2'
};

enum Result {
    LOSE = -1,
    TIE = 0,
    WIN = 1,
};

byte_t** createMap(int n, int m);
void freeMemory(byte_t** map, int n);
void printMap(byte_t** map, int n, int m);
bool checkWinCond(byte_t** map, int N, int M, int K, byte_t ActivePlayer);
bool checkHorizontalAxis(byte_t** map, int N, int M, int K, byte_t ActivePlayer);
bool checkVerticalAxis(byte_t** map, int N, int M, int K, byte_t ActivePlayer);
bool checkVerticalAxis(byte_t** map, int N, int M, int K, byte_t ActivePlayer);
bool checkDiagonalsAxis(byte_t** map, int N, int M, int K, byte_t ActivePlayer);
bool checkAntiDiagonalsAxis(byte_t** map, int N, int M, int K, byte_t ActivePlayer);
void generateAllPositionMoves(byte_t** map, int N, int M, int K, byte_t ActivePlayer);
int countPosMoves(byte_t** map, int N, int M);
void generateAllPositionMovesCutIfWin(byte_t** map, int N, int M, int K, byte_t ActivePlayer);
byte_t changePlayer(byte_t ActivePlayer);
void solveGame(byte_t** map, int N, int M, int K, byte_t player);
//Based on https://en.wikipedia.org/wiki/Minimax and https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-1-introduction/
int minimax(byte_t** map, int N, int M, int K, byte_t player, byte_t enemy, bool isMaximizing, int alpha, int beta);

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N = 0, M = 0, K = 0;
    byte_t player;
    byte_t** map = NULL;
    char command[MAX_CMD_LENGTH];
    while (true) {
        cin >> command;
        if (feof(stdin) != 0) {
            break;
        }
        if (checkString(command, "GEN_ALL_POS_MOV")) {
            cin >> N >> M >> K >> player;
            map = createMap(N, M);
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < M; x++) {
                    cin >> map[y][x];
                }
            }
            generateAllPositionMoves(map, N, M, K, player);
            freeMemory(map, N);
        }
        else if (checkString(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER")) {
            cin >> N >> M >> K >> player;
            map = createMap(N, M);
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < M; x++) {
                    cin >> map[y][x];
                }
            }
            generateAllPositionMovesCutIfWin(map, N, M, K, player);
            freeMemory(map, N);
        }
        else if (checkString(command, "SOLVE_GAME_STATE")) {
            cin >> N >> M >> K >> player;
            map = createMap(N, M);
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < M; x++) {
                    cin >> map[y][x];
                }
            }
            solveGame(map, N, M, K, player);
            freeMemory(map, N);
        }
    }
    return 0;
}

byte_t** createMap(int n, int m) {
    byte_t** map = new byte_t * [n];
    for (int i = 0; i < n; i++) {
        map[i] = new byte_t[m];
    }
    return map;
}

void freeMemory(byte_t** map, int n) {
    if (map) {
        for (int i = 0; i < n; i++) {
            if (map[i]) {
                delete[] map[i];
            }
        }
        delete[] map;
    }
}

void printMap(byte_t** map, int n, int m) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            cout << map[y][x] << " ";
        }
        cout << endl;
    }
}

bool checkWinCond(byte_t** map, int N, int M, int K, byte_t ActivePlayer) {
    return checkHorizontalAxis(map, N, M, K, ActivePlayer)
        || checkVerticalAxis(map, N, M, K, ActivePlayer)
        || checkDiagonalsAxis(map, N, M, K, ActivePlayer)
        || checkAntiDiagonalsAxis(map, N, M, K, ActivePlayer);
}
//poziom
bool checkHorizontalAxis(byte_t** map, int N, int M, int K, byte_t ActivePlayer) {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x + K - 1 < M; x++) {
            if (map[y][x] == ActivePlayer) {
                int k = 0;
                for (k = 0; k < K; k++) {
                    if (map[y][x] != map[y][x + k]) {
                        break;
                    }

                }
                if (k == K)
                    return true;
            }
        }
    }
    return false;
}
//pion
bool checkVerticalAxis(byte_t** map, int N, int M, int K, byte_t ActivePlayer) {
    for (int y = 0; y + K - 1 < N; y++) {
        for (int x = 0; x < M; x++) {
            if (map[y][x] == ActivePlayer) {
                int k = 0;
                for (k = 0; k < K; k++) {
                    if (map[y][x] != map[y + k][x]) {
                        break;
                    }
                }
                if (k == K)
                    return true;
            }
        }
    }
    return false;
}

bool checkDiagonalsAxis(byte_t** map, int N, int M, int K, byte_t ActivePlayer) {
    for (int y = 0; y + K - 1 < N; y++) {
        for (int x = 0; x + K - 1 < M; x++) {
            if (map[y][x] == ActivePlayer) {
                int k = 0;
                for (k = 0; k < K; k++) {
                    if (map[y][x] != map[y + k][x + k]) {
                        break;
                    }
                }
                if (k == K)
                    return true;
            }
        }
    }
    return false;
}

bool checkAntiDiagonalsAxis(byte_t** map, int N, int M, int K, byte_t ActivePlayer) {
    for (int y = 0; y + K - 1 < N; y++) {
        for (int x = M - 1; x - K + 1 >= 0; x--) {
            if (map[y][x] == ActivePlayer) {
                int k = 0;
                for (k = 0; k < K; k++) {
                    if (map[y][x] != map[y + k][x - k]) {
                        break;
                    }
                }
                if (k == K)
                    return true;
            }
        }
    }
    return false;
}

int countPosMoves(byte_t** map, int N, int M) {
    int pos_moves = 0;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (map[y][x] == EMPTY)
                pos_moves++;
        }
    }
    return pos_moves;
}

void generateAllPositionMoves(byte_t** map, int N, int M, int K, byte_t ActivePlayer) {
    if (checkWinCond(map, N, M, K, FIRST_PLAYER) || checkWinCond(map, N, M, K, SECOND_PLAYER)) {
        cout << 0 << endl;
        return;
    }
    int pos_moves = countPosMoves(map, N, M);
    cout << pos_moves << endl;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (map[y][x] == EMPTY) {
                map[y][x] = ActivePlayer;
                printMap(map, N, M);
                map[y][x] = EMPTY;
            }
        }
    }
}

void generateAllPositionMovesCutIfWin(byte_t** map, int N, int M, int K, byte_t ActivePlayer) {
    if (checkWinCond(map, N, M, K, FIRST_PLAYER) || checkWinCond(map, N, M, K, SECOND_PLAYER)) {
        cout << 0 << endl;
        return;
    }
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (map[y][x] == EMPTY) {
                map[y][x] = ActivePlayer;
                if (checkWinCond(map, N, M, K, ActivePlayer)) {
                    cout << 1 << endl;
                    printMap(map, N, M);
                    return;
                }
                map[y][x] = EMPTY;
            }
        }
    }
    int pos_moves = countPosMoves(map, N, M);
    cout << pos_moves << endl;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (map[y][x] == EMPTY) {
                map[y][x] = ActivePlayer;
                printMap(map, N, M);
                map[y][x] = EMPTY;
            }
        }
    }
}

byte_t changePlayer(byte_t ActivePlayer) {
    if (ActivePlayer == FIRST_PLAYER)
        return SECOND_PLAYER;
    else
        return FIRST_PLAYER;
}

void solveGame(byte_t** map, int N, int M, int K, byte_t player) {
    int gameresult = minimax(map, N, M, K, player, changePlayer(player), true, INT_MIN, INT_MAX);
    if (gameresult == WIN) {
        if (player == FIRST_PLAYER)
            cout << "FIRST_PLAYER_WINS\n";
        else
            cout << "SECOND_PLAYER_WINS\n";
    }
    else if (gameresult == LOSE) {
        if (player == FIRST_PLAYER)
            cout << "SECOND_PLAYER_WINS\n";
        else
            cout << "FIRST_PLAYER_WINS\n";
    }
    else
        cout << "BOTH_PLAYERS_TIE\n";
}

int minimax(byte_t** map, int N, int M, int K, byte_t player, byte_t enemy, bool isMaximizing, int alpha, int beta) {
    if (checkWinCond(map, N, M, K, player)) {
        return WIN;
    }
    if (checkWinCond(map, N, M, K, enemy)) {
        return LOSE;
    }
    if (countPosMoves(map, N, M) == 0) {
        return TIE;
    }
    if (isMaximizing) {
        int optimal = INT_MIN;
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < M; x++) {
                if (map[y][x] == EMPTY) {
                    map[y][x] = player;
                    int move = minimax(map, N, M, K, player, enemy, false, alpha, beta);
                    optimal = max(optimal, move);
                    map[y][x] = EMPTY;
                    alpha = max(alpha, optimal);
                    if (alpha >= beta)
                        return alpha;
                }
            }
        }
        return optimal;
    }
    else {
        int optimal = INT_MAX;
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < M; x++) {
                if (map[y][x] == EMPTY) {
                    map[y][x] = enemy;
                    int move = minimax(map, N, M, K, player, enemy, true, alpha, beta);
                    optimal = min(optimal, move);
                    map[y][x] = EMPTY;
                    beta = min(beta, optimal);
                    if (alpha >= beta)
                        return beta;
                }
            }
        }
        return optimal;
    }
}