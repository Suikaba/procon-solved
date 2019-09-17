#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

const int inf = 1e9;

const int dy[4] = {0, 1, 0, -1};
const int dx[4] = {1, 0, -1, 0};

int main() {
    int n, m, k;
    while(cin >> n >> m >> k, n != 0) {
        vector<string> v(n);
        for(int i = 0; i < n; ++i) {
            cin >> v[i];
        }

        int sy, sx, gy, gx;
        queue<pii> que;
        vector<vector<int>> fire(n, vector<int>(m, inf));
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(v[i][j] == 'f') {
                    fire[i][j] = 0;
                    que.emplace(i, j);
                }
                if(v[i][j] == 's') {
                    sy = i, sx = j;
                }
                if(v[i][j] == 't') {
                    gy = i, gx = j;
                }
            }
        }

        auto is_range = [&] (int y, int x) {
            return 0 <= y && y < n && 0 <= x && x < m;
        };

        while(!que.empty()) {
            const int y = que.front().first, x = que.front().second;
            que.pop();
            for(int dy = -1; dy <= 1; ++dy) {
                for(int dx = -1; dx <= 1; ++dx) {
                    const int ny = y + dy, nx = x + dx;
                    if(!is_range(ny, nx) || fire[ny][nx] < fire[y][x] + k) continue;
                    fire[ny][nx] = fire[y][x] + k;
                    que.emplace(ny, nx);
                }
            }
        }

        vector<vector<int>> d(n, vector<int>(m, inf));
        d[sy][sx] = 0;
        que.emplace(sy, sx);
        while(!que.empty()) {
            const int y = que.front().first, x = que.front().second;
            que.pop();
            for(int i = 0; i < 4; ++i) {
                const int ny = y + dy[i], nx = x + dx[i];
                if(!is_range(ny, nx) || d[ny][nx] != inf || fire[ny][nx] <= d[y][x] + 1) continue;
                d[ny][nx] = d[y][x] + 1;
                que.emplace(ny, nx);
            }
        }

        if(d[gy][gx] == inf) {
            cout << "Impossible" << endl;
        } else {
            cout << d[gy][gx] << endl;
        }
    }
}