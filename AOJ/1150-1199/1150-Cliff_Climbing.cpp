#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1150&lang=jp

constexpr int inf = 1e9;

int main() {
    int w, h;
    while(cin >> w >> h, w) {
        vector<vector<char>> s(h, vector<char>(w));
        vector<vector<vector<int>>> d(h, vector<vector<int>>(w, vector<int>(2, inf)));
        using state = tuple<int, int, int, int>;
        priority_queue<state, vector<state>, greater<state>> que;
        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < w; ++j) {
                cin >> s[i][j];
                if(s[i][j] == 'S') {
                    d[h - i - 1][j][0] = d[h - i - 1][j][1] = 0;
                    que.emplace(0, h - i - 1, j, 0);
                    que.emplace(0, h - i - 1, j, 1);
                }
            }
        }
        reverse(begin(s), end(s));
        while(!que.empty()) {
            int cur_d, y, x, step;
            tie(cur_d, y, x, step) = que.top();
            que.pop();
            if(cur_d > d[y][x][step]) continue;
            int inc = step == 0 ? 1 : -1;
            for(int i = 1; i <= 3; ++i) {
                for(int dy = -3 + i; dy <= 3 - i; ++dy) {
                    int ny = y + dy, nx = x + inc * i;
                    if(ny < 0 || h <= ny || nx < 0 || w <= nx || s[ny][nx] == 'X') continue;
                    int nxt_d = cur_d + (isalpha(s[ny][nx]) ? 0 : s[ny][nx] - '0');
                    if(d[ny][nx][!step] > nxt_d) {
                        que.emplace(nxt_d, ny, nx, !step);
                        d[ny][nx][!step] = nxt_d;
                    }
                }
            }
        }

        int ans = inf;
        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < w; ++j) {
                if(s[i][j] == 'T') {
                    ans = min({ans, d[i][j][0], d[i][j][1]});
                }
            }
        }
        cout << (ans == inf ? -1 : ans) << endl;
    }
}
