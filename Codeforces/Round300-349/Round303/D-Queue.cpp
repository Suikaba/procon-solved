#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<int> t(n);
    for(int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    sort(begin(t), end(t));
    ll w = 0;
    int ans = 0;
    for(auto x : t) {
        if(w <= x) {
            ans += 1;
            w += x;
        }
    }
    cout << ans << endl;
}
