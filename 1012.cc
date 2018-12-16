#include <cstdio>
using namespace std;

int get_initial_number(int x, int m, int k) {
    for(int i = k + 1; i <= k+k; i++) {
        x = (x + m) % i;
    }
    return x;
}

bool can(int k, int m) {
    for(int i = 0; i < k; i++) {
        int initial_number = get_initial_number(i, m, k);
        if(initial_number >= k) return false;
    }
    return true;
}

int main() {
    int k;
    while(scanf("%d", &k) == 1 && k) {
        for(int i = k + 1; ; i++) {
            if(can(k, i)) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}
