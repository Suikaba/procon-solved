#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

using pii = pair<int, int>;

constexpr int dx[4] = {0, 1, 0, -1};
constexpr int dy[4] = {1, 0, -1, 0};

template<typename T>
std::vector<T> table(int n, T v) { return std::vector<T>(n, v); }

template <class... Args>
auto table(int n, Args... args) {
    auto val = table(args...);
    return std::vector<decltype(val)>(n, std::move(val));
}

int main() {
    int h, w;
    while(cin >> h >> w, h) {
        vector<string> v(h);
        int sy = -1, sx = -1;
        for(int i = 0; i < h; ++i) {
            cin >> v[i];
            for(int j = 0; j < w; ++j) {
                if(v[i][j] == 'X' && sy == -1) {
                    sy = i, sx = j;
                }
            }
        }
        if(sy == 0 && sx == 0) {
            cout << 0 << endl;
            continue;
        }

        auto in_range = [&] (int y, int x) {
                            return 0 <= y && y < h && 0 <= x && x < w;
                        };
        auto is_king = [&] (int y, int x, int ky, int kx) {
            return    (y == ky && x == kx) || (y == ky + 1 && x == kx)
                   || (y == ky && x == kx + 1) || (y == ky + 1 && x == kx + 1);
        };
        auto d = table(h, w, 4, inf);
        auto calc_dist = [&] (int y1, int x1, int y2, int x2, int ky, int kx) {
            queue<tuple<int, int, int, int>> que;
            auto dist = table(h, w, h, w, inf);
            vector<int> sy2 = {y1, y2}, sx2 = {x1, x2};
            dist[sy2[0]][sx2[0]][sy2[1]][sx2[1]] = 0;
            que.emplace(sy2[0], sx2[0], sy2[1], sx2[1]);
            while(!que.empty()) {
                vector<int> y(2), x(2); tie(y[0], x[0], y[1], x[1]) = que.front();
                que.pop();
                for(int i = 0; i < 2; ++i) {
                    for(int j = 0; j < 4; ++j) {
                        const int ny = y[i] + dy[j], nx = x[i] + dx[j];
                        const int ny1 = (i == 0 ? ny : y[0]), nx1 = (i == 0 ? nx : x[0]);
                        const int ny2 = (i == 1 ? ny : y[1]), nx2 = (i == 1 ? nx : x[1]);
                        if(!in_range(ny, nx) || v[ny][nx] == '*' || is_king(ny, nx, ky, kx) || dist[ny1][nx1][ny2][nx2] != inf) continue;
                        dist[ny1][nx1][ny2][nx2] = dist[y[0]][x[0]][y[1]][x[1]] + 1;
                        que.emplace(ny1, nx1, ny2, nx2);
                    }
                }
            }
            return dist;
        };

        using S = tuple<int, int, int, int>;
        priority_queue<S, vector<S>, greater<>> que;
        { // calc initial
            vector<int> sy2, sx2;
            for(int i = 0; i < h; ++i) {
                for(int j = 0; j < w; ++j) {
                    if(v[i][j] == '.') sy2.push_back(i), sx2.push_back(j);
                }
            }
            auto init = calc_dist(sy2[0], sx2[0], sy2[1], sx2[1], sy, sx);
            if(sy + 2 < h) {
                d[sy][sx][0] = min(init[sy + 2][sx][sy + 2][sx + 1], init[sy + 2][sx + 1][sy + 2][sx]);
                if(d[sy][sx][0] != inf) que.emplace(d[sy][sx][0], sy, sx, 0);
            }
            if(sx + 2 < w) {
                d[sy][sx][1] = min(init[sy][sx + 2][sy + 1][sx + 2], init[sy + 1][sx + 2][sy][sx + 2]);
                if(d[sy][sx][1] != inf) que.emplace(d[sy][sx][1], sy, sx, 1);
            }
            if(sy - 1 >= 0) {
                d[sy][sx][2] = min(init[sy - 1][sx][sy - 1][sx + 1], init[sy - 1][sx + 1][sy - 1][sx]);
                if(d[sy][sx][2] != inf) que.emplace(d[sy][sx][2], sy, sx, 2);
            }
            if(sx - 1 >= 0) {
                d[sy][sx][3] = min(init[sy][sx - 1][sy + 1][sx - 1], init[sy + 1][sx - 1][sy][sx - 1]);
                if(d[sy][sx][3] != inf) que.emplace(d[sy][sx][3], sy, sx, 3);
            }
        }
        while(!que.empty()) {
            int cur_d, ky, kx, dir; tie(cur_d, ky, kx, dir) = que.top();
            que.pop();
            if(d[ky][kx][dir] < cur_d) continue;
            { // move king
                const int nky = ky + dy[dir], nkx = kx + dx[dir];
                if(d[nky][nkx][(dir + 2) % 4] > cur_d + 1) {
                    d[nky][nkx][(dir + 2) % 4] = cur_d + 1;
                    que.emplace(cur_d + 1, nky, nkx, (dir + 2) % 4);
                }
            }
            { // move empty cell
                int sy1, sx1, sy2, sx2;
                if(dir == 0) sy1 = ky + 2, sx1 = kx, sy2 = ky + 2, sx2 = kx + 1;
                if(dir == 1) sy1 = ky, sx1 = kx + 2, sy2 = ky + 1, sx2 = kx + 2;
                if(dir == 2) sy1 = ky - 1, sx1 = kx, sy2 = ky - 1, sx2 = kx + 1;
                if(dir == 3) sy1 = ky, sx1 = kx - 1, sy2 = ky + 1, sx2 = kx - 1;
                vector<queue<pii>> que2(2);
                auto d2 = table(h, w, 2, inf);
                que2[0].emplace(sy1, sx1), que2[1].emplace(sy2, sx2);
                d2[sy1][sx1][0] = 0, d2[sy2][sx2][1] = 0;
                for(int i = 0; i < 2; ++i) {
                    while(!que2[i].empty()) {
                        int y, x; tie(y, x) = que2[i].front();
                        que2[i].pop();
                        for(int j = 0; j < 4; ++j) {
                            const int ny = y + dy[j], nx = x + dx[j];
                            if(!in_range(ny, nx) || v[ny][nx] == '*' || is_king(ny, nx, ky, kx)) continue;
                            if(d2[ny][nx][i] != inf) continue;
                            d2[ny][nx][i] = d2[y][x][i] + 1;
                            que2[i].emplace(ny, nx);
                        }
                    }
                }
                vector<vector<int>> gy(4), gx(4);
                gy[2] = {ky - 1, ky - 1}, gx[2] = {kx, kx + 1};
                gy[3] = {ky, ky + 1}, gx[3] = {kx - 1, kx - 1};
                gy[0] = {ky + 2, ky + 2}, gx[0] = {kx, kx + 1};
                gy[1] = {ky, ky + 1}, gx[1] = {kx + 2, kx + 2};
                for(int ndir = 0; ndir < 4; ++ndir) {
                    if(!in_range(gy[ndir][0], gx[ndir][0]) || !in_range(gy[ndir][1], gx[ndir][1])) continue;
                    int cost = inf;
                    for(int j = 0; j < 2; ++j) {
                        cost = min(cost, d2[gy[ndir][0]][gx[ndir][0]][j] + d2[gy[ndir][1]][gx[ndir][1]][!j]);
                    }
                    if(cost == inf) continue;
                    if(d[ky][kx][ndir] > cur_d + cost) {
                        d[ky][kx][ndir] = cur_d + cost;
                        que.emplace(cur_d + cost, ky, kx, ndir);
                    }
                }
            }
        }

        const int ans = *min_element(begin(d[0][0]), end(d[0][0]));
        if(ans == inf) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }
}
