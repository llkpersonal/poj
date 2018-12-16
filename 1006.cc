#include <cstdio>
using namespace std;

const int P = 23;
const int E = 28;
const int I = 33;
int t1, t2, t3, lcm_total;

int gcd(int a, int b) {
    while(b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int lcm(int a, int b) {
    int gcd_number = gcd(a, b);
    return a / gcd(a, b) * b;
}

int lcm(int a, int b, int c) {
    return lcm(lcm(a, b), c);
}

int extGcd(int a, int b, int &x, int &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int dx, dy;
    int gcd_number = extGcd(b, a%b, dx, dy);
    x = dy;
    y = dx - (a / b) * dy;
    return gcd_number;
}

int getNextDay(int p, int e, int i, int d) {
    p = p % P;
    e = e % E;
    i = i % I;
    int crt_result = (p * t1 * (lcm_total / P)) % lcm_total;
    crt_result = (crt_result + (e * t2 * (lcm_total / E)) % lcm_total) % lcm_total;
    crt_result = (crt_result + (i * t3 * (lcm_total / I)) % lcm_total) % lcm_total;
    crt_result = (crt_result + lcm_total) % lcm_total;
    while(crt_result <= d) {
        crt_result += lcm_total;
    }
    return crt_result - d;
}

void init() {
    int t, a;
    lcm_total = lcm(P, E, I);
    a = lcm_total / P;
    extGcd(a, P, t1, t);
    a = lcm_total / E;
    extGcd(a, E, t2, t);
    a = lcm_total / I;
    extGcd(a, I, t3, t);
}

int main() {
    init();
    int p,e,i,d;
    int case_num = 1;
    while(scanf("%d%d%d%d", &p, &e, &i, &d) != EOF) {
        if(p == -1 && e == -1 && i == -1 && d == -1) break;
        int next_day = getNextDay(p, e, i, d);
        printf("Case %d: the next triple peak occurs in %d days.\n", case_num++, next_day);
    }
    return 0;
}
