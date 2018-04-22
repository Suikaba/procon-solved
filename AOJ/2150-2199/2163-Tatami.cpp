#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2163

int main() {
    int H, W;
    while(cin >> H >> W, H) {
        vector<vector<int>> tatami(H, vector<int>(W, -1));

        auto cond_check = [&](int y, int x) {
            return y == 0 || x == 0
            || tatami[y - 1][x - 1] == tatami[y - 1][x] || tatami[y][x - 1] == tatami[y][x]
            || tatami[y - 1][x - 1] == tatami[y][x - 1] || tatami[y - 1][x] == tatami[y][x];
        };

        long long id = 0;
        function<int(int, int)> solve = [&](int y, int x) {
            if(y == H - 1 && x == W - 1 && tatami[y][x] != -1) return 1;
            if(x >= W) return solve(y + 1, 0);
            if(tatami[y][x] != -1) return solve(y, x + 1);
            if(!cond_check(y, x)) return 0;

            int res = 0;
            if(y + 1 < H) { // put vert
                tatami[y][x] = tatami[y + 1][x] = id++;
                res += solve(y, x + 1);
                tatami[y][x] = tatami[y + 1][x] = -1;
            }
            if(x + 1 < W && tatami[y][x + 1] == -1) { // put hori
                tatami[y][x] = tatami[y][x + 1] = id++;
                res += solve(y, x + 1);
                tatami[y][x] = tatami[y][x + 1] = -1;
            }

            return res;
        };

        cout << solve(0, 0) << endl;
    }
}
