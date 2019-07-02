#include <bits/stdc++.h>
using namespace std;

constexpr int dx[4] = {0, 1, 0, -1};
constexpr int dy[4] = {1, 0, -1, 0};

bool dfs(int y, int x, vector<vector<int>>& S, vector<vector<int>> const& v) {
    const int h = S.size(), w = S[0].size();
    if(y == h && x == 0) return true;
    const int ny = (x == w - 1 ? y + 1 : y);
    const int nx = (x == w - 1 ? 0 : x + 1);
    if(v[y][x] == 1) {
        return dfs(ny, nx, S, v);
    } else {
        array<int, 4> use = {{0, 0, 1, 1}};
        auto in_range = [&] (int a, int b) {
            return 0 <= a && a < h && 0 <= b && b < w;
        };
        bool res = false;
        do {
            S[y][x] = 0;
            bool ok = true;
            auto searched = [&] (int yy, int xx) {
                return yy < y || (yy == y && xx < x);
            };
            for(int i = 0; i < 4 && ok; ++i) {
                if(!use[i]) {
                    const int rev = (i + 2) % 4;
                    const int yy = y + dy[i], xx = x + dx[i];
                    ok &= !in_range(yy, xx) || v[yy][xx] == 1 || !(S[yy][xx] & (1 << rev));
                } else {
                    S[y][x] |= 1 << i;
                    const int yy = y + dy[i], xx = x + dx[i];
                    const int rev = (i + 2) % 4;
                    ok &= in_range(yy, xx) && v[yy][xx] == 0 && (!searched(yy, xx) || (S[yy][xx] & (1 << rev)));
                }
            }
            if(ok) {
                res = dfs(ny, nx, S, v);
            }
        } while(!res && next_permutation(begin(use), end(use)));
        return res;
    }
}

int main() {
    int h, w;
    while(cin >> w >> h, h) {
        vector<vector<int>> c(h, vector<int>(w));
        int cnt = 0;
        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < w; ++j) {
                cin >> c[i][j];
                cnt += c[i][j] == 0;
            }
        }

        vector<vector<bool>> vis(h, vector<bool>(w));
        function<int(int, int)> connected = [&] (int y, int x) {
            vis[y][x] = true;
            int res = 1;
            for(int i = 0; i < 4; ++i) {
                const int ny = y + dy[i], nx = x + dx[i];
                if(0 <= ny && ny < h && 0 <= nx && nx < w && c[ny][nx] == 0 && !vis[ny][nx]) {
                    res += connected(ny, nx);
                }
            }
            return res;
        };
        const int sz = [&] {
            for(int i = 0; i < h; ++i) {
                for(int j = 0; j < w; ++j) {
                    if(c[i][j] == 0) {
                        return connected(i, j);
                    }
                }
            }
            return -1;
        }();
        vector<vector<int>> S(h, vector<int>(w));
        cout << (cnt > 0 && sz == cnt && dfs(0, 0, S, c) ? "Yes" : "No") << endl;
    }
}
