#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1174&lang=jp

// 反省点
// 実装下手ですねぇ．bfs 2回書くのは流石にどうなの？
// でも dfs で実装サボろうとすると，変数をグローバルに置くか引数が爆発するかのどっちかなんだよな．
// そう考えるとまあ別にこれでもいいけど10分ぐらいで書こうな．

using pii = pair<int, int>;

constexpr int dx[4] = {0, -1, 0, 1};
constexpr int dy[4] = {1, 0, -1, 0};

int main() {
    int h, w, c;
    while(cin >> h >> w >> c, h) {
        vector<vector<int>> col(h, vector<int>(w));
        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < w; ++j) {
                cin >> col[i][j];
            }
        }
        auto in_range = [&] (int y, int x) {
            return 0 <= y && y < h && 0 <= x && x < w;
        };
        auto calc_col = [&] (vector<vector<int>> col) {
            if(col[0][0] != c) return 0;
            queue<pii> que;
            que.emplace(0, 0);
            vector<vector<bool>> vis(h, vector<bool>(w));
            vis[0][0] = true;
            int same_col = col[0][0] == c;
            while(!que.empty()) {
                auto p = que.front();
                que.pop();
                for(int i = 0; i < 4; ++i) {
                    int ny = p.first + dy[i], nx = p.second + dx[i];
                    if(!in_range(ny, nx) || vis[ny][nx]) continue;
                    vis[ny][nx] = true;
                    if(col[0][0] != col[ny][nx]) continue;
                    que.emplace(ny, nx);
                    same_col += col[ny][nx] == c;
                }
            }
            return same_col;
        };
        function<int(int, vector<vector<int>>)> solve = [&] (int depth, vector<vector<int>> col) {
            if(depth == 5) {
                return calc_col(col);
            } else {
                int res = calc_col(col);
                const int from = col[0][0];
                for(int to = 1; to <= 6; ++to) {
                    if(to == col[0][0]) continue;
                    queue<pii> que;
                    que.emplace(0, 0);
                    auto tcol = col;
                    tcol[0][0] = to;
                    while(!que.empty()) {
                        auto p = que.front();
                        que.pop();
                        for(int i = 0; i < 4; ++i) {
                            int ny = p.first + dy[i], nx = p.second + dx[i];
                            if(!in_range(ny, nx) || tcol[ny][nx] != from) continue;
                            que.emplace(ny, nx);
                            tcol[ny][nx] = to;
                        }
                    }
                    res = max(res, solve(depth + 1, tcol));
                }
                return res;
            }
        };

        cout << solve(0, col) << endl;
    }
}
