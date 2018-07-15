
// http://codeforces.com/contest/538/problem/D

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n;
    cin >> n;
    vector<string> board(n);
    for(int i = 0; i < n; ++i) {
        cin >> board[i];
    }

    const int cy = n - 1, cx = n - 1;
    vector<string> ans(2 * n - 1, string(2 * n - 1, '?'));
    auto in_range = [&] (int y, int x) {
        return 0 <= y && y < n && 0 <= x && x < n;
    };
    auto in_range2 = [&] (int y, int x) {
        return 0 <= y && y < 2 * n - 1 && 0 <= x && x < 2 * n - 1;
    };
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(board[i][j] != 'o') continue;
            for(int dy = -n; dy <= n; ++dy) {
                for(int dx = -n; dx <= n; ++dx) {
                    int y = i + dy, x = j + dx;
                    if(!in_range(y, x) || !in_range2(cy + dy, cx + dx)) continue;
                    if(board[y][x] == '.') ans[cy + dy][cx + dx] = '.';
                }
            }
        }
    }
    for(int i = 0; i < 2 * n - 1; ++i) {
        for(int j = 0; j < 2 * n - 1; ++j) {
            if(ans[i][j] == '?') ans[i][j] = 'x';
        }
    }
    ans[n - 1][n - 1] = 'o';

    // check
    vector<string> check(n, string(n, '.'));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(board[i][j] != 'o') continue;
            check[i][j] = 'o';
            for(int dy = -n; dy <= n; ++dy) {
                for(int dx = -n; dx <= n; ++dx) {
                    int y = i + dy, x = j + dx;
                    if(!in_range(y, x) || !in_range2(cy + dy, cx + dx)) continue;
                    if(ans[cy + dy][cx + dx] == 'x' && check[y][x] != 'o') check[y][x] = 'x';
                }
            }
        }
    }

    if(check == board) {
        cout << "YES" << endl;
        for(auto& s : ans) {
            cout << s << endl;
        }
    } else {
        cout << "NO" << endl;
    }
}
