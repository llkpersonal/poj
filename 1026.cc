#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

void roll(char* text, vector<int>& roll_vec, int k) {
    int n = roll_vec.size();
    char t_text[222];
    for(int i = 0; text[i] != '\0'; i++) {
        t_text[i] = text[i];
    }
    for(int i = 0; i < n; i++) {
        int id = (i+k)%n;
        t_text[roll_vec[id]] = text[roll_vec[i]];
    }
    for(int i = 0; text[i] != '\0'; i++) {
        text[i] = t_text[i];
    }
}

void encode(const char* raw_text, char* output_text, int n, vector<int>& p, int k) {
    int i;
    for(i = 0; raw_text[i]; i++) {
        output_text[i] = raw_text[i];
    }
    while(i < n) {
        output_text[i++] = ' ';
    }
    output_text[i] = '\0';

    vector<bool> vis(n, false);
    vector<int> pc;
    for(i = 0; i < n; i++) {
        if(!vis[i]) {
            pc.clear();
            int id = i;
            do{
                vis[id] = true;
                pc.push_back(id);
                id = p[id];
            } while(id != i);
            int mod = pc.size();
            int k_count = k % mod;
            roll(output_text, pc, k_count);
        }
    }
}

int main() {
    int n;
    char raw_text[222];
    while(scanf("%d", &n) != EOF && n) {
        vector<int> p(n, 0);
        for(int i = 0; i < n; i++) {
            scanf("%d", &p[i]);
            p[i]--;
        }
        int k;
        while(scanf("%d", &k)!=0 && k) {
            getchar();
            gets(raw_text);
            char output_text[222];
            encode(raw_text, output_text, n, p, k);
            puts(output_text);
        }
        printf("\n");
    }
    return 0;
}
