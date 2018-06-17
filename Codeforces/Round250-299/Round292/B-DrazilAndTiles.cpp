#include <bits/stdc++.h>
using namespace std;

// 反省点

// どう考えても実装方針が悪いんだけどどうすればよかったんだろう．

using pii = pair<int, int>;

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> fld(h);
    for(int i = 0; i < h; ++i) {
        cin >> fld[i];
    }

    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    auto in_range = [&](int y, int x) {
        return y >= 0 && y < h && 0 <= x && x < w;
    };

    vector<string> now = fld;
    vector<vector<int>> cnt(h, vector<int>(w));
    queue<tuple<int, int, int>> nxt_put;
    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            if(now[i][j] != '.') continue;
            for(int d = 0; d < 4; ++d) {
                int y = i + dy[d], x = j + dx[d];
                if(in_range(y, x) && now[y][x] == '.') {
                    cnt[i][j] += 1;
                }
            }
        }
    }
    bool debug = false;
    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            if(cnt[i][j] == 1) {
                for(int d = 0; d < 4; ++d) {
                    int ny = i + dy[d], nx = j + dx[d];
                    if(in_range(ny, nx) && now[ny][nx] == '.') {
                        if(debug) {
                            cout << "put: " << i << ' ' << j << ' ' << d << endl;
                        }
                        nxt_put.emplace(i, j, d);
                        cnt[i][j] = cnt[ny][nx] = 0;
                    }
                }
            }
        }
    }


    while(!nxt_put.empty()) {
        int y, x, dir;
        tie(y, x, dir) = nxt_put.front();
        if(debug) {
            cout << y << ' ' << x << ' ' << dir << endl;
        }
        nxt_put.pop();
        if(dir == 0 && now[y][x] == '.' && now[y + 1][x] == '.') {
            now[y][x] = '^';
            now[y + 1][x] = 'v';
        } else if(dir == 1 && now[y][x] == '.' && now[y][x + 1] == '.') {
            now[y][x] = '<';
            now[y][x + 1] = '>';
        } else if(dir == 2 && now[y][x] == '.' && now[y - 1][x] == '.') {
            now[y][x] = 'v';
            now[y - 1][x] = '^';
        } else if(now[y][x] == '.' && now[y][x - 1] == '.') {
            now[y][x] = '>';
            now[y][x - 1] = '<';
        }
        for(int d = 0; d < 4; ++d) {
            int y2 = y + dy[d], x2 = x + dx[d];
            if(in_range(y2, x2) && --cnt[y2][x2] == 1) {
                for(int d2 = 0; d2 < 4; ++d2) {
                    int y3 = y2 + dy[d2], x3 = x2 + dx[d2];
                    if(in_range(y3, x3) && now[y3][x3] == '.') {
                        nxt_put.emplace(y2, x2, d2);
                        cnt[y2][x2] = cnt[y3][x3] = 0;
                        break;
                    }
                }
            }

            int y3 = y + dy[dir] + dy[d], x3 = x + dx[dir] + dx[d];
            if(in_range(y3, x3) && --cnt[y3][x3] == 1) {
                for(int d2 = 0; d2 < 4; ++d2) {
                    int y4 = y3 + dy[d2], x4 = x3 + dx[d2];
                    if(in_range(y4, x4) && now[y4][x4] == '.') {
                        nxt_put.emplace(y3, x3, d2);
                        cnt[y3][x3] = cnt[y4][x4] = 0;
                        break;
                    }
                }
            }
        }
    }

    bool ok = true;
    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            ok &= now[i][j] != '.';
        }
    }

    if(ok) {
        for(auto& s : now) {
            cout << s << endl;
        }
    } else {
        cout << "Not unique" << endl;
    }
}
