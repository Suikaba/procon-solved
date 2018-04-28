#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

constexpr int dx[4] = {0, 1, 0, -1};
constexpr int dy[4] = {1, 0, -1, 0};

class DungeonEscape {
public:
    int exitTime(vector <string> up, vector <string> down, vector <string> east, vector <string> west, int startLevel, int startEasting) {
        const int n = up.size(), m = up[0].size();
        vector<vector<string>> w = {down, east, up, west};
        vector<vector<int>> d(n, vector<int>(m, inf));
        d[startLevel][startEasting] = 0;

        auto is_in = [&](int y, int x) {
            return -1 <= y && y < n && 0 <= x && x < m;
        };

        // (y, x, d)
        using state = tuple<int, int, int>;
        priority_queue<state, vector<state>, greater<state>> que;
        que.emplace(startLevel, startEasting, 0);
        int ans = inf;
        while(!que.empty()) {
            int y, x, cur_d;
            tie(y, x, cur_d) = que.top();
            que.pop();
            if(y == -1) {
                ans = min(ans, cur_d);
                continue;
            }
            if(cur_d > d[y][x]) continue;
            for(int i = 0; i < 4; ++i) {
                int nd = cur_d + (w[i][y][x] == 'x' ? inf : w[i][y][x] - '0');
                int ny = y + dy[i], nx = x + dx[i];
                if(!is_in(ny, nx)) continue;
                if(ny == -1) {
                    que.emplace(ny, nx, nd);
                } else {
                    if(d[ny][nx] > nd && nd < (n - ny) * m) {
                        que.emplace(ny, nx, nd);
                        d[ny][nx] = nd;
                    }
                }
            }
        }
        return (ans == inf ? -1 : ans);
    }
};
