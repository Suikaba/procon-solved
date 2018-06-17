#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// http://codeforces.com/problemset/problem/516/A

// 反省点
// 未証明です（は？）

int main() {
    int n;
    ll a;
    cin >> n >> a;
    string ans;
    while(a > 1) {
        int x = a % 10;
        a /= 10;
        if(x == 9) {
            ans += "7332";
        } else if(x == 8) {
            ans += "7222";
        } else if(x == 6) {
            ans += "53";
        } else if(x == 4) {
            ans += "322";
        } else if(x != 0 && x != 1) {
            ans += '0' + x;
        }
    }
    sort(rbegin(ans), rend(ans));
    cout << ans << endl;
}
