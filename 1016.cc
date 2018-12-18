#include <cstdio>
#include <cstring>
#include <map>
#include <string>
using namespace std;

string get_inventory(const string& str) {
    int cnt[10];
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < str.size(); i++) {
        cnt[str[i]-'0']++;
    }
    char t_cnt[5];
    string res = "";
    for(int i = 0; i < 10; i++) if(cnt[i]) {
        sprintf(t_cnt, "%d", cnt[i]);
        res += string(t_cnt);
        res.append(1, char(i+'0'));
    }
    return res;
}

int main() {
    char number[100];
    while(scanf("%s", number) != EOF) {
        if(!strcmp(number, "-1")) break;
        map<string, int> inventories;
        string inventory = number;
        inventories[inventory] = 0;
        int i;
        for(i = 1; i <= 15; i++) {
            inventory = get_inventory(inventory);
            if(inventories.find(inventory) != inventories.end()) {
                int k = i - inventories[inventory];
                if(k == 1) {
                    if(i == 1) printf("%s is self-inventorying\n", number);
                    else printf("%s is self-inventorying after %d steps\n", number, i - 1);
                } else {
                    printf("%s enters an inventory loop of length %d\n", number, k);
                }
                break;
            }
            inventories[inventory] = i;
        }
        if(i == 16) {
            printf("%s can not be classified after 15 iterations\n", number);
        }
    }
}
