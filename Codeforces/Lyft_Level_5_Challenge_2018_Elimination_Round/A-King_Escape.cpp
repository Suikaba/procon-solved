#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int ax, ay, bx, by, cx, cy;
    cin >> ax >> ay >> bx >> by >> cx >> cy;
    ax--, ay--, bx--, by--, cx--, cy--;

    auto in_range = [&] (int y, int x) {
        return 0 <= y && y < n && 0 <= x && x < n;
    };
    vector<vector<int>> d(n, vector<int>(n));
    for(int i = 0; i < n; ++i) {
        d[ay][i] = d[i][ax] = -1;
        const int s1 = ax + ay, s2 = ax - ay;
        const int y1 = i, x1 = s1 - y1;
        const int y2 = i, x2 = s2 + y2;
        if(in_range(y1, x1)) d[y1][x1] = -1;
        if(in_range(y2, x2)) d[y2][x2] = -1;
    }

    function<void(int, int)> dfs = [&] (int y, int x) {
        for(int dy = -1; dy <= 1; ++dy) {
            for(int dx = -1; dx <= 1; ++dx) {
                const int ny = y + dy, nx = x + dx;
                if(!in_range(ny, nx) || d[ny][nx] != 0) continue;
                d[ny][nx] = 1;
                dfs(ny, nx);
            }
        }
    };
    d[by][bx] = 1;
    dfs(by, bx);

    cout << (d[cy][cx] == 1 ? "YES" : "NO") << endl;
}
