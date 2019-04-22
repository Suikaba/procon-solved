#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n; cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    ll mini = a.back() - 1;
    for(int i = n - 2; i >= 0; --i) {
        a[i] = min(a[i], mini);
        mini = max(a[i] - 1, 0LL);
    }
    
    cout << accumulate(begin(a), end(a), 0LL) << endl;
}