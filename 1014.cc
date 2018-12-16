#include <cstdio>
#include <cstring>
#include <deque>
#include <queue>
using namespace std;

const int INF = ~0U>>2;

int n[7];
int f[60001];

int main() {
    int case_number = 1;
    while(scanf("%d", &n[1]) != EOF) {
        int sum = n[1];
        for(int i = 2; i <= 6; i++) {
            scanf("%d", &n[i]);
            sum += i * n[i];
        }
        if(sum == 0) break;
        printf("Collection #%d:\n", case_number++);
        if(sum % 2 == 1) {
            printf("Can't be divided.\n\n");
            continue;
        }
        
        memset(f, 0, sizeof(f));
        
        for(int i = 1; i <= 6; i++) if(n[i]) {
            queue<int> p;
            deque<int> q;
            for(int j = 0; j < i; j++) {
                for(int k = j, s = 0; k <= sum / 2; k += i, s++) {
                    if(p.size() == n[i] + 1) {
                        if(p.front() == q.front()) q.pop_front();
                        p.pop();
                    }
                    int t = f[k] - i * s;
                    p.push(t);
                    while(!q.empty() && q.back() < t) q.pop_back();
                    q.push_back(t);
                    f[k] = q.front() + i * s;
                }
            }
        }
        
        if(f[sum / 2] == sum / 2) {
            printf("Can be divided.\n\n");
        } else {
            printf("Can't be divided.\n\n");
        }
    }
    return 0;
}
