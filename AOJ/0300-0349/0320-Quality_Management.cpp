#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0320

int main() {
    int c, n;
    cin >> c >> n;
    vector<string> p(n);
    for(int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    int incorrect = 0;
    for(int i = 0; i < n / 2; ++i) {
        for(int j = 0; j < n / 2; ++j) {
            incorrect += p[i][j] != p[i][n - j - 1] || p[i][j] != p[n - i - 1][j];
        }
    }

    int ans = incorrect == 0;
    for(int i = 0; i < c - 1; ++i) {
        int d; cin >> d;
        for(int j = 0; j < d; ++j) {
            int r, c; cin >> r >> c;
            r--; c--;
            if(p[n - r - 1][c] == p[r][c] && p[r][c] == p[r][n - c - 1]) incorrect += 1;
            p[r][c] = (p[r][c] == '0') ? '1' : '0';
            if(p[n - r - 1][c] == p[r][c] && p[r][c] == p[r][n - c - 1]) incorrect -= 1;
        }
        ans += incorrect == 0;
    }

    cout << ans << endl;
}
