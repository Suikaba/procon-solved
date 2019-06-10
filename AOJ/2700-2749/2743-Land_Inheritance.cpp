#include <bits/stdc++.h>
using namespace std;

int solve(int y1, int x1, int y2, int x2, int num, vector<vector<int>> const& sum) {
    auto calc = [&sum] (int yy1, int xx1, int yy2, int xx2) {
        return sum[yy2][xx2] - sum[yy1][xx2] - sum[yy2][xx1] + sum[yy1][xx1];
    };
    if(num == 1) return calc(y1, x1, y2, x2);
    int res = 0;
    for(int mx = x1; mx <= x2; ++mx) {
        res = max(res, min(calc(y1, x1, y2, mx), solve(y1, mx, y2, x2, num - 1, sum)));
        res = max(res, min(calc(y1, mx, y2, x2), solve(y1, x1, y2, mx, num - 1, sum)));
    }
    for(int my = y1; my <= y2; ++my) {
        res = max(res, min(calc(y1, x1, my, x2), solve(my, x1, y2, x2, num - 1, sum)));
        res = max(res, min(calc(my, x1, y2, x2), solve(y1, x1, my, x2, num - 1, sum)));
    }
    if(num == 4) {
        for(int my1 = y1; my1 <= y2; ++my1) {
            for(int my2 = y1; my2 <= y2; ++my2) {
                vector<int> v1(x2 + 1), v2(x2 + 1);
                for(int mx = x1; mx <= x2; ++mx) {
                    v1[mx] = min(calc(y1, x1, my1, mx), calc(y1, mx, my2, x2));
                    v2[mx] = min(calc(my1, x1, y2, mx), calc(my2, mx, y2, x2));
                }
                if(my1 < my2) swap(v1, v2);
                for(int mx = x1 + 1; mx <= x2; ++mx) {
                    v1[mx] = max(v1[mx], v1[mx - 1]);
                }
                for(int mx = x2 - 1; mx >= x1; --mx) {
                    v2[mx] = max(v2[mx], v2[mx + 1]);
                }
                if(my1 == my2) {
                    res = max(res, min(v1.back(), v2[0]));
                } else {
                    for(int mx = x1; mx <= x2; ++mx) {
                        res = max(res, min(v1[mx], v2[mx]));
                    }
                }
            }
        }
    }
    return res;
};

int main() {
    int h, w, n; cin >> h >> w >> n;
    vector<vector<int>> sum(h + 1, vector<int>(w + 1));
    for(int i = 1; i <= h; ++i) {
        for(int j = 1; j <= w; ++j) {
            cin >> sum[i][j];
        }
    }
    for(int i = 1; i <= h; ++i) {
        for(int j = 0; j < w; ++j) {
            sum[i][j + 1] += sum[i][j];
        }
    }
    for(int i = 0; i < h; ++i) {
        for(int j = 1; j <= w; ++j) {
            sum[i + 1][j] += sum[i][j];
        }
    }

    cout << solve(0, 0, h, w, n, sum) << endl;
}
