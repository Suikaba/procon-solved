#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while(T--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> v(n, vector<int>(m));
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                cin >> v[i][j];
            }
        }

        int ans = 0;
        for(int i =  n - 1; i >= 0; --i) {
            for(int j = 0; j < m; ++j) {
                if(v[i][j] == 0) continue;
                int cur = i;
                while(cur != n - 1 && v[cur + 1][j] == 0) {
                    ans += 1;
                    v[cur + 1][j] = 1;
                    v[cur][j] = 0;
                    cur++;
                }
            }
        }

        cout << ans << endl;
    }
}
