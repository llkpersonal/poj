#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

vector<ll> counts;
string str;

void init() {
    const int upper = 2147483647;
    ll total_count = 0;
    ll current_length = 0;
    int current_number = 1;
    str = "";
    char buff[10];
    while(total_count <= upper) {
        sprintf(buff, "%d", current_number);
        current_length = current_length + strlen(buff);
        total_count += current_length;
        current_number++;
        counts.push_back(total_count);
        str += buff;
    }
}

int binary_search(ll n) {
    int l = -1, r = counts.size() - 1;
    while(r - l > 1) {
        int m = (l+r) / 2;
        if(counts[m] >= n) r = m;
        else l = m;
    }
    return l;
}

int main() {
    init();
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int base = binary_search(n);
        printf("%c\n", base == -1 ? '1' : str[n - counts[base] - 1]);
    }
    return 0;
}
