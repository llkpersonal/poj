#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
using namespace std;

bool can(int s, vector<int>& sides, int placed, int n, vector<int>& column) {
    if(placed == n) {
        return true;
    }
    
    int next_column = 0;
    for(int i = 1; i < s; i++) {
        if(column[i] < column[next_column]) {
            next_column = i;
        }
    }
    
    for(int i = 10; i >= 1; i--) {
        if(sides[i] == 0 || i+column[next_column] > s || next_column+i > s) {
            continue;
        }
        
        bool can_place = true;
        for(int j = next_column; j < next_column+i; j++) {
            if(column[j] > column[next_column]) {
                can_place = false;
                break;
            }
        }
        if(!can_place) continue;
        
        sides[i]--;
        for(int j = next_column; j < next_column+i; j++) {
            column[j] += i;
        }
        
        if(can(s, sides, placed+1, n, column)) {
            return true;
        }
        
        sides[i]++;
        for(int j = next_column; j < next_column+i; j++) {
            column[j] -= i;
        }
    }
    
    return false;
}

int main() {
    int t, s, n, side;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &s, &n);
        vector<int> sides(11, 0);
        for(int i = 0; i < n; i++) {
            scanf("%d", &side);
            sides[side]++;
        }
        vector<int> column(s, 0);
        bool ans = can(s, sides, 0, n, column);
        printf(ans?"KHOOOOB!\n":"HUTUTU!\n");
    }
    return 0;
}
