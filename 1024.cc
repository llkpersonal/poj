#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iterator>
#include <map>
#include <queue>
#include <set>
using namespace std;

typedef set< pair< pair<int,int>, pair<int,int> > > wallset;

char path[10010];

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
        // printf("nx = %d, ny = %d\n", nx, ny);
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
    //printf("WALLS COUNT: %d\n", walls.size());
    static int dx[] = {-1, 1, 0, 0};
    static int dy[] = {0, 0, 1, -1};
    int path_length = strlen(path);
    queue< pair< pair<int, int>, int> > q;
    q.push(make_pair(make_pair(0,0),0));
    map< pair<int, int>, pair< pair<int,int>, int> > visited;
    visited[make_pair(0, 0)] = make_pair(make_pair(-1, -1), 0);
    int shortest_length = 0;
    
    while(!q.empty()) {
        pair< pair<int, int>, int> t = q.front(); q.pop();
        pair<int, int> position = t.first;
        //printf("(%d, %d)\n", position.first, position.second);
        int step = t.second;
        if(step > path_length) continue;
        if(position.first == tx && position.second == ty) {
            if(step < path_length) return false;
            shortest_length ++;
            if(shortest_length == 2) return false;
        }
        for(int i = 0; i < 4; i++) {
            int nx = position.first + dx[i];
            int ny = position.second + dy[i];
            if(not_wall(position.first, position.second, nx, ny, walls) && check_boundary(w, h, nx, ny)) {
                map< pair<int, int>, pair< pair<int, int>, int> >::iterator it
                    = visited.find(make_pair(nx, ny));
                if(it == visited.end() ||
                   (it != visited.end() && it->second.second == step+1 &&
                        (it->second.first.first != nx || it->second.first.second != ny))
                   ){
                    visited[make_pair(nx, ny)] = make_pair(position, step+1);
                    q.push(make_pair(make_pair(nx, ny), step+1));
                } else if(it->second.second > step + 1) {
                    //printf("nx = %d, ny = %d, it->second = %d\n", nx, ny, it->second.second);
                    return false;
                }
            }
        }
    }
    
    return shortest_length == 1;
}

bool check_correct(int w, int h, wallset& walls) {
    pair<int, int> terminal = check_walls_and_get_terminal(w, h, walls);
    if(terminal.first == -1) {
        // printf("CASE 1: walls invalid!\n");
        return false;
    }
    // printf("CASE 1 PASSED!\n");
    
    if(!check_unique_and_shortest(terminal.first, terminal.second, w, h, walls)) {
        // printf("CASE 2: unique or shortest invalid!\n");
        return false;
    }
    // printf("CASE 2 PASSED!\n");
    // return false;
    for(wallset::iterator it = walls.begin(); it != walls.end(); ++it) {
        pair< pair<int,int>, pair<int,int> > t = *it;
        walls.erase(it);
        //printf("Remove wall: (%d, %d) | (%d, %d)\n", t.first.first, t.first.second, t.second.first, t.second.second);
        if(check_unique_and_shortest(terminal.first, terminal.second, w, h, walls)) {
            //printf("CASE 3: extra walls!\n");
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
        
        if(check_correct(w, h, walls)) {
            printf("CORRECT\n");
        } else {
            printf("INCORRECT\n");
        }
    }
    return 0;
}
