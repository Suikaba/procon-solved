// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0297

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    while(n--) {
        int k, p; cin >> k >> p;
        if(k % p == 0) cout << p << endl;
        else           cout << (k % p) << endl;
    }
}
