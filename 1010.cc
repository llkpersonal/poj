#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
using namespace std;

void find_maximum_types(vector<int>& types, int index, int last_index, int sum, int aim, int type_count, vector<int>& output, vector<int>& ans, int& ans_type_count, bool& tie) {
    if(sum > aim) return;
    if(sum == aim) {
        if(type_count > ans_type_count) {
            ans_type_count = type_count;
            ans = vector<int>(output);
            tie = false;
        } else if(type_count == ans_type_count) {
            if(output.size() < ans.size() || (output.size() == ans.size() && output[0] > ans[0])) {
                ans.clear();
                ans = vector<int>(output);
            } else if(output.size() == ans.size() && output[0] == ans[0]){
                tie = true;
            }
        }
        return;
    }
    
    if(output.size() == 4) return;
    
    int add_count = 0;
    output.push_back(types[index]);
    if(index != last_index) add_count = 1;
    find_maximum_types(types, index, index, sum+types[index], aim, type_count + add_count, output, ans, ans_type_count, tie);
    output.pop_back();
    if(index+1 < types.size()) {
        find_maximum_types(types, index+1, last_index, sum, aim, type_count, output, ans, ans_type_count, tie);
    }
}

int main() {
    int stamp_type;
    while(scanf("%d", &stamp_type) != EOF) {
        vector<int> types;
        types.push_back(stamp_type);
        while(scanf("%d", &stamp_type)==1 && stamp_type) {
            types.push_back(stamp_type);
        }
        sort(types.begin(), types.end(), greater<int>());
        int aim;
        while(scanf("%d", &aim) == 1 && aim) {
            vector<int> output, ans;
            int ans_type_count = 0;
            bool tie = false;
            find_maximum_types(types, 0, -1, 0, aim, 0, output, ans, ans_type_count, tie);
            if(ans.size() == 0) {
                printf("%d ---- none\n", aim);
            } else {
                sort(ans.begin(), ans.end());
                printf("%d (%d): ", aim, ans_type_count);
                if(tie) printf("tie\n");
                else {
                    for(int i = 0; i < ans.size(); i++) {
                        printf(i == ans.size() - 1 ? "%d\n":"%d ", ans[i]);
                    }
                }
            }
        }
    }
    return 0;
}
