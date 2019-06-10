#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

template<typename T>
std::vector<T> table(int n, T v) { return std::vector<T>(n, v); }

template <class... Args>
auto table(int n, Args... args) {
    auto val = table(args...);
    return std::vector<decltype(val)>(n, std::move(val));
}

constexpr int dx[3] = {1, 0, -1};
constexpr int dy[2][3] = {
    {0, 1, 0}, // (x + y) % 2 == 0
    {0, -1, 0}
};

constexpr int df[20][2][3] = {
    {{1, 5, 4}, {4, 5, 1}},
    {{2, 6, 0}, {0, 6, 2}},
    {{3, 7, 1}, {1, 7, 3}},
    {{4, 8, 2}, {2, 8, 4}},
    {{0, 9, 3}, {3, 9, 0}},
    {{10, 0, 11}, {11, 0, 10}},
    {{11, 1, 12}, {12, 1, 11}},
    {{12, 2, 13}, {13, 2, 12}},
    {{13, 3, 14}, {14, 3, 13}},
    {{14, 4, 10}, {10, 4, 14}},
    {{5, 15, 9}, {9, 15, 5}},
    {{6, 16, 5}, {5, 16, 6}},
    {{7, 17, 6}, {6, 17, 7}},
    {{8, 18, 7}, {7, 18, 8}},
    {{9, 19, 8}, {8, 19, 9}},
    {{19, 10, 16}, {16, 10, 19}},
    {{15, 11, 17}, {17, 11, 15}},
    {{16, 12, 18}, {18, 12, 16}},
    {{17, 13, 19}, {19, 13, 17}},
    {{18, 14, 15}, {15, 14, 18}}
};
constexpr int dd[3][2][3] = { // only used on 0, ..., 4, 15, ..., 19
    {{2, 0, 1}, {1, 0, 2}},
    {{1, 2, 0}, {0, 2, 1}},
    {{0, 1, 2}, {2, 1, 0}}
};

int main() {
    constexpr int max_x = 201, max_y = 102;
    constexpr int cx = 100, cy = 50;
    auto in_range = [] (int x, int y) {
        return 0 <= x && x < max_x && 0 <= y && y < max_y;
    };

    int gx, gy, n;
    while(cin >> gx >> gy >> n, gx | gy | n) {
        gx += cx, gy += cy;
        auto d = table(max_x, max_y, 20, 3, inf);
        d[cx][cy][0][0] = 0;
        queue<tuple<int, int, int, int>> que;
        que.emplace(cx, cy, 0, 0);
        int ans = inf;
        while(!que.empty()) {
            int x, y, f, dir; tie(x, y, f, dir) = que.front();
            que.pop();
            if(x == gx && y == gy && f == n) {
                ans = d[x][y][f][dir];
                break;
            }
            for(int i = 0; i < 3; ++i) {
                const int nx = x + dx[i], ny = y + dy[(x + y) & 1][i];
                int nf = 0, nd = 0;
                if((x + y) & 1) {
                    nf = df[f][1][(i - dir + 3) % 3];
                } else {
                    nf = df[f][0][(i + dir) % 3];
                }
                if((5 <= f && f < 15) || (5 <= nf && nf < 15)) {
                    nd = dir;
                } else {
                    nd = dd[dir][(x + y) & 1][i];
                }
                if(!in_range(nx, ny) || d[nx][ny][nf][nd] != inf) continue;
                d[nx][ny][nf][nd] = d[x][y][f][dir] + 1;
                que.emplace(nx, ny, nf, nd);
            }
        }

        cout << ans << endl;
    }
}
