#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    int n[7];
    while(scanf("%d", &n[1]) != EOF) {
        int sum = n[1];
        for(int i = 2; i <= 6; i++) {
            scanf("%d", &n[i]);
            sum += n[i];
        }
        if(sum == 0) break;

        int ans = n[6];

        if(n[5]) {
            ans += n[5];
            n[1] = n[1] - min(n[1], n[5] * 11);
        }

        if(n[4]) {
            ans += n[4];
            int cnt_2 = min(n[2], n[4] * 5);
            n[2] = n[2] - cnt_2;
            int t = n[4] * 36 - n[4] * 16 - cnt_2 * 4;
            n[1] = n[1] - min(n[1], t);
        }

        if(n[3]) {
            int cnt_2 = 0;
            ans += n[3] / 4;
            int cnt_3 = n[3] % 4;
            if(cnt_3) {
                ans++;
                if(cnt_3 == 1) {
                    cnt_2 = min(n[2], 5);
                } else if(cnt_3 == 2) {
                    cnt_2 = min(n[2], 3);
                } else if(cnt_3 == 3) {
                    cnt_2 = min(n[2], 1);
                }
                n[2] -= cnt_2;
                int cnt_1 = 36 - 9 * cnt_3 - 4 * cnt_2;
                n[1] = n[1] - min(n[1], cnt_1);
            }
        }

        if(n[2]) {
            ans += n[2] / 9;
            n[2] %= 9;
            if(n[2]) {
                ans++;
                int cnt_1 = 36 - 4 * n[2];
                n[1] = n[1] - min(n[1], cnt_1);
            }
        }

        ans += (n[1] + 35) / 36;
        printf("%d\n", ans);
    }
    return 0;
}
