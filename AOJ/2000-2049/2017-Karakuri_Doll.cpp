#include <bits/stdc++.h>
using namespace std;

// direction
// 0: N, 1: E, 2:S, 3:W
constexpr int dx[4] = {0, 1, 0, -1};
constexpr int dy[4] = {-1, 0, 1, 0};
constexpr int dd[2] = {1, 3}; // turn right, left

bool reach1[16][64][4]; // only go to kitchen
bool reach[16][64][4][16][64][4];

int main() {
    int w, h;
    while(cin >> w >> h, w) {
        memset(reach1, false, sizeof(reach1));
        memset(reach, false, sizeof(reach));
        vector<string> v(h);
        for(auto& s : v) cin >> s;

        int sy = -1, sx = -1, sd = -1, gy = -1, gx = -1;
        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < w; ++j) {
                if(v[i][j] == '#') continue;
                if(v[i][j] == 'K') {
                    sy = i, sx = j;
                    for(int d = 0; d < 4; ++d) {
                        if(v[sy + dy[d]][sx + dx[d]] == '#') continue;
                        sd = d;
                    }
                }
                if(v[i][j] == 'M') {
                    gy = i, gx = j;
                }
            }
        }

        function<bool(int, int, int)> go_to_kitchen = [&] (int y, int x, int d) {
            if(reach1[y][x][d]) return false;
            reach1[y][x][d] = true;
            if(y == gy && x == gx) return true;
            bool res = false;
            if(v[y + dy[d]][x + dx[d]] != '#') {
                res = go_to_kitchen(y + dy[d], x + dx[d], d);
            } else {
                res = go_to_kitchen(y, x, (d + 1) % 4);
                res |= go_to_kitchen(y, x, (d + 3) % 4);
            }
            return res;
        };
        function<bool(int, int, int, int, int, int)> dfs = [&] (int y1, int x1, int d1, int y2, int x2, int d2) {
            if(reach[y1][x1][d1][y2][x2][d2]) return false;
            reach[y1][x1][d1][y2][x2][d2] = true;
            if(gy == y2 && gx == x2 && gy == y1 && gx == x1
               && v[y2 - dy[d2]][x2 - dx[d2]] != '#' && v[y1 + dy[d1]][x1 + dx[d1]] == '#') {
                return true;
            }
            bool res = false;
            if(v[y1 + dy[d1]][x1 + dx[d1]] != '#') {
                res = dfs(y1 + dy[d1], x1 + dx[d1], d1, y2, x2, d2);
            } else { // can turn
                for(int i = 0; i < 2; ++i) {
                    const int nd1 = (d1 + dd[i]) % 4, nd2 = (d2 + dd[i]) % 4;
                    if(v[y2 - dy[nd2]][x2 - dx[nd2]] != '#') continue; // front must be wall
                    res |= dfs(y1, x1, nd1, y2, x2, nd2);
                }
            }
            if(v[y2 + dy[d2]][x2 + dx[d2]] != '#') {
                res |= dfs(y1, x1, d1, y2 + dy[d2], x2 + dx[d2], d2);
            }
            return res;
        };

        bool ac = false;
        for(int d = 0; d < 4; ++d) {
            ac |= dfs(sy, sx, sd, sy, sx, d);
        }

        if(ac) {
            cout << "He can accomplish his mission." << endl;
        } else if(go_to_kitchen(sy, sx, sd)) {
            cout << "He cannot return to the kitchen." << endl;
        } else {
            cout << "He cannot bring tea to his master." << endl;
        }
    }
}
