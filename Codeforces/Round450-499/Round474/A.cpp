#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<string> v(n);
    for(int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    bool ans = true;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(v[i][j] == '.') continue;
            for(int k = 0; k < n; ++k) {
                if(v[k][j] == '#') {
                    ans &= v[k] == v[i];
                }
            }
        }
    }

    cout << (ans ? "Yes" : "No") << endl;
}