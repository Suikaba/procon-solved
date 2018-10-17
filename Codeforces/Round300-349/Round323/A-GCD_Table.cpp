// http://codeforces.com/contest/582/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    multiset<int, greater<>> s;
    for(int i = 0; i < n * n; ++i) {
        int x; cin >> x;
        s.insert(x);
    }
    vector<vector<int>> g(n, vector<int>(n));
    for(int i = 0; i < n; ++i) {
        g[i][i] = *s.begin();
        s.erase(begin(s));
        for(int j = 0; j < i; ++j) {
            g[i][j] = g[j][i] = __gcd(g[i][i], g[j][j]);
            s.erase(s.lower_bound(g[i][j]));
            s.erase(s.lower_bound(g[i][j]));
        }
    }

    for(int i = 0; i < n; ++i) {
        cout << g[i][i] << " \n"[i + 1 == n];
    }
}
