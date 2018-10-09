// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1618

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int d, w;
    while(cin >> d >> w, d) {
        vector<vector<int>> e(d, vector<int>(w));
        for(int i = 0; i < d; ++i) {
            for(int j = 0; j < w; ++j) {
                cin >> e[i][j];
            }
        }
        int ans = 0;
        for(int ly = 0; ly + 2 < d; ++ly) {
            for(int lx = 0; lx + 2 < w; ++lx) {
                for(int ry = ly + 2; ry < d; ++ry) {
                    for(int rx = lx + 2; rx < w; ++rx) {
                        int mini = inf;
                        for(int i = lx; i <= rx; ++i) {
                            mini = min({mini, e[ly][i], e[ry][i]});
                        }
                        for(int i = ly; i <= ry; ++i) {
                            mini = min({mini, e[i][lx], e[i][rx]});
                        }
                        int tans = 0;
                        for(int i = ly + 1; i <= ry - 1; ++i) {
                            for(int j = lx + 1; j <= rx - 1; ++j) {
                                if(e[i][j] >= mini) {
                                    tans = -inf;
                                }
                                tans += mini - e[i][j];
                            }
                        }
                        ans = max(ans, tans);
                    }
                }
            }
        }

        cout << ans << endl;
    }
}
