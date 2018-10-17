// http://codeforces.com/contest/573/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    int g = 0;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        g = __gcd(a[i], g);
    }
    bool ans = true;
    for(int i = 0; i < n; ++i) {
        a[i] /= g;
        while(a[i] % 2 == 0) a[i] /= 2;
        while(a[i] % 3 == 0) a[i] /= 3;
        if(a[i] != 1) ans = false;
    }

    cout << (ans ? "Yes" : "No") << endl;
}
