#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while(T--) {
        int n, k; cin >> n >> k;
        vector<string> v(3);
        for(int i = 0; i < 3; ++i) cin >> v[i];

        vector<vector<bool>> vis(3, vector<bool>(n));
        auto can_move = [&] (int y, int x, int ny, int nx) {
            if(ny < 0 || 3 <= ny || nx < 0) return false;
            if(x + 1 < n && v[y][x + 1] != '.') return false;
            if(x + 1 < n && v[ny][x + 1] != '.') return false;
            if(x + 2 < n && v[ny][x + 2] != '.') return false;
            if(x + 3 < n && v[ny][x + 3] != '.') return false;
            return true;
        };
        function<bool(int, int)> dfs = [&] (int y, int x) {
            if(x >= n) return true;
            if(vis[y][x]) return false;
            vis[y][x] = true;
            bool res = false;
            if(can_move(y, x, y, x + 3)) res |= dfs(y, x + 3);
            if(can_move(y, x, y + 1, x + 3)) res |= dfs(y + 1, x + 3);
            if(can_move(y, x, y - 1, x + 3)) res |= dfs(y - 1, x + 3);
            return res;
        };

        int sy = 0;
        for(int i = 0; i < 3; ++i) {
            if(v[i][0] == 's') sy = i;
        }
        cout << (dfs(sy, 0) ? "YES" : "NO") << endl;
    }
}
