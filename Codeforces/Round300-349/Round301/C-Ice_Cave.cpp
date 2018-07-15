
// http://codeforces.com/contest/540/problem/C

// 反省点
// 普通に全パターン網羅できてなかった．
// 細かいところ詰めるの苦手すぎか？コーナーケースまみれの問題で訓練したほうがいいのかな．

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

constexpr int inf = 1e9;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> v(n);
    for(int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    r1--, c1--, r2--, c2--;

    queue<pii> que;
    que.emplace(r1, c1);
    constexpr int dx[4] = {0, 1, 0, -1};
    constexpr int dy[4] = {1, 0, -1, 0};
    vector<vector<int>> d(n, vector<int>(m, inf));
    d[r1][c1] = 0;
    auto in_range = [&] (int y, int x) {
        return 0 <= y && y < n && 0 <= x && x < m;
    };
    while(!que.empty()) {
        auto p = que.front();
        que.pop();
        for(int i = 0; i < 4; ++i) {
            int ny = p.first + dy[i], nx = p.second + dx[i];
            if(!in_range(ny, nx) || d[ny][nx] != inf) continue;
            if(v[ny][nx] == 'X' && (ny != r2 || nx != c2)) continue;
            d[ny][nx] = d[p.first][p.second] + 1;
            que.emplace(ny, nx);
        }
    }

    int cnt = 0;
    for(int i = 0; i < 4; ++i) {
        int y = r2 + dy[i], x = c2 + dx[i];
        if(!in_range(y, x)) continue;
        cnt += v[y][x] == '.';
    }

    bool ok = false;
    if(r2 == r1 && c2 == c1) {
        ok = cnt >= 1;
    } else if(abs(r1 - r2) + abs(c1 - c2) <= 1) {
        ok = v[r2][c2] == 'X' || cnt >= 1;
    } else {
        if(v[r2][c2] == '.') {
            ok = cnt >= 2 && d[r2][c2] != inf;
        } else {
            ok = d[r2][c2] != inf;
        }
    }
    cout << (ok ? "YES" : "NO") << endl;
}
