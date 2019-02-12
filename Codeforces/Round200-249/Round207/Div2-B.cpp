#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<int> ans(n, -1);
    for(int i = 0; i < m; ++i) {
        set<int> col = {1, 2, 3};
        vector<int> v(3);
        for(int j = 0; j < 3; ++j) {
            cin >> v[j];
            v[j]--;
            col.erase(ans[v[j]]);
        }
        for(int j = 0; j < 3; ++j) {
            if(ans[v[j]] != -1) continue;
            ans[v[j]] = *col.begin();
            col.erase(col.begin());
        }
    }
    for(int i = 0; i < n; ++i) {
        if(ans[i] == -1) {
            ans[i] = 1;
        }
    }

    for(int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}