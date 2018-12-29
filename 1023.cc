#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

string print_binary(int* binary, int k) {
    string res = "";
    for(int i = k - 1; i >= 0; i--) {
        res.append(1, binary[i] + '0');
    }
    return res;
}

bool solve(int* binary, char* bit, int k, bool positive) {
    int i = 0;
    while(i < k) {
        for(; i < k; i++) {
            if(binary[i] == 1 && bit[i] == (positive ? 'n' : 'p')) {
                break;
            }
        }
        if(i == k) {
            return true;
        }
        i++;
        for(; i < k; i++) {
            if(binary[i] == 0 && bit[i] == (positive ? 'p' : 'n')) {
                binary[i] = 1;
                break;
            }
            binary[i] = 1 - binary[i];
        }
        if(i == k) {
            return false;
        }
        i++;
    }
    return true;
}

string solve(char* bit, int k, long long N) {
    reverse(bit, bit+k);
    int *binary = new int[k];
    memset(binary, 0, sizeof(int)*k);
    bool positive = N >= 0;
    unsigned long long M = N >= 0 ? N : -N;
    int ptr = 0;
    while(ptr < k && M) {
        binary[ptr++] = M % 2;
        M >>= 1;
    }
    string res = "Impossible";
    if(!M && solve(binary, bit, k, positive)) {
        res = print_binary(binary, k);
    }
    delete[] binary;
    return res;
}

int main() {
    int t, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &k);
        char *bit = new char[k+1];
        scanf("%s", bit);
        long long N;
        scanf("%lld", &N);
        printf("%s\n", solve(bit, k, N).c_str());
        delete[] bit;
    }
    return 0;
}

/*
Input:
5
4
nppp
-5
4
ppnn
10
3
pnp
6
4
ppnn
-3
5
pnppn
11
--------------
Output:
1011
1110
Impossible
0011
11101
*/
