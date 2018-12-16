#include <cstdio>
#include <cstring>
#include <map>
using namespace std;

char left[3][20], right[3][20], verdict[3][10];
int weight[12];
char ans[2][30]= {"light", "heavy"};
int len[3];

bool check(int id, int w) {
    weight[id] = w;
    for(int i = 0; i < 3; i++) {
        int left_weight = 0, right_weight = 0;
        for(int j = 0; j < len[i]; j++) {
            left_weight += weight[left[i][j] - 'A'];
            right_weight += weight[right[i][j] - 'A'];
        }

        if((left_weight == right_weight && strcmp(verdict[i], "even"))
           || (left_weight > right_weight && strcmp(verdict[i], "up"))
           || (left_weight < right_weight && strcmp(verdict[i], "down"))) {
            weight[id] = 1;
            return false;
        }
    }
    weight[id] = 1;
    return true;
}

pair<int, int> solve() {
    for(int i = 0; i < 12; i++) weight[i] = 1;
    for(int i = 0; i < 12; i++) {
        if(check(i, 0)) {
            return make_pair(i, 0);
        }
        if(check(i, 2)) {
            return make_pair(i, 1);
        }
    }
    return make_pair(-1, -1);
}

int main() {
    int n;
    scanf("%d", &n);
    while(n--) {
        for(int i = 0; i < 3; i++) {
            scanf("%s%s%s", left[i], right[i], verdict[i]);
            len[i] = strlen(left[i]);
        }
        pair<int,int> result = solve();
        printf("%c is the counterfeit coin and it is %s.\n", char(result.first + 'A'), ans[result.second]);
    }
    return 0;
}
