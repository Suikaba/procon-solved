
// http://codeforces.com/contest/569/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t, s, q;
    cin >> t >> s >> q;
    int ans = 0;
    while(t > s) {
        s *= q;
        ans++;
    }
    cout << ans << endl;
}
