#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int h, w; cin >> h >> w;
    vector<string> s(h);
    int sy = -1, sx = -1;
    for(int i = 0; i < h; ++i) {
        cin >> s[i];
        for(int j = 0; j < w; ++j) {
            if(s[i][j] == '@') {
                sy = i, sx = j;
            }
        }
    }

    vector<pii> path;
    for(int i = 0; i < h; ++i) {
        path.emplace_back(i, 0);
    }
    function<void(int, int, int)> snake = [&] (int y, int x, int dx) {
        path.emplace_back(y, x);
        if(x + 2 * dx == 0 && y == 0) {
            path.emplace_back(0, 1);
            return;
        }
        if(x + dx < 2 || w <= x + dx) {
            path.emplace_back(y - 1, x);
            dx *= -1;
            y -= 2;
            snake(y, x, dx);
        } else {
            snake(y, x + dx, dx);
        }
    };
    snake(h - 1, 1, 1);
    rotate(begin(path), find(begin(path), end(path), make_pair(sy, sx)), end(path));
    while(s[path.back().first][path.back().second] != '*') {
        path.pop_back();
    }
    for(auto const& p : path) {
        const int y = p.first, x = p.second;
        if(s[y][x] == '.') {
            s[y][x] = '#';
        }
    }

    for(auto const& t : s) {
        cout << t << endl;
    }
}