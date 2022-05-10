#include <iostream>
#include <string.h>

using namespace std;

typedef unsigned char byte_t;
#define checkString(a, b) strcmp(a, b) == 0
#define MAX_CMD_LENGTH 100
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b
enum Position {
    EMPTY = '0',
    FIRST_PLAYER = '1',
    SECOND_PLAYER = '2'
};
enum State {
    BOTH_PLAYERS_TIE = 0,
    FIRST_PLAYER_WINS = 1,
    SECOND_PLAYER_WINS = -1,
};
byte_t** createMap(int n, int m);
void freeMemory(byte_t** map, int n);
void printMap(byte_t** map, int n, int m);
bool checkWinCond(byte_t** map, int N, int M, int K, char ActivePlayer);
bool checkHorizontalAxis(byte_t** map, int N, int M, int K, char ActivePlayer);
bool checkVerticalAxis(byte_t** map, int N, int M, int K, char ActivePlayer);
bool checkVerticalAxis(byte_t** map, int N, int M, int K, char ActivePlayer);
bool checkDiagonalsAxis(byte_t** map, int N, int M, int K, char ActivePlayer);
bool checkAntiDiagonalsAxis(byte_t** map, int N, int M, int K, char ActivePlayer);
void generateAllPositionMoves(byte_t** map, int N, int M, int K, char ActivePlayer);
int countPosMoves(byte_t** map, int N, int M);
void generateAllPositionMovesCutIfWin(byte_t** map, int N, int M, int K, char ActivePlayer);
int minimax(byte_t** map, int N, int M, int K, char ActivePlayer, bool isMaximizing);
char changePlayer(char ActivePlayer);
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N = 0, M = 0, K;
    byte_t player;
    byte_t** map = NULL;
    char command[MAX_CMD_LENGTH];
    while (true) {
        cin >> command;
        if (feof(stdin) != 0) {
            break;
        }
        else if (checkString(command, "GEN_ALL_POS_MOV")) {
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
            if (player == FIRST_PLAYER) {
                int val = minimax(map, N, M, K, FIRST_PLAYER, true);

                if (val == 1) {
                    cout << "FIRST_PLAYER_WINS\n";
                }
                else if (val == -1) {
                    cout << "SECOND_PLAYER_WINS\n";
                }
                else {
                    cout << "BOTH_PLAYERS_TIE\n";
                }
            }
            else {
                int val = minimax(map, N, M, K, SECOND_PLAYER, false);

                if (val == 1) {
                    cout << "FIRST_PLAYER_WINS\n";
                }
                else if (val == -1) {
                    cout << "SECOND_PLAYER_WINS\n";
                }
                else {
                    cout << "BOTH_PLAYERS_TIE\n";
                }
            }
            freeMemory(map, N);
        }
    }  
    return 0;
}

//minimax pos gleb maxplayer
byte_t** createMap(int n, int m) {
    byte_t** map = new byte_t *[n];
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

bool checkWinCond(byte_t** map, int N, int M, int K, char ActivePlayer) {
    return checkHorizontalAxis(map, N, M, K, ActivePlayer)
        || checkVerticalAxis(map, N, M, K, ActivePlayer)
        || checkDiagonalsAxis(map, N, M, K, ActivePlayer)
        || checkAntiDiagonalsAxis(map, N, M, K, ActivePlayer);
}
//poziom
bool checkHorizontalAxis(byte_t** map, int N, int M, int K, char ActivePlayer) {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x + K - 1 < M; x++) {
            if (map[y][x] == ActivePlayer) {
                int k = 0;
                for (k = 0; k < K; k++) {
                    if (map[y][x] != map[y][x + k]) {
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
bool checkVerticalAxis(byte_t** map, int N, int M, int K, char ActivePlayer) {
    for (int y = 0; y + K - 1 < N; y++) {
        for (int x = 0; x < M; x++) {
            if (map[y][x] == ActivePlayer) {
                int k = 0;
                for (k = 0; k < K; k++) {
                    if (map[y][x] != map[y + k][x]) {
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

bool checkDiagonalsAxis(byte_t** map, int N, int M, int K, char ActivePlayer) {
    for (int y = 0; y + K - 1 < N; y++) {
        for (int x = 0; x + K - 1 < M; x++) {
            if (map[y][x] == ActivePlayer) {
                int k = 0;
                for (k = 0; k < K; k++) {
                    if (map[y][x] != map[y + k][x + k]) {
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

bool checkAntiDiagonalsAxis(byte_t** map, int N, int M, int K, char ActivePlayer) {
    for (int y = 0; y + K - 1 < N; y++) {
        for (int x = M - 1; x - K + 1 >= 0; x--) {
            if (map[y][x] == ActivePlayer) {
                int k = 0;
                for (k = 0; k < K; k++) {
                    if (map[y][x] != map[y + k][x - k]) {
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

void generateAllPositionMoves(byte_t** map, int N, int M, int K, char ActivePlayer) {
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

void generateAllPositionMovesCutIfWin(byte_t** map, int N, int M, int K, char ActivePlayer) {
    if (checkWinCond(map, N, M, K, FIRST_PLAYER) || checkWinCond(map, N, M, K, SECOND_PLAYER)) {
        cout << 0 << endl;
        return;
    }
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (map[y][x] == EMPTY) {
                map[y][x] = ActivePlayer;
                if (checkWinCond(map, N, M, K, ActivePlayer)) {
                    cout << 1<<endl;
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

char changePlayer(char ActivePlayer) {
    if (ActivePlayer == '1')
        return '2';
    else
        return '1';
}
int minimax(byte_t** map, int N, int M, int K, char ActivePlayer,bool isMaximizing) {
    
  //  cout << "Teraz rusza " << (char)ActivePlayer << " czyMAX" << isMaximizing << endl;
    //cout << "Mapa jaka zastal " << ActivePlayer << endl;
   // printMap(map, N, M);
    
   // cout << endl;
    if (checkWinCond(map, N, M, K, FIRST_PLAYER)) {
       // cout << "zwrocono 1\n";
        return 1;
    }
    if (checkWinCond(map, N, M, K, SECOND_PLAYER)) {
       //cout << "zwrocono -1\n";
        return -1;
    }
    if (countPosMoves(map, N, M) == 0)
        return 0;

    if (isMaximizing) {
       // cout << " szukam max\n";
        int bestval = -INT_MAX;
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < M; x++) {
                if (map[y][x] == EMPTY) {
                    map[y][x] = ActivePlayer;
                    bestval = max(bestval, minimax(map, N, M, K, changePlayer(ActivePlayer), false));
                    map[y][x] = EMPTY;
                }
            }           
        }
        return bestval;
    }
    else {
      //  cout << " szukam min\n";
        int bestval = INT_MAX;
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < M; x++) {
                if (map[y][x] == EMPTY) {
                    map[y][x] = ActivePlayer;
                    bestval = min(bestval, minimax(map, N, M, K, changePlayer(ActivePlayer), true));
                    map[y][x] = EMPTY;
                }
            }
        }
        return bestval;
    }
}