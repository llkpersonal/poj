#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

void roll(char* text, vector<int>& roll_vec) {
    int n = roll_vec.size();
    char c = text[roll_vec[0]];
    for(int i = 0; i < n-1; i++) {
        int p = roll_vec[i];
        int q = roll_vec[i+1];
        c = text[q];
        text[q] = text[p];
    }
    text[roll_vec[0]] = c;
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
            pc.push_back(i);
            int id = i;
            do{
                vis[id] = true;
                pc.push_back(id);
                id = p[id];
            } while(id != i);
            int mod = pc.size();
            int k_count = k % mod;
            while(k_count--) {
                roll(output_text, pc);
            }
        }
    }
}

void print_output_text(const char* output_text, int n) {
    for(int i = 0; i < n; i++) printf("%c", output_text[i]);
    printf("\n");
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
        scanf("%d", &k);
        gets(raw_text);
        char output_text[222];
        encode(raw_text, output_text, n, p, k);
        print_output_text(output_text, n);
    }
    return 0;
}
