#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, t, p;
    while(cin >> n >> m >> t >> p, n) {
        vector<vector<int>> cur(n, vector<int>(m, 1));
        for(int i = 0; i < t; ++i) {
            int d, c; cin >> d >> c;
            const int nw = (d == 2 ? cur.size() : max(c, (int)cur.size() - c));
            const int nh = (d == 1 ? cur[0].size() : max(c, (int)cur[0].size() - c));
            vector<vector<int>> nxt(nw, vector<int>(nh));
            for(int x = 0; x < (int)cur.size(); ++x) {
                for(int y = 0; y < (int)cur[0].size(); ++y) {
                    const int nx = (d == 2 ? x : x < c ? c - x - 1 : x - c);
                    const int ny = (d == 1 ? y : y < c ? c - y - 1 : y - c);
                    nxt[nx][ny] += cur[x][y];
                }
            }
            cur = move(nxt);
        }

        for(int i = 0; i < p; ++i) {
            int x, y; cin >> x >> y;
            cout << cur[x][y] << endl;
        }
    }
}
