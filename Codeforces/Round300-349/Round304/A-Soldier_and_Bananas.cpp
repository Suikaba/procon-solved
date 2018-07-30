
// http://codeforces.com/contest/546/problem/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    int k, w, n;
    cin >> k >> n >> w;
    int need = 0;
    for(int i = 1; i <= w; ++i) {
        need += i * k;
    }
    cout << max(0, need - n) << endl;
}
