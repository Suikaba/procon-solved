#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 2e9;

int main() {
    int w, h; cin >> w >> h;
    vector<vector<int>> s(h, vector<int>(w));
    vector<vector<int>> hsum(h, vector<int>(w + 1));
    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            cin >> s[i][j];
        }
    }
    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            hsum[i][j + 1] += hsum[i][j] + s[i][j];
        }
    }

    vector<vector<int>> dp(h + 1, vector<int>(w + 1, inf));
    dp[h][w] = 0;
    function<int(int, int)> solve = [&] (int y, int x) {
        assert(y < (int)dp.size() && x < (int)dp[y].size());
        if(dp[y][x] != inf) return dp[y][x];
        const int turn = (y + x) & 1;
        int& res = dp[y][x] = (turn == 0 ? -inf : inf);
        if(y != h) {
            if(turn == 0) res = max(res, solve(y + 1, x) + (hsum[y][w] - hsum[y][x]) - hsum[y][x]);
            else          res = min(res, solve(y + 1, x) + (hsum[y][w] - hsum[y][x]) - hsum[y][x]);
        }
        if(x != w) {
            if(turn == 0) res = max(res, solve(y, x + 1));
            else          res = min(res, solve(y, x + 1));
        }
        return res;
    };

    cout << abs(solve(0, 0)) << endl;
}
