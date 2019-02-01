#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    map<int, int> lpos, rpos;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        if(lpos.count(a[i]) == 0) lpos[a[i]] = i;
        rpos[a[i]] = i;
    }

    vector<int> sum(n + 1);
    sum[0] += 1; // first pos is not up
    sum[1] -= 1;
    for(auto& p : lpos) {
        const int val = p.first;
        const int l = p.second, r = rpos[val];
        sum[l + 1] += 1;
        sum[r + 1] -= 1;
    }
    for(int i = 0; i < n; ++i) {
        sum[i + 1] += sum[i];
    }

    int ans = 1;
    for(int i = 0; i < n; ++i) {
        if(sum[i] == 0) {
            (ans += ans) %= mod;
        }
    }
    cout << ans << endl;
}
