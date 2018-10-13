// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1627

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while(cin >> n, n) {
        vector<vector<bool>> v(n, vector<bool>(n));
        int m; cin >> m;
        vector<int> win(n), lose(n);
        for(int i = 0; i < m; ++i) {
            int x, y; cin >> x >> y;
            v[x - 1][y - 1] = v[y - 1][x - 1] = true;
            win[x - 1] += 1;
            lose[y - 1] += 1;
        }

        function<int(int, int)> dfs = [&] (int y, int x) {
            for(int i = 0; i < n; ++i) {
                if(win[i] > (n - 1) / 2 || lose[i] > (n - 1) / 2) {
                    return 0;
                }
            }
            if(y == n) {
                return 1;
            }
            if(y == x || v[y][x]) {
                if(x == n - 1) return dfs(y + 1, 0);
                else           return dfs(y, x + 1);
            } else {
                int res = 0;

                win[y] += 1, lose[x] += 1;
                v[y][x] = v[x][y] = true;
                if(x == n - 1) res = dfs(y + 1, 0);
                else           res = dfs(y, x + 1);
                v[y][x] = v[x][y] = false;
                win[y] -= 1, lose[x] -= 1;

                lose[y] += 1, win[x] += 1;
                v[y][x] = v[x][y] = true;
                if(x == n - 1) res += dfs(y + 1, 0);
                else           res += dfs(y, x + 1);
                v[y][x] = v[x][y] = false;
                lose[y] -= 1, win[x] -= 1;

                return res;
            }
        };

        cout << dfs(0, 0) << endl;
    }
}
