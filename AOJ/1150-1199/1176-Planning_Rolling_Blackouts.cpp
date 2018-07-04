#include <bits/stdc++.h>
using namespace std;

// 反省点
// 条件式を書き間違えていた．

constexpr int inf = 1e9;
using pii = pair<int, int>;

template<typename T>
std::vector<T> table(int n, T v) { return std::vector<T>(n, v); }

template <class... Args>
auto table(int n, Args... args) {
    auto val = table(args...);
    return std::vector<decltype(val)>(n, std::move(val));
}

int main() {
    int h, w, s;
    while(cin >> h >> w >> s, h) {
        vector<vector<int>> u(h, vector<int>(w));
        vector<vector<int>> sum(h + 1, vector<int>(w + 1));
        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < w; ++j) {
                cin >> u[i][j];
                sum[i + 1][j + 1] = u[i][j];
            }
        }
        for(int i = 1; i <= h; ++i) {
            for(int j = 0; j < w; ++j) {
                sum[i][j + 1] += sum[i][j];
            }
        }
        for(int i = 0; i < h; ++i) {
            for(int j = 0; j <= w; ++j) {
                sum[i + 1][j] += sum[i][j];
            }
        }
        auto calc = [&] (int y1, int x1, int y2, int x2) {
            return sum[y2][x2] - sum[y2][x1] - sum[y1][x2] + sum[y1][x1];
        };

        auto dp = table(h + 1, w + 1, h + 1, w + 1, make_pair(-inf, -inf));
        function<pii(int, int, int, int)> rec = [&] (int y1, int x1, int y2, int x2) {
            if(dp[y1][x1][y2][x2].first != -inf) return dp[y1][x1][y2][x2];
            auto& res = dp[y1][x1][y2][x2];
            if(calc(0, 0, h, w) - calc(y1, x1, y2, x2) > s) {
                res.first = -1;
            } else {
                res.first = 1;
                res.second = s - (calc(0, 0, h, w) - calc(y1, x1, y2, x2));
            }
            for(int my = y1 + 1; my < y2; ++my) {
                auto t1 = rec(y1, x1, my, x2), t2 = rec(my, x1, y2, x2);
                if(min(t1.second, t2.second) < 0) continue;
                res = max(res, make_pair(t1.first + t2.first, min(t1.second, t2.second)));
            }
            for(int mx = x1 + 1; mx < x2; ++mx) {
                auto t1 = rec(y1, x1, y2, mx), t2 = rec(y1, mx, y2, x2);
                if(min(t1.second, t2.second) < 0) continue;
                res = max(res, make_pair(t1.first + t2.first, min(t1.second, t2.second)));
            }
            return res;
        };
        auto ans = rec(0, 0, h, w);
        cout << ans.first << ' ' << ans.second << endl;
    }
}
