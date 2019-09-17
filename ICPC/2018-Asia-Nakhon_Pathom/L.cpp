#include <bits/stdc++.h>
using namespace std;

int sum[1024][1024];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int T; cin >> T;
    while(T--) {
        int r, c; cin >> r >> c;
        cin.ignore();
        for(int i = 1; i <= r; ++i) {
            string line;
            getline(cin, line);
            for(int j = 0; j < c; ++j) {
                sum[i][j + 1] = line[j * 2] == '1';
            }
        }
        for(int i = 1; i <= r; ++i) {
            for(int j = 0; j < c; ++j) {
                sum[i][j + 1] += sum[i][j];
            }
        }
        for(int i = 0; i < r; ++i) {
            for(int j = 1; j <= c; ++j) {
                sum[i + 1][j] += sum[i][j];
            }
        }

        auto calc = [&] (int y1, int x1, int y2, int x2) {
            return sum[y2][x2] - sum[y1][x2] - sum[y2][x1] + sum[y1][x1];
        };

        //int ans = 0;
        //for(int y = 0; y < r; ++y) {
        //    int l = 0, cur = 0; // cur pos = (y + cur, cur)
        //    while(y + cur <= r && calc(y + l, l, y + cur, cur) <= 1) {
        //        cur += 1;
        //    }
        //    ans = max(ans, cur - l - 1);
        //}
        //for(int x = 0; x < c; ++x) {
        //    int l = 0, cur = 0; // cur pos = (cur, x + cur)
        //    while(x + cur <= c && calc(l, x + l, cur, x + cur) <= 1) {
        //        cur += 1;
        //    }
        //    ans = max(ans, cur - l - 1);
        //}

        //cout << ans << endl;

        int ans = 0;
        for(int i = 1; i <= r; ++i) {
            for(int j = 1; j <= c; ++j) {
                int lb = 0, ub = min(i, j) + 1;
                while(ub - lb > 1) {
                    const int mid = (ub + lb) >> 1;
                    (calc(i - mid, j - mid, i, j) <= 1 ? lb : ub) = mid;
                }
                ans = max(ans, lb);
            }
        }

        cout << ans << endl;
    }
}
