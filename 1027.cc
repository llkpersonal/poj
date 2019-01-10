#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

char matrix[10][20];
bool vis[10][20];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool valid_position(int x, int y) {
    return x >= 0 && x < 10 && y >= 0 && y < 20;
}

void find_max_cluster(int x,
                      int y,
                      int& chess_count,
                      int& left_most,
                      int& bottom_most) {
    if(left_most == -1 || y < left_most) {
        left_most = y;
        bottom_most = x;
    }
    if(y == left_most && x < bottom_most) {
        bottom_most = x;
    }
    vis[x][y] = true;
    chess_count++;
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(valid_position(nx, ny) && !vis[nx][ny] && matrix[nx][ny] == matrix[x][y]) {
            find_max_cluster(nx, ny, chess_count, left_most, bottom_most);
        }
    }
}

void fill_dot(int x, int y, char c) {
    matrix[x][y] = '.';
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(valid_position(nx, ny) && matrix[nx][ny] == c) {
            fill_dot(nx, ny, c);
        }
    }
}

void regular_column(int y, vector<char>& v) {
    v.clear();
    for(int x = 0; x < 10; x++) {
        if(matrix[x][y] != '.') {
            v.push_back(matrix[x][y]);
        }
    }
}

void regular_chessboard() {
    int y = 0;
    vector<char> v;
    for(int j = 0; j < 15; j++) {
        regular_column(j, v);
        if(v.empty()) continue;
        for(int i = 0; i < 10; i++) {
            matrix[i][y] = i < v.size() ? v[i] : '.';
        }
        y++;
    }
    while(y < 15) {
        for(int i = 0; i < 10; i++) {
            matrix[i][y] = '.';
        }
        y++;
    }
}

int main() {
    int t;
    scanf("%d", &t);
    int game_index = 1;
    while(t--) {
        for(int i = 9; i >= 0; i--) scanf("%s", matrix[i]);
        int score = 0;
        int move_index = 1;
        int moved_balls = 0;
        printf("Game %d:\n\n", game_index++);
        while(true) {
            int x = -1, y = -1, max_chess_count = -1;
            memset(vis, 0, sizeof(vis));
            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 15; j++) {
                    if(!vis[i][j] && matrix[i][j] != '.') {
                        int chess_count = 0, left_most = -1, bottom_most = -1;
                        find_max_cluster(i, j, chess_count, left_most, bottom_most);
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
            fill_dot(x, y, matrix[x][y]);
            regular_chessboard();
        }
        if(moved_balls == 150) {
            score += 1000;
        }
        printf("Final score: %d, with %d balls remaining.\n\n", score, 150-moved_balls);
    }
    return 0;
}
