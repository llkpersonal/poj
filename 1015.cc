#include <algorithm>
#include <cstdio>
using namespace std;

const int INF = ~0U>>2;
int F[20][9000];

struct Candidate{
    int index;
    int d;
    int p;
};

Candidate candidates[201];

bool compare(Candidate& a, Candidate& b) {
    return a.d - a.p < b.d - b.p;
}

int& f(int j, int k) {
    return F[j][k+4000];
}

int main() {
    int m, n;
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &candidates[i].d, &candidates[i].p);
            candidates[i].index = i;
        }
        
        sort(candidates+1, candidates + 1 + n, compare);
        
        for(int j = 0; j < 20; j++) {
            for(int k = 0; k < 9000; k++) {
                F[j][k] = -INF;
            }
        }
        
        int min_sum = 0, max_sum = 0;
        for(int i = 1; i <= m; i++) {
            min_sum += candidates[i].d - candidates[i].p;
        }
        for(int i = n; i > n - m; i--) {
            max_sum += candidates[i].d - candidates[i].p;
        }
        
        f(0, 0) = 0;
        
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                for(int k = max_sum; k >= min_sum; k--) {
                    if(k - candidates[i].d + candidates[i].p >= min_sum
                       && k - candidates[i].d + candidates[i].p <= max_sum)
                        f(j, k) = max(f(j, k),
                            f(j-1, k-candidates[i].d+candidates[i].p) + candidates[i].d + candidates[i].p);
                }
            }
        }
        
        int min_number = INF;
        
        for(int i = min_sum; i <= max_sum; i++) {
            if(f(m, i) > 0)
                min_number = min(min_number, abs(i));
        }
        
        printf("%d %d\n", min_number, max(f(m, -min_number), f(m, min_number)));
    }
    return 0;
}
