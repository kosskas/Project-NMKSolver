#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <cstdio>

#define checkString(a, b) (strcmp(a, b) == 0)
#define MAX_CMD_LENGTH 100
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

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

char** createMap(int n, int m);
void freeMemory(char** map, int n);
void printMap(char** map, int n, int m);
bool checkWinCond(char** map, int N, int M, int K, char ActivePlayer);
bool checkHorizontalAxis(char** map, int N, int M, int K, char ActivePlayer);
bool checkVerticalAxis(char** map, int N, int M, int K, char ActivePlayer);
bool checkVerticalAxis(char** map, int N, int M, int K, char ActivePlayer);
bool checkDiagonalsAxis(char** map, int N, int M, int K, char ActivePlayer);
bool checkAntiDiagonalsAxis(char** map, int N, int M, int K, char ActivePlayer);
void generateAllPositionMoves(char** map, int N, int M, int K, char ActivePlayer);
int countPosMoves(char** map, int N, int M);
void generateAllPositionMovesCutIfWin(char** map, int N, int M, int K, char ActivePlayer);
char changePlayer(char ActivePlayer);
void solveGame(char** map, int N, int M, int K, char player);
//Based on https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-1-introduction/
//and P.Wroblewski Algorytmy, struktury danych i techniki programowania
int minimax(char** map, int N, int M, int K, char player, char enemy, bool isMaximizing, int alpha, int beta);

int main() {
    int N = 0, M = 0, K = 0;
    char player = FIRST_PLAYER;
    char** map = NULL;
    char command[MAX_CMD_LENGTH];
    while (true) {
        scanf("%s %d %d %d %c\n", command, &N, &M, &K, &player);
        if (feof(stdin) != 0) {
            break;
        }
        if (checkString(command, "GEN_ALL_POS_MOV")) {
            map = createMap(N, M);
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < M; x++) {
                    scanf("%c ", &map[y][x]);
                }
            }
            generateAllPositionMoves(map, N, M, K, player);
            freeMemory(map, N);
        }
        else if (checkString(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER")) {
            map = createMap(N, M);
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < M; x++) {
                    scanf("%c ", &map[y][x]);
                }
            }
            generateAllPositionMovesCutIfWin(map, N, M, K, player);
            freeMemory(map, N);
        }
        else if (checkString(command, "SOLVE_GAME_STATE")) {
            map = createMap(N, M);
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < M; x++) {
                    scanf("%c ", &map[y][x]);
                }
            }
            solveGame(map, N, M, K, player);
            freeMemory(map, N);
        }
    }
    return 0;
}

char** createMap(int n, int m) {
    char** map = new char * [n];
    for (int i = 0; i < n; i++) {
        map[i] = new char[m];
    }
    return map;
}

void freeMemory(char** map, int n) {
    if (map) {
        for (int i = 0; i < n; i++) {
            if (map[i]) {
                delete[] map[i];
            }
        }
        delete[] map;
    }
}

void printMap(char** map, int n, int m) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            printf("%c ", map[y][x]);
        }
        printf("\n");
    }
}

bool checkWinCond(char** map, int N, int M, int K, char ActivePlayer) {
    return checkHorizontalAxis(map, N, M, K, ActivePlayer)
        || checkVerticalAxis(map, N, M, K, ActivePlayer)
        || checkDiagonalsAxis(map, N, M, K, ActivePlayer)
        || checkAntiDiagonalsAxis(map, N, M, K, ActivePlayer);
}
//poziom
bool checkHorizontalAxis(char** map, int N, int M, int K, char ActivePlayer) {
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
bool checkVerticalAxis(char** map, int N, int M, int K, char ActivePlayer) {
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

bool checkDiagonalsAxis(char** map, int N, int M, int K, char ActivePlayer) {
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

bool checkAntiDiagonalsAxis(char** map, int N, int M, int K, char ActivePlayer) {
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

int countPosMoves(char** map, int N, int M) {
    int pos_moves = 0;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (map[y][x] == EMPTY)
                pos_moves++;
        }
    }
    return pos_moves;
}

void generateAllPositionMoves(char** map, int N, int M, int K, char ActivePlayer) {
    if (checkWinCond(map, N, M, K, FIRST_PLAYER) || checkWinCond(map, N, M, K, SECOND_PLAYER)) {
        printf("0\n");
        return;
    }
    int pos_moves = countPosMoves(map, N, M);
    printf("%d\n", pos_moves);
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

void generateAllPositionMovesCutIfWin(char** map, int N, int M, int K, char ActivePlayer) {
    if (checkWinCond(map, N, M, K, FIRST_PLAYER) || checkWinCond(map, N, M, K, SECOND_PLAYER)) {
        printf("0\n");
        return;
    }
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (map[y][x] == EMPTY) {
                map[y][x] = ActivePlayer;
                if (checkWinCond(map, N, M, K, ActivePlayer)) {
                    printf("1\n");
                    printMap(map, N, M);
                    return;
                }
                map[y][x] = EMPTY;
            }
        }
    }
    int pos_moves = countPosMoves(map, N, M);
    printf("%d\n", pos_moves);
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

char changePlayer(char ActivePlayer) {
    if (ActivePlayer == FIRST_PLAYER)
        return SECOND_PLAYER;
    else
        return FIRST_PLAYER;
}

void solveGame(char** map, int N, int M, int K, char player) {
    int gameresult = minimax(map, N, M, K, player, changePlayer(player), true, INT_MIN, INT_MAX);
    if (gameresult == WIN) {
        if (player == FIRST_PLAYER)
            printf("FIRST_PLAYER_WINS\n");
        else
            printf("SECOND_PLAYER_WINS\n");
    }
    else if (gameresult == LOSE) {
        if (player == FIRST_PLAYER)
            printf("SECOND_PLAYER_WINS\n");
        else
            printf("FIRST_PLAYER_WINS\n");
    }
    else
        printf("BOTH_PLAYERS_TIE\n");
}

int minimax(char** map, int N, int M, int K, char player, char enemy, bool isMaximizing, int alpha, int beta) {
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