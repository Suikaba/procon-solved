#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    vector<ll> v(n), d(n), p(n);
    for(int i = 0; i < n; ++i) {
        cin >> v[i] >> d[i] >> p[i];
    }

    vector<int> ans;
    for(int i = 0; i < n; ++i) {
        if(p[i] < 0) continue;
        ans.push_back(i + 1);
        ll minus = v[i];
        ll sum = 0;
        for(int j = i + 1; j < n; ++j) {
            if(p[j] < 0) continue;
            p[j] -= max(0LL, minus) + sum;
            if(p[j] < 0) {
                sum += d[j];
            }
            minus--;
        }
    }

    const int sz = ans.size();
    cout << sz << endl;
    for(int i = 0; i < sz; ++i) {
        cout << ans[i] << " \n"[i + 1 == sz];
    }
}
