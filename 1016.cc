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
        printf("%s\n", get_inventory(number).c_str());
    }
}
