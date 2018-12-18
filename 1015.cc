#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int INF = ~0U>>2;
int F[2][21][901];
bool P[201][21][901];

struct Candidate{
    int d;
    int p;
};

Candidate candidates[201];

int& f(int i, int j, int k) {
    return F[i % 2][j][k+400];
}

bool& p(int i, int j, int k) {
    return P[i][j][k+400];
}

void get_answer(vector<int>& answer, int volume, int n, int m) {
    while(n > 0 && m > 0) {
        if(p(n, m, volume)) {
            answer.push_back(n);
            m--;
            volume = volume - candidates[n].d + candidates[n].p;
        }
        n--;
    }
    reverse(answer.begin(), answer.end());
}

int main() {
    int m, n;
    int jury_number = 1;
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &candidates[i].d, &candidates[i].p);
        }

        for(int i = 0; i < 2; i++) {
            for(int j = 0; j <= 20; j++) {
                for(int k = 0; k < 901; k++) {
                    F[i][j][k] = -INF;
                }
            }
        }
        
        memset(P, 0, sizeof(P));
        
        for(int i = 0; i <= 1; i++) {
            f(i, 0, 0) = 0;
        }
        
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= min(m,i); j++) {
                for(int k = -400; k <= 400; k++) {
                    f(i, j, k) = f(i-1, j, k);
                    if(k - candidates[i].d + candidates[i].p >= -400
                        && k - candidates[i].d + candidates[i].p <= 400) {
                        int t = f(i-1, j-1, k-candidates[i].d+candidates[i].p) + candidates[i].d + candidates[i].p;
                        if(f(i, j, k) <= t) {
                            p(i, j, k) = true;
                            f(i, j, k) = t;
                        }
                    }
                }
            }
        }
        
        int min_number = INF;
        
        for(int i = -400; i <= 400; i++) {
            if(f(n, m, i) >= 0)
                min_number = min(min_number, abs(i));
        }
        
        vector<int> result;
        if(f(n, m, -min_number) <= f(n, m, min_number)) {
            get_answer(result, min_number, n, m);
        } else {
            get_answer(result, -min_number, n, m);
        }
        
        int DJ = 0, PJ = 0;
        for(int i = 0; i < result.size(); i++) {
            DJ += candidates[result[i]].d;
            PJ += candidates[result[i]].p;
        }
        
        printf("Jury #%d\n", jury_number++);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", DJ, PJ);
        for(int i = 0; i < result.size(); i++) printf(" %d", result[i]);
        printf("\n");
    }
    return 0;
}
