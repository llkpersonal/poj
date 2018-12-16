#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct DnaString{
    char* dna_string;
    int unorder_count;
};

bool compare(const DnaString& a, const DnaString& b) {
    return a.unorder_count < b.unorder_count;
}

void freeDnaString(DnaString& dna) {
    delete[] dna.dna_string;
}

DnaString inputDnaString(int length) {
    DnaString res;
    res.dna_string = new char[length + 1];
    res.unorder_count = 0;
    scanf("%s", res.dna_string);
    return res;
}

int getUnorderCount(char* dna_string, int l, int r, char* buff) {
    int m = (l + r) >> 1;
    if(l + 1 == r) {
        return 0;
    }
    int count = 0;
    count += getUnorderCount(dna_string, l, m, buff);
    count += getUnorderCount(dna_string, m, r, buff);
    int ptr = 0;
    int ptr_l = l, ptr_r = m;
    while(ptr_l < m && ptr_r < r) {
        if(dna_string[ptr_r] < dna_string[ptr_l]) {
            buff[ptr++] = dna_string[ptr_r++];
            count += m - ptr_l;
        } else {
            buff[ptr++] = dna_string[ptr_l++];
        }
    }
    while(ptr_l < m) buff[ptr++] = dna_string[ptr_l++];
    while(ptr_r < r) buff[ptr++] = dna_string[ptr_r++];
    for(int i = l; i < r; i++) {
        dna_string[i] = buff[i - l];
    }
    return count;
}

int main() {
    int n, length;
    scanf("%d%d", &length, &n);
    vector<DnaString> dna_strings;
    for(int i = 0; i < n; i++) {
        DnaString dna_string = inputDnaString(length);
        dna_strings.push_back(dna_string);
    }
    char *buff = new char[length];
    char *dna_string = new char[length + 1];
    for(int i = 0; i < n; i++) {
        DnaString& current_dna = dna_strings[i];
        memcpy(dna_string, current_dna.dna_string, sizeof(char)*length);
        current_dna.unorder_count = getUnorderCount(dna_string, 0, length, buff);
    }
    delete[] buff;
    delete[] dna_string;
    sort(dna_strings.begin(), dna_strings.end(), compare);
    for(int i = 0; i < n; i++) {
        printf("%s\n", dna_strings[i].dna_string);
        freeDnaString(dna_strings[i]);
    }
    return 0;
}
