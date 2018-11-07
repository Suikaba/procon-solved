#include <bits/stdc++.h>
using namespace std;

int main() {
    auto compress = [&] (int c1, int c2) {
        if(c1 > c2) swap(c1, c2);
        if(c1 == c2) return 6;
        if(c1 == 0) return c2 - 1; // (0, 1), (0, 2), (0, 3);
        return c1 + c2;            // (1, 2), (1, 3), (2, 3)
    };

    int n; cin >> n;
    vector<vector<vector<int>>> g(4, vector<vector<int>>(4));
    vector<vector<int>> sum(4, vector<int>(4));
    for(int i = 0; i < n; ++i) {
        int c1, v, c2; cin >> c1 >> v >> c2;
        c1--, c2--;
        if(c1 > c2) swap(c1, c2);
        g[c1][c2].push_back(v);
        sum[c1][c2] += v;
    }
    for(int i = 0; i < 4; ++i) {
        for(int j = i; j < 4; ++j) {
            sort(begin(g[i][j]), end(g[i][j]));
        }
    }

    int ans = 0;
    for(int s = 0; s < 4; ++s) { // start vertex
        for(int S = 0; S < (1 << 6); ++S) {
            vector<bool> c(4); // connected ?
            c[s] = true;
            bool update = true;
            while(update) {
                update = false;
                for(int i = 0; i < 4; ++i) {
                    if(!c[i]) continue;
                    for(int j = 0; j < 4; ++j) {
                        if(c[j]) continue;
                        const bool erased = (S >> (compress(i, j))) & 1;
                        if((int)g[i][j].size() > erased) {
                            update = c[j] = true;
                        }
                        if((int)g[j][i].size() > erased) {
                            update = c[j] = true;
                        }
                    }
                }
            }

            int tans = 0;
            vector<int> deg(4);
            for(int i = 0; i < 4; ++i) {
                for(int j = i; j < 4; ++j) {
                    if(!c[i] || !c[j]) continue;
                    const bool erased = (S >> (compress(i, j))) & 1;
                    if((int)g[i][j].size() <= erased) continue;
                    tans += sum[i][j];
                    if(erased) {
                        tans -= g[i][j][0];
                    }
                    deg[i] += (int)g[i][j].size() - erased;
                    deg[j] += (int)g[i][j].size() - erased;
                }
            }

            int cnt = 0;
            for(int i = 0; i < 4; ++i) {
                cnt += deg[i] & 1;
            }
            if(cnt <= 2) {
                ans = max(ans, tans);
            }
        }
    }

    cout << ans << endl;
}
