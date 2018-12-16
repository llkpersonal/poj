#include <cstdio>
using namespace std;

int main() {
    double current = 0, total = 0;
    for(int i = 0; i < 12; i++) {
        scanf("%lf", &current);
        total += current;
    }
    printf("$%.2f\n", total / 12);
    return 0;
}
