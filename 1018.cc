#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iterator>
#include <map>
#include <vector>
using namespace std;

double get_maximize_b_over_p(vector< vector<int> >& bandwidths, vector< vector<int> >& prices) {
    map<int, int> devices[2];
    for(int i = 0; i < bandwidths[0].size(); i++) {
        devices[0][bandwidths[0][i]] = prices[0][i];
    }
    
    for(int i = 1; i < bandwidths.size(); i++) {
        map<int, int>& c_device = devices[i%2];
        map<int, int>& p_device = devices[(i-1)%2];
        c_device.clear();
        for(int j = 0; j < bandwidths[i].size(); j++) {
            for(map<int,int>::iterator it = p_device.begin(); it != p_device.end(); ++it) {
                int bandwidth = min(it->first, bandwidths[i][j]);
                int price = it->second + prices[i][j];
                map<int,int>::iterator c_it = c_device.find(bandwidth);
                if(c_it == c_device.end()) {
                    c_device[bandwidth] = price;
                } else {
                    c_it->second = min(c_it->second, price);
                }
            }
        }
    }
    
    int n = bandwidths.size();
    map<int,int>& c_device = devices[(n-1) % 2];
    double res = 0;
    for(map<int,int>::iterator it = c_device.begin(); it != c_device.end(); ++it) {
        res = max(res, 1.0 * it->first / it->second);
    }
    return res;
}

int main() {
    int t, n, m;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        vector< vector<int> > bandwidths, prices;
        for(int i = 0; i < n; i++) {
            scanf("%d", &m);
            vector<int> bandwidth(m, 0), price(m, 0);
            for(int j = 0; j < m; j++) {
                scanf("%d%d", &bandwidth[j], &price[j]);
            }
            bandwidths.push_back(bandwidth);
            prices.push_back(price);
        }
        
        double result = get_maximize_b_over_p(bandwidths, prices);
        printf("%.3f\n", result);
    }
    return 0;
}
