#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> pic(n);
    vector<vector<int>> val(n, vector<int>(m));
    for(int i = 0; i < n; ++i) {
        cin >> pic[i];
        for(int j = 0; j < m; ++j) {
            val[i][j] = pic[i][j] == 'B' ? -1 : 1;
        }
    }

    int ans = 0;
    for(int i = n - 1; i >= 0; --i) {
        for(int j = m - 1; j >= 0; --j) {
            if(val[i][j] != 0) {
                ans += 1;
                for(int k = 0; k <= i; ++k) {
                    for(int l = 0; l <= j; ++l) {
                        val[k][l] -= val[i][j];
                    }
                }
            }
        }
    }
    cout << ans << endl;
}
