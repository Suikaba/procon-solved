#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<string> v(n);
    for(int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    int ans = 0;
    for(int i = 1; i < n - 1; ++i) {
        for(int j = 1; j < n - 1; ++j) {
            if(v[i][j] == 'X' && v[i - 1][j - 1] == 'X' && v[i - 1][j + 1] == 'X' && v[i + 1][j - 1] == 'X' && v[i + 1][j + 1] == 'X') {
                ans += 1;
            }
        }
    }
    cout << ans << endl;
}
