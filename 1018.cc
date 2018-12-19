#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

double get_maximize_b_over_p(vector< vector<int> >& bandwidths, vector< vector<int> >& prices) {
    static double max_value[100][100];
    static double total_price[100][100];
    static double minimize_bandwidth[100][100];
    memset(max_value, 0, sizeof(max_value));
    memset(total_price, 0, sizeof(total_price));
    memset(minimize_bandwidth, 0, sizeof(minimize_bandwidth));
    
    int n = bandwidths.size();
    
    for(int j = 0; j < bandwidths[0].size(); j++) {
        max_value[0][j] = bandwidths[0][j] / prices[0][j];
        total_price[0][j] = prices[0][j];
        minimize_bandwidth[0][j] = bandwidths[0][j];
    }
    
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < bandwidths[i].size(); j++) {
            for(int k = 0; k < bandwidths[i-1].size(); k++) {
                double current_minimize_bandwidth = min(minimize_bandwidth[i-1][k], 1.0 * bandwidths[i][j]);
                double current_total_price = total_price[i-1][k] + prices[i][j];
                double current_value = current_minimize_bandwidth / current_total_price;
                if(max_value[i][j] < current_value) {
                    max_value[i][j] = current_value;
                    minimize_bandwidth[i][j] = current_minimize_bandwidth;
                    total_price[i][j] = current_total_price;
                }
            }
        }
    }
    
    double result = max_value[n-1][0];
    for(int j = 0; j < bandwidths[n-1].size(); j++) {
        result = max(result, max_value[n-1][j]);
    }
    return result;
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
