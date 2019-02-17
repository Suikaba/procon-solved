#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while(T--) {
        vector<string> b(8);
        for(int i = 0; i < 8; ++i) {
            cin >> b[i];
        }

        auto in_range = [&] (int y, int x) {
            return 0 <= y && y < 8 && 0 <= x && x < 8;
        };
        vector<vector<vector<int>>> ans(8, vector<vector<int>>(8, vector<int>(2)));
        function<void(int, int, int, int)> dfs = [&] (int y, int x, int t, int f) {
            if(!in_range(y, x) || ans[y][x][t] & (1 << f)) return;
            ans[y][x][t] |= (1 << f);
            dfs(y - 2, x - 2, !t, f);
            dfs(y - 2, x + 2, !t, f);
            dfs(y + 2, x - 2, !t, f);
            dfs(y + 2, x + 2, !t, f);
        };
        int itr = 0;
        for(int i = 0; i < 8; ++i) {
            for(int j = 0; j < 8; ++j) {
                if(b[i][j] != 'K') continue;
                dfs(i, j, 0, itr++);
            }
        }

        bool ok = false;
        for(int i = 0; i < 8; ++i) {
            for(int j = 0; j < 8; ++j) {
                for(int k = 0; k < 2; ++k) {
                    ok |= ans[i][j][k] == 3 && b[i][j] != '#';
                }
            }
        }

        cout << (ok ? "YES" : "NO") << endl;
    }
}
