#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

struct RlePair {
    int pixel_value;
    int run_length;
};

void addOutput(vector<RlePair>& output, RlePair& output_pair) {
    int m = output.size();
    if(m > 0 && output_pair.pixel_value == output[m-1].pixel_value) {
        output[m-1].run_length += output_pair.run_length;
    } else {
        output.push_back(output_pair);
    }
}

bool check(int x, int y, int width, int height) {
    return x >= 0 && x < height && y >= 0 && y < width;
}

bool compare(const RlePair& a, const RlePair& b) {
    return a.run_length < b.run_length;
}

int getPixel(int x, int y, int width, vector<RlePair>& rle_pairs) {
    int index = x * width + y;
    int l = 0, r = rle_pairs.size();
    while(r - l > 1) {
        int m = (l+r) >> 1;
        if(rle_pairs[m].run_length > index) r = m;
        else l = m;
    }
    return rle_pairs[l].pixel_value;
}

pair<int, int> getCoordinates(int index, int width) {
    int x = index / width;
    int y = index % width;
    return make_pair(x, y);
}

int getEdgePixel(int x, int y, int width, int height, int current_pixel, vector<RlePair>& rle_pairs) {
    int max_absolute_pixel = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if(i == 0 && j == 0) continue;
            int dx = x + i;
            int dy = y + j;
            if(check(dx, dy, width, height)) {
                int pixel = getPixel(dx, dy, width, rle_pairs);
                max_absolute_pixel = max(max_absolute_pixel, abs(current_pixel - pixel));
            }
        }
    }
    return max_absolute_pixel;
}

void edgeDetect(int width, vector<RlePair>& rle_pairs, vector<RlePair>& output) {
    output.clear();
    vector<RlePair> total;
    int sum = 0;
    for(int i = 0; i < rle_pairs.size(); ++i) {
        RlePair t_pair;
        t_pair.pixel_value = rle_pairs[i].pixel_value;
        t_pair.run_length = sum;
        sum += rle_pairs[i].run_length;
        total.push_back(t_pair);
    }
    vector<RlePair> t_output;
    int height = sum / width;
/*
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; j++) {
            int pixel = getPixel(i, j, width, total);
            int c_pixel = getEdgePixel(i, j, width, height, pixel, total);
            RlePair output_pair;
            output_pair.pixel_value = c_pixel;
            output_pair.run_length = 1;
            addOutput(output, output_pair);
        }
    }
    
    return;
*/
    sum = 0;
    set< pair<int, int> > s;
    for(int i = 0; i < rle_pairs.size(); ++i) {
        RlePair& current_pair = rle_pairs[i];
        pair<int, int> coordinate = getCoordinates(sum, width);
        int x = coordinate.first, y = coordinate.second;
        for(int dx = -1; dx <= 1; dx++) {
            for(int dy = -1; dy <= 1; dy++) {
                int nx = x + dx, ny = y + dy;
                if(check(nx, ny, width, height) && s.find(make_pair(nx, ny)) == s.end()) {
                    s.insert(make_pair(nx, ny));
                    RlePair t_pair;
                    int current_pixel = getPixel(nx, ny, width, total);
                    t_pair.pixel_value = getEdgePixel(nx, ny, width, height, current_pixel, total);
                    t_pair.run_length = nx * width + ny;
                    t_output.push_back(t_pair);
                }
            }
        }
        sum += current_pair.run_length;
    }
    sort(t_output.begin(), t_output.end(), compare);
    
    for(int i = 0; i < t_output.size(); i++) {
        RlePair output_pair;
        if(i == t_output.size() - 1) {
            output_pair.run_length = sum - t_output[i].run_length;
        } else {
            output_pair.run_length = t_output[i+1].run_length - t_output[i].run_length;
        }
        output_pair.pixel_value = t_output[i].pixel_value;
        addOutput(output, output_pair);
    }
}

int main() {
    int width, pixel_value, run_length;
    RlePair rle_pair;
    while(scanf("%d", &width) && width) {
        vector<RlePair> rle_pairs;
        while(true) {
            scanf("%d%d", &pixel_value, &run_length);
            rle_pair.pixel_value = pixel_value;
            rle_pair.run_length = run_length;
            rle_pairs.push_back(rle_pair);
            if(pixel_value == 0 && run_length == 0) break;
        }
        vector<RlePair> output;
        edgeDetect(width, rle_pairs, output);
        printf("%d\n", width);
        for(int i = 0; i < output.size(); i++) {
            printf("%d %d\n", output[i].pixel_value, output[i].run_length);
        }
        printf("0 0\n");
    }
    printf("0\n");
    return 0;
}

/*
 30
 10 41
 20 41
 15 41
 30 41
 25 41
 0 5
 0 0
 ==
 30
 0 10
 10 62
 5 20
 15 62
 5 20
 25 6
 5 15
 0 9
 25 6
 0 0
 */
