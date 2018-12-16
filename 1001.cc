#include <cstdio>
#include <cstring>
using namespace std;

struct BigDecimal{
    int *num;
    int dot_position;
    int len;
};

void freeBigDecimal(BigDecimal &decimal) {
    delete[] decimal.num;
}

BigDecimal multiply(BigDecimal* a, BigDecimal* b) {
    int len_a = a->len;
    int len_b = b->len;
    BigDecimal res;
    res.len = len_a + len_b;
    res.dot_position = a->dot_position + b->dot_position;
    res.num = new int[len_a + len_b];
    memset(res.num, 0, sizeof(int) * (len_a + len_b));
    for(int i = 0; i < len_a; i++) {
        int promote = 0;
        for(int j = 0; j < len_b; j++) {
            int d = i + j;
            int t = a->num[i] * b->num[j] + promote + res.num[d];
            res.num[d] = (t % 10);
            promote = t / 10;
        }
        int ptr = i + len_b;
        while(promote) {
            int t = res.num[ptr] + promote;
            res.num[ptr] = t % 10;
            promote = t / 10;
            ptr++;
        }
    }
    return res;
}

BigDecimal parseStrToBigDecimal(const char* R) {
    int len = strlen(R);
    BigDecimal decimal;
    decimal.dot_position = 0;
    decimal.num = new int[len];
    memset(decimal.num, 0, sizeof(int) * len);
    int ptr = 0;
    for(int i = len - 1; i >= 0; i--) {
        int pos = len - 1 - i;
        if(R[i] == '.') {
            decimal.dot_position = pos;
        } else {
            decimal.num[ptr++] = R[i] - '0';
        }
    }
    decimal.len = ptr;
    return decimal;
}

void printBigDecimal(BigDecimal& decimal) {
    char *str = new char[decimal.len+1];
    for(int i = 0; i <= decimal.len; i++) {
        str[i] = '0';
    }
    int ptr = 0;
    for(int i = 0; i < decimal.len; i++) {
        if(i == decimal.dot_position) str[ptr++] = '.';
        str[ptr++] = decimal.num[i] + '0';
    }
    int first = 0;
    int last = decimal.len;
    while(first <= decimal.len && str[first] == '0') first++;
    while(last >= 0 && str[last] == '0') last--;
    if(str[first] == '.') first++;
    
    if(first > last) printf("0\n");
    else {
        for(int i = last ; i >= first; i--) {
            printf("%c", str[i]);
        }
        printf("\n");
    }
    delete[] str;
}

int main() {
    char R[100];
    int n;
    BigDecimal ans;
    while(scanf("%s%d", R, &n) != EOF) {
        BigDecimal decimal = parseStrToBigDecimal(R);
        BigDecimal ans = parseStrToBigDecimal("1");
        for(int i = 0; i < n; i++) {
            BigDecimal t = multiply(&decimal, &ans);
            freeBigDecimal(ans);
            ans = t;
        }
        printBigDecimal(ans);
        freeBigDecimal(decimal);
        freeBigDecimal(ans);
    }
    return 0;
}
