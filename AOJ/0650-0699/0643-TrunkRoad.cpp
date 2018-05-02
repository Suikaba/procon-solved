#include <bits/stdc++.h>
using namespace std;

// Trunk Road
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0643

constexpr int inf = 1e9;

int main() {
    int h, w;
    cin >> h >> w;
    vector<vector<int>> a(h, vector<int>(w));
    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            cin >> a[i][j];
        }
    }

    int ans = inf;
    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            int tans = 0;
            for(int k = 0; k < h; ++k) {
                for(int l = 0; l < w; ++l) {
                    tans += min(abs(i - k), abs(j - l)) * a[k][l];
                }
            }
            ans = min(ans, tans);
        }
    }

    cout << ans << endl;
}
