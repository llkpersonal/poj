#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

char directory[] = "22233344455566677778889999";
int m[10000000];

int mapStringToPhone(const char* str) {
    int len = strlen(str);
    int phone = 0;
    for(int i = 0; i < len; i++) {
        if(str[i] != '-') {
            if(isalpha(str[i])) phone = phone * 10 + directory[str[i]-'A'] - '0';
            else phone = phone * 10 + str[i] - '0';
        }
    }
    return phone;
}

int main() {
    int n;
    scanf("%d", &n);
    char phone_number[100];
    for(int i = 0; i < n; i++) {
        scanf("%s", phone_number);
        int phone = mapStringToPhone(phone_number);
        m[phone]++;
    }
    
    bool has_duplicate = false;
    for(int i = 0; i < 10000000; i++) {
        if(m[i] > 1) has_duplicate = true;
    }
    
    if(!has_duplicate) {
        printf("No duplicates.\n");
    } else {
        for(int i = 0; i < 10000000; i++) {
            if(m[i] > 1) {
                printf("%03d-%04d %d\n", i / 10000, i % 10000, m[i]);
            }
        }
    }
    return 0;
}
