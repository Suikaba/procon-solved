#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n; cin >> n;
    vector<int> c(n);
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
    }

    int ans = 0;
    vector<int> vis(n, -1); // -1: not vis, -2: on circuit, otherwise: s
    for(int s = 0; s < n; ++s) {
        if(vis[s] != -1) continue;
        int cur = s;
        int mini = inf;
        while(vis[cur] != -2) {
            if(vis[cur] > 0 && vis[cur] != s) {
                break;
            }
            if(vis[cur] == s) {
                vis[cur] = -2;
                mini = min(mini, c[cur]);
            } else {
                vis[cur] = s;
            }
            cur = a[cur];
        }
        if(mini != inf) { // already added
            ans += mini;
        }
    }

    cout << ans << endl;
}
