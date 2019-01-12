#include <cstdio>
#include <vector>
using namespace std;

bool check(vector< vector<int> >& left,
           vector< vector<int> >& right,
           vector<char>& verdict,
           vector<int>& weight) {
    int n = left.size();
    for(int i = 0; i < n; i++) {
        int left_weight = 0, right_weight = 0;
        int m = left[i].size();
        for(int j = 0; j < m; j++) {
            left_weight += weight[left[i][j]];
            right_weight += weight[right[i][j]];
        }
        if((left_weight < right_weight && verdict[i] != '<')
           || (left_weight > right_weight && verdict[i] != '>')
           || (left_weight == right_weight && verdict[i] != '='))
            return false;
    }
    return true;
}

int main() {
    int N, K;
    char s[2];
    scanf("%d%d", &N, &K);
    vector<int> weight(N+1, 1);
    vector< vector<int> > left, right;
    vector<char> verdict;
    int p, a;
    for(int i = 0; i < K; i++) {
        scanf("%d", &p);
        vector<int> cur_left, cur_right;
        for(int j = 0; j < p; j++) {
            scanf("%d", &a);
            cur_left.push_back(a);
        }
        for(int j = 0; j < p; j++) {
            scanf("%d", &a);
            cur_right.push_back(a);
        }
        left.push_back(cur_left);
        right.push_back(cur_right);
        scanf("%s", s);
        verdict.push_back(s[0]);
    }
    
    int ans = 0, ans_count = 0;
    
    for(int i = 1; i <= N; i++) {
        weight[i] = 0;
        if(check(left, right, verdict, weight) && ans != i) {
            ans = i;
            ans_count ++;
        }
        weight[i] = 2;
        if(check(left, right, verdict, weight) && ans != i) {
            ans = i;
            ans_count ++;
        }
        weight[i] = 1;
    }
    
    if(ans_count != 1) printf("0\n");
    else printf("%d\n", ans);
    
    return 0;
}

