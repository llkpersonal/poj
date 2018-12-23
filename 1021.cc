#include <algorithm>
#include <cstdio>
#include <iterator>
#include <set>
#include <vector>
using namespace std;
typedef pair<int,int> P;
typedef vector< vector<bool> > Matrix;

void add(multiset<P>& s, int right, int down) {
    int max_number = max(right, down);
    int min_number = min(right, down);
    s.insert(make_pair(min_number, max_number));
}

void statistic_coordinates(multiset<P>& s, const Matrix& matrix) {
    int w = matrix.size(), h = matrix[0].size();
    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            if(matrix[i][j]) {
                int right = 0;
                for(int k = i; k < w && matrix[k][j]; k++) {
                    ++right;
                }
                int down = 0;
                for(int k = j; k < h && matrix[i][k]; k++) {
                    ++down;
                }
                add(s, right, down);
            }
        }
    }
}

bool check(multiset<P>& s_left, multiset<P>& s_right) {
    for(multiset<P>::iterator it = s_left.begin(); it != s_left.end(); ++it) {
        P t = *it;
        multiset<P>::iterator t_it = s_right.find(t);
        if(t_it == s_right.end()) return false;
        s_right.erase(t_it);
    }
    return s_right.empty();
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

        multiset<P> s_left, s_right;
        statistic_coordinates(s_left, matrix_left);
        statistic_coordinates(s_right, matrix_right);

        bool ans = check(s_left, s_right);
        printf(ans ? "YES\n" : "NO\n");
    }
    return 0;
}
