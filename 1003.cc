#include <cstdio>
#include <cmath>
using namespace std;

int solve(double c) {
    int res = 0;
    double current = 0;
    while(current < c) {
        res++;
        current += 1.0 / (res+1);
    }
    return res;
}

int main() {
    double c;
    while(scanf("%lf", &c) != EOF) {
        if(fabs(c) < 1e-8) break;
        int ans = solve(c);
        printf("%d card(s)\n", ans);
    }
    return 0;
}
