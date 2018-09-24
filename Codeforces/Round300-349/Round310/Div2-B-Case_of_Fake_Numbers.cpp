
// http://codeforces.com/contest/556/problem/B

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    const int diff = a[0];
    bool ans = true;
    for(int i = 0; i < n; ++i) {
        a[i] = (i & 1 ? (a[i] + diff) % n : (a[i] - diff + n) % n);
        ans &= a[i] == i;
    }
    cout << (ans ? "Yes" : "No") << endl;
}
