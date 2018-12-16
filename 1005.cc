#include <cstdio>
#include <cmath>
using namespace std;

const double PI = acos(-1.0);

int getErosionYear(double x, double y) {
    double radius_square = x * x + y * y;
    double area = PI * radius_square * 0.5;
    double year = area / 50;
    return ceil(year);
}

int main() {
    int T;
    scanf("%d", &T);
    for(int i = 0; i < T; i++) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        int year = getErosionYear(x, y);
        printf("Property %d: This property will begin eroding in year %d.\n", i + 1, year);
    }
    printf("END OF OUTPUT.\n");
    return 0;
}
