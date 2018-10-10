// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1626

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll b;
    while(cin >> b, b) {
        int ans_len = -1, low = -1;
        for(int len = sqrt(2 * b) + 1; len >= 1; --len) {
            if(2 * b % len != 0) continue;
            ll t = 2 * b / len - len + 1;
            if(t & 1) continue;
            if(t / 2 <= 0) continue;
            ans_len = len, low = t / 2;
            break;
        }
        cout << low << " " << ans_len << endl;
    }
}
