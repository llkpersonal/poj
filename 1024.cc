#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iterator>
#include <queue>
#include <set>
using namespace std;

typedef set< pair< pair<int,int>, pair<int,int> > > wallset;

char path[10010];
int f[110][110];

bool check_boundary(int w, int h, int x, int y) {
    return x >= 0 && x < w && y >= 0 && y < h;
}

pair<int, int> get_direction(char dir) {
    if(dir == 'U') return make_pair(0, 1);
    if(dir == 'D') return make_pair(0, -1);
    if(dir == 'L') return make_pair(-1, 0);
    return make_pair(1, 0);
}

bool not_wall(int x1, int y1, int x2, int y2, wallset& walls) {
    return walls.find(make_pair(make_pair(x1,y1), make_pair(x2,y2))) == walls.end() &&
        walls.find(make_pair(make_pair(x2,y2), make_pair(x1,y1))) == walls.end();
}

pair<int,int> check_walls_and_get_terminal(int w, int h, wallset& walls) {
    for(wallset::iterator it = walls.begin(); it != walls.end(); ++it) {
        pair<int, int> wall_a = it->first;
        pair<int, int> wall_b = it->second;
        if(wall_a.first == wall_b.first) {
            if(abs(wall_a.second - wall_b.second) != 1) {
                return make_pair(-1, -1);
            }
        } else if(wall_a.second == wall_b.second) {
            if(abs(wall_a.first - wall_b.first) != 1) {
                return make_pair(-1, -1);
            }
        } else {
            return make_pair(-1, -1);
        }
    }

    pair<int, int> res = make_pair(0, 0);
    for(int i = 0; path[i]; i++) {
        pair<int,int> d = get_direction(path[i]);
        int dx = d.first, dy = d.second;
        int x = res.first, y = res.second;
        int nx = x + dx, ny = y + dy;
        if(not_wall(x, y, nx, ny, walls)) {
            if(check_boundary(w, h, nx, ny)) {
                res = make_pair(nx, ny);
            } else {
                return make_pair(-1, -1);
            }
        } else {
            return make_pair(-1, -1);
        }
    }
    
    return res;
}

bool check_unique_and_shortest(int tx, int ty, int w, int h, wallset& walls) {
    static int dx[] = {-1, 1, 0, 0};
    static int dy[] = {0, 0, 1, -1};
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            f[i][j] = -1;
        }
    }
    int path_length = strlen(path);
    int count = 0;
    queue< pair<int, int> > q;
    f[0][0] = 0;
    q.push(make_pair(0, 0));
    while(!q.empty()) {
        pair<int, int> t = q.front(); q.pop();
        int x = t.first, y = t.second;
        int step = f[x][y];
        if(step > path_length) continue;
        if(x == tx && y == ty) {
            if(step < path_length) return false;
            ++count;
            if(count == 2) return false;
        }
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(check_boundary(w, h, nx, ny) &&
                not_wall(x, y, nx, ny, walls) && f[nx][ny] == -1) {
                f[nx][ny] = step+1;
                q.push(make_pair(nx, ny));
            }
        }
    }
    
    while(tx != 0 || ty != 0) {
        int cnt = 0;
        int xx = tx, yy = ty;
        for(int i = 0; i < 4; i++) {
            int nx = xx + dx[i], ny = yy + dy[i];
            if(check_boundary(w, h, nx, ny)
                    && not_wall(xx, yy, nx, ny, walls)
                    && f[xx][yy] == f[nx][ny] + 1) {
                ++cnt;
                tx = nx;
                ty = ny;
            }
        }
        if(cnt > 1) return false;
    }
    
    return true;
}

bool check_correct(int w, int h, wallset& walls) {
    pair<int, int> terminal = check_walls_and_get_terminal(w, h, walls);
    if(terminal.first == -1) {
        return false;
    }
    
    if(!check_unique_and_shortest(terminal.first, terminal.second, w, h, walls)) {
        return false;
    }
    
    for(wallset::iterator it = walls.begin(); it != walls.end(); ++it) {
        pair< pair<int,int>, pair<int,int> > t = *it;
        walls.erase(it);
        if(check_unique_and_shortest(terminal.first, terminal.second, w, h, walls)) {
            return false;
        }
        walls.insert(t);
        it = walls.find(t);
    }
    return true;
}

int main() {
    int t, w, h, m, x1, y1, x2, y2;
    scanf("%d", &t);
    while(t--) {
        wallset walls;
        scanf("%d%d", &w, &h);
        scanf("%s", path);
        scanf("%d", &m);
        
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            walls.insert(make_pair(make_pair(x1,y1), make_pair(x2,y2)));
        }
        
        printf(check_correct(w, h, walls) ? "CORRECT\n" : "INCORRECT\n");
    }
    return 0;
}
