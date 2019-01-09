#include <algorithm>
#include <cstdio>
#include <iterator>
#include <set>
#include <vector>
using namespace std;
typedef pair<int,int> P;
typedef vector< vector<bool> > Matrix;

void dfs(int x, int y, vector<P>& result, Matrix& matrix) {
    static int dx[] = {-1, 1, 0, 0};
    static int dy[] = {0, 0, 1, -1};
    
    result.push_back(make_pair(x, y));
    matrix[x][y] = false;
    
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >= 0 && nx < matrix.size() && ny >= 0 && ny < matrix[0].size() && matrix[nx][ny]) {
            dfs(nx, ny, result, matrix);
        }
    }
}

int calculate_hash(vector<P>& points) {
    int res = 0;
    for(int i = 0; i < points.size(); i++) {
        P& x = points[i];
        for(int j = i + 1; j < points.size(); j++) {
            P& y = points[j];
            res += (x.first - y.first) * (x.first - y.first)
                + (x.second - y.second) * (x.second - y.second);
        }
    }
    return res;
}

void handle(multiset<int>& result_set, Matrix& matrix) {
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[0].size(); j++) {
            if(matrix[i][j]) {
                vector<P> result;
                dfs(i, j, result, matrix);
                int hash_value = calculate_hash(result);
                result_set.insert(hash_value);
            }
        }
    }
}

bool check(multiset<int>& hash_left, multiset<int> hash_right) {
    for(multiset<int>::iterator it = hash_left.begin(); it != hash_left.end(); ++it) {
        int t = *it;
        multiset<int>::iterator t_it = hash_right.find(t);
        if(t_it != hash_right.end()) {
            hash_right.erase(t_it);
        } else {
            return false;
        }
    }
    return hash_right.empty();
}

int main() {
    int t,w,h,n,x,y;
    scanf("%d",&t);
    while(t--) {
        scanf("%d%d%d",&w,&h,&n);
        Matrix matrix_left(w, vector<bool>(h, false));
        Matrix matrix_right(matrix_left);
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &x, &y);
            matrix_left[x][y] = true;
        }

        for(int i = 0; i < n; i++) {
            scanf("%d%d", &x, &y);
            matrix_right[x][y] = true;
        }

        multiset<int> hash_left, hash_right;
        handle(hash_left, matrix_left);
        handle(hash_right, matrix_right);
        
        bool ans = check(hash_left, hash_right);
        printf(ans ? "YES\n" : "NO\n");
    }
    return 0;
}
