#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

void print_binary(int* binary, int k) {
    for(int i = k - 1; i >= 0; i--) {
        printf("%d", binary[i]);
    }
    printf("\n");
}

bool solve_positive(int* binary, char* bit, int k) {
    int i;
    for(i = 0; i < k; i++) {
        if(binary[i] == 1 && bit[i] == 'n') {
            break;
        }
    }
    if(i == k) {
        return true;
    }
    i++;
    for(; i < k; i++) {
        if(binary[i] == 0 && bit[i] == 'p') {
            binary[i] = 1;
            break;
        }
    }
    if(i == k) {
        return false;
    }
    return true;
}

bool solve_negative(int *binary, char* bit, int begin, long long N, int k) {
    if(begin == 0) {
        if(N == -1) {
            binary[0] = 1;
            return true;
        }
        else return false;
    }
    
    long long p = 0;
    p = (1ULL << begin);
    unsigned long long NN = -N;
    if(p > NN) {
        p = p - NN;
        int ptr = 0;
        while(ptr < begin && p) {
            binary[ptr++] = p % 2;
            p /= 2;
        }
        binary[begin] = 1;
        if(p) return false;
        return solve_positive(binary, bit, begin);
    } else if(p == NN) {
        binary[begin] = 1;
        return true;
    } else {
        binary[begin] = 1;
        int index = begin-1;
        for(; index >= 0; index--) {
            if(bit[index] == 'n') break;
        }
        if(index == -1) return false;
        return solve_negative(binary, bit, index, N+(1<<begin), k);
    }
}

int main() {
    int t, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &k);
        char *bit = new char[k+1];
        scanf("%s", bit);
        reverse(bit, bit+k);
        long long N;
        unsigned long long M;
        int upper = k;
        scanf("%I64d", &N);
        int *binary = new int[k];
        memset(binary, 0, sizeof(int)*k);
        if(N >= 0) {
            int ptr = 0;
            while(ptr < k && N) {
                binary[ptr++] = N % 2;
                N /= 2;
            }
            if(N == 0) {
                bool ans = solve_positive(binary, bit, k);
                if(ans) {
                    print_binary(binary, k);
                } else {
                    printf("Impossible\n");
                }
            } else {
                printf("Impossible\n");
            }
        } else {
            int i;
            for(i = k - 1; i >= 0; i--) {
                if(bit[i] == 'n') {
                    break;
                }
            }
            if(i == -1) {
                printf("Impossible\n");
            } else {
                bool ans = false;
                for(int i = k-1; i >= 0; i--) {
                    memset(binary, 0, sizeof(int)*k);
                    if(bit[i] == 'n') {
                        ans = solve_negative(binary, bit, i, N, k);
                        if(ans) break;
                    }
                }
                
                if(ans) {
                    print_binary(binary, k);
                } else {
                    printf("Impossible\n");
                }
            }
        }
        delete[] binary;
        delete[] bit;
    }
    return 0;
}

/*
5
 
4
nppp
-5
1011
 
4
ppnn
10
1110
 
3
pnp
6
Impossible
 
4
ppnn
-3
0011
 */
