#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    bool f = false;
    for(int i = 0; i < n; ++i) {
        f |= a[i][0] == 1 || a[i][m - 1] == 1;
    }
    for(int i = 0; i < m; ++i) {
        f |= a[0][i] == 1 || a[n - 1][i] == 1;
    }

    cout << (f ? 2 : 4) << endl;
}
