// http://codeforces.com/contest/584/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, t; cin >> n >> t;
    if(t == 10) {
        if(n == 1) cout << -1 << endl;
        else       cout << 1 << string(n - 1, '0') << endl;
    } else {
        cout << string(n, '0' + t) << endl;
    }
}
