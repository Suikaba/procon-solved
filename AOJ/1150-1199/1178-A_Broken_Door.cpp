#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1178

// 反省点
// 考察に抜けがあった．詰めが甘い．
// 具体的には，ダイクストラの状態に step 数を含めてやらないと，現時点ではだめだけど
// 後々それが最適解につながる状態が死んでしまうことに気がついてなかった．
// もうちょっと詰め切ってから書くべきかなあ．でも書きはじめて気づくこともあるので意外とバランスが難しい．

using pii = pair<int, int>;

constexpr int inf = 1e9;
constexpr int dx[4] = {0, 1, 0, -1};
constexpr int dy[4] = {1, 0, -1, 0};

int main() {
    int h, w;
    while(cin >> h >> w, h) {
        vector<vector<int>> horz(h - 1, vector<int>(w)), vert(h, vector<int>(w - 1));
        for(int i = 0; i < 2 * h - 1; ++i) {
            auto& v = (i & 1 ? horz : vert);
            for(int j = 0; j < w - 1 + (i & 1); ++j) {
                cin >> v[i / 2][j];
            }
        }

        auto in_range = [&] (int y, int x) {
            return 0 <= y && y < h && 0 <= x && x < w;
        };
        auto get_wall = [&] (int ny, int nx, int d) {
            if(d == 0) return &horz[ny - 1][nx];
            if(d == 1) return &vert[ny][nx - 1];
            if(d == 2) return &horz[ny][nx];
            if(d == 3) return &vert[ny][nx];
            assert(false);
        };
        std::function<int(int, int)> bfs = [&] (int sy, int sx) {
            queue<pii> que;
            vector<vector<int>> dist(h, vector<int>(w, inf));
            dist[sy][sx] = 0;
            que.emplace(sy, sx);
            while(!que.empty()) {
                auto p = que.front();
                const int y = p.first, x = p.second;
                que.pop();
                for(int i = 0; i < 4; ++i) {
                    int ny = y + dy[i], nx = x + dx[i];
                    if(!in_range(ny, nx) || *get_wall(ny, nx, i) == 1 || dist[ny][nx] != inf) continue;
                    dist[ny][nx] = dist[y][x] + 1;
                    que.emplace(ny, nx);
                }
            }
            return dist[h - 1][w - 1];
        };
        vector<vector<int>> broken_dist(h, vector<int>(w));
        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < w; ++j) {
                for(int d = 0; d < 4; ++d) {
                    int ny = i + dy[d], nx = j + dx[d];
                    if(!in_range(ny, nx) || *get_wall(ny, nx, d) == 1) continue;
                    *get_wall(ny, nx, d) = 1;
                    broken_dist[i][j] = max(broken_dist[i][j], bfs(i, j));
                    *get_wall(ny, nx, d) = 0;
                }
            }
        }

        using state = tuple<int, int, int, int>;
        vector<vector<vector<int>>> d(h, vector<vector<int>>(w, vector<int>(h * w, inf)));
        priority_queue<state, vector<state>, greater<state>> que;
        d[0][0][0] = broken_dist[0][0];
        que.emplace(broken_dist[0][0], 0, 0, 0);
        while(!que.empty()) {
            int cur_d, step, y, x;
            tie(cur_d, step, y, x) = que.top();
            que.pop();
            if(cur_d > d[y][x][step] || step + 1 >= h * w) continue;
            for(int i = 0; i < 4; ++i) {
                int ny = y + dy[i], nx = x + dx[i];
                if(!in_range(ny, nx) || *get_wall(ny, nx, i) == 1) continue;
                int nxt_d = max(cur_d, broken_dist[ny][nx] + step + 1);
                if(d[ny][nx][step + 1] > nxt_d) {
                    que.emplace(nxt_d, step + 1, ny, nx);
                    d[ny][nx][step + 1] = nxt_d;
                }
            }
        }

        const int ans = *min_element(begin(d[h - 1][w - 1]), end(d[h - 1][w - 1]));
        cout << (ans == inf ? -1 : ans) << endl;
    }
}
