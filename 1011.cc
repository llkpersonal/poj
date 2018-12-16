#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
using namespace std;

void calculate_factor(int x, vector<int>& factors) {
    for(int i = 1; i * i <= x; i++) {
        if(x % i == 0) {
            factors.push_back(i);
            if(x / i != i) {
                factors.push_back(x / i);
            }
        }
    }
    sort(factors.begin(), factors.end());
}

bool can(vector<int>& sticks, int index, int aim, int sum, vector<bool>& vis, const vector<int>& next) {
    vis[index] = true;
    sum += sticks[index];
    if(sum == aim) {
        for(int i = 0; i < sticks.size(); i++) {
            if(!vis[i]) {
                bool res = can(sticks, i, aim, 0, vis, next);
                if(!res) vis[index] = false;
                return res;
            }
        }
        return true;
    }
    
    for(int i = index+1; i < sticks.size(); i++) {
        if(!vis[i] && sum + sticks[i] <= aim) {
            bool res = can(sticks, i, aim, sum, vis, next);
            i = next[i];
            if(res) return true;
        }
    }
    
    vis[index] = false;
    return false;
}

int main() {
    int n;
    while(scanf("%d", &n) != EOF && n) {
        vector<int> sticks(n, 0);
        int sum_length = 0, max_length = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &sticks[i]);
            sum_length += sticks[i];
            max_length = max(max_length, sticks[i]);
        }
        sort(sticks.begin(), sticks.end(), greater<int>());
        vector<int> next(n, 0);
        for(int i = 0; i < n; i++) next[i] = i;
        for(int i = n-2; i >= 0; i--) {
            if(sticks[i+1] == sticks[i]) {
                next[i] = next[i+1];
            }
        }
        vector<int> factors;
        calculate_factor(sum_length, factors);
        vector<bool> vis(n, false);
        for(int i = 0; i < factors.size(); i++) {
            if(factors[i] >= max_length) {
                // printf("Current factor: %d\n", factors[i]);
                bool c = can(sticks, 0, factors[i], 0, vis, next);
                if(c) {
                    printf("%d\n", factors[i]);
                    break;
                }
            }
        }
    }
    return 0;
}
