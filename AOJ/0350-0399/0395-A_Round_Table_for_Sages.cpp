#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n), w(n);
    for(auto& x : a) cin >> x;
    for(auto& x : w) cin >> x;

    vector<int> ord(n);
    iota(begin(ord), end(ord), 0);
    int ans = 10000000;
    do {
        int tans = 0;
        for(int i = 0; i < n; ++i) {
            if(a[ord[i]] == 0) {
                if(a[ord[(i + n - 1) % n]] == 1) {
                    tans += w[ord[i]];
                }
            } else {
                if(a[ord[(i + 1) % n]] == 0) {
                    tans += w[ord[i]];
                }
            }
        }
        ans = min(ans, tans);
    } while(next_permutation(begin(ord) + 1, end(ord)));

    cout << ans << endl;
}
