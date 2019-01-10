#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

char matrix[10][20];
char t_matrix[10][20];

bool valid_position(int x, int y, char m[10][20]) {
    return x >= 0 && x < 10 && y >= 0 && y < 20 && m[x][y] != '.';
}

void find_max_cluster(int x,
                      int y,
                      int& chess_count,
                      int& left_most,
                      int& bottom_most,
                      char m[10][20]) {
    if(left_most == -1 || y < left_most) {
        left_most = y;
        bottom_most = x;
    }
    if(y == left_most && x < bottom_most) {
        bottom_most = x;
    }
    chess_count++;
    char t = m[x][y];
    m[x][y] = '.';
    static int dx[] = {-1, 1, 0, 0};
    static int dy[] = {0, 0, -1, 1};
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(valid_position(nx, ny, m) && m[nx][ny] == t) {
            find_max_cluster(nx, ny, chess_count, left_most, bottom_most, m);
        }
    }
}


void regular_column(int y, vector<char>& v) {
    for(int x = 0; x < 10; x++) {
        if(matrix[x][y] != '.') {
            v.push_back(matrix[x][y]);
        }
    }
}

void regular_chessboard() {
    for(int i = 0; i < 10; i++) for(int j = 0; j < 15; j++) t_matrix[i][j] = '.';
    int y = 0;
    for(int j = 0; j < 15; j++) {
        vector<char> v;
        regular_column(j, v);
        if(v.empty()) continue;
        for(int i = 0; i < v.size(); i++) {
            t_matrix[i][y] = v[i];
        }
        y++;
    }
    memcpy(matrix, t_matrix, sizeof(matrix));
}

int main() {
    int t;
    scanf("%d", &t);
    int game_index = 1;
    while(t--) {
        for(int i = 0; i < 10; i++) scanf("%s", matrix[i]);
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 15; j++) {
                t_matrix[9 - i][j] = matrix[i][j];
            }
        }
        memcpy(matrix, t_matrix, sizeof(matrix));
        int score = 0;
        int move_index = 1;
        int moved_balls = 0;
        printf("Game %d:\n\n", game_index++);
        while(true) {
            int x = -1, y = -1, max_chess_count = -1;
            memcpy(t_matrix, matrix, sizeof(matrix));
            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 15; j++) {
                    if(t_matrix[i][j] != '.') {
                        int chess_count = 0, left_most = -1, bottom_most = -1;
                        find_max_cluster(i, j, chess_count, left_most, bottom_most, t_matrix);
                        if(chess_count > max_chess_count) {
                            x = bottom_most; y = left_most; max_chess_count = chess_count;
                        } else if(chess_count == max_chess_count) {
                            if(left_most < y || (left_most == y && bottom_most < x)) {
                                x = bottom_most; y = left_most;
                            }
                        }
                    }
                }
            }
            if(max_chess_count < 2) break;
            int current_score = (max_chess_count - 2) * (max_chess_count - 2);
            score += current_score;
            moved_balls += max_chess_count;
            printf("Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n",
                   move_index++, x+1, y+1, max_chess_count, matrix[x][y], current_score);
            max_chess_count = 0;
            int left_most = -1, bottom_most = -1;
            find_max_cluster(x, y, max_chess_count, left_most, bottom_most, matrix);
            regular_chessboard();
            /*
            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 15; j++) {
                    putchar(matrix[i][j]);
                }
                printf("\n");
            }
            */
        }
        if(moved_balls == 150) {
            score += 1000;
        }
        printf("Final score: %d, with %d balls remaining.\n\n", score, 150-moved_balls);
    }
    return 0;
}
