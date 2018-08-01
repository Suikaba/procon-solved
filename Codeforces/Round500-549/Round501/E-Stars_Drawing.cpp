
// http://codeforces.com/contest/1015/problem/E2

// 反省
// このど典型にどんだけ時間かけとんねん

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> fld(n);
    for(int i = 0; i < n; ++i) {
        cin >> fld[i];
    }
    vector<vector<int>> from_top(n, vector<int>(m));
    auto from_bottom = from_top, from_left = from_top, from_right = from_top;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(fld[i][j] == '.') {
                from_top[i][j] = from_left[i][j] = 0;
                continue;
            }
            if(i == 0) {
                from_top[i][j] = 1;
            } else {
                from_top[i][j] = from_top[i - 1][j] + 1;
            }
            if(j == 0) {
                from_left[i][j] = 1;
            } else {
                from_left[i][j] = from_left[i][j - 1] + 1;
            }
        }
    }
    for(int i = n - 1; i >= 0; --i) {
        for(int j = m - 1; j >= 0; --j) {
            if(fld[i][j] == '.') {
                from_bottom[i][j] = from_right[i][j] = 0;
                continue;
            }
            if(i == n - 1) {
                from_bottom[i][j] = 1;
            } else {
                from_bottom[i][j] = from_bottom[i + 1][j] + 1;
            }
            if(j == m - 1) {
                from_right[i][j] = 1;
            } else {
                from_right[i][j] = from_right[i][j + 1] + 1;
            }
        }
    }

    vector<tuple<int, int, int>> ans;
    vector<vector<int>> imos1(n + 1, vector<int>(m)); // vert
    vector<vector<int>> imos2(n, vector<int>(m + 1)); // hori
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            const int w = min({from_top[i][j], from_bottom[i][j], from_left[i][j], from_right[i][j]}) - 1;
            if(w >= 1) {
                imos1[i - w][j] += 1;
                imos1[i + w + 1][j] -= 1;
                imos2[i][j - w] += 1;
                imos2[i][j + w + 1] -= 1;
                ans.emplace_back(i + 1, j + 1, w);
            }
        }
    }

    for(int j = 0; j < m; ++j) {
        for(int i = 0; i < n; ++i) {
            imos1[i + 1][j] += imos1[i][j];
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            imos2[i][j + 1] += imos2[i][j];
        }
    }

    bool ok = true;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            ok &= fld[i][j] == '.' || imos1[i][j] >= 1 || imos2[i][j] >= 1;
        }
    }
    if(ok) {
        cout << ans.size() << endl;
        for(auto& t : ans) {
            cout << get<0>(t) << ' ' << get<1>(t) << ' ' << get<2>(t) << endl;
        }
    } else {
        cout << -1 << endl;
    }
}
