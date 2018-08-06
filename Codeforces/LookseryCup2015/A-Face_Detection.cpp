#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> pic(n);
    for(int i = 0; i < n; ++i) {
        cin >> pic[i];
    }

    int ans = 0;
    for(int i = 0; i + 1 < n; ++i) {
        for(int j = 0; j + 1 < m; ++j) {
            string s;
            s += pic[i][j];
            s += pic[i + 1][j];
            s += pic[i][j + 1];
            s += pic[i + 1][j + 1];
            sort(begin(s), end(s));
            ans += s == "acef";
        }
    }
    cout << ans << endl;
}