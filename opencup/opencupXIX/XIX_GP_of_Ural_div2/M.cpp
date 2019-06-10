#include <bits/stdc++.h>
using namespace std;

using ll = __int128;

int main() {
    string s; cin >> s;
    ll v = 0;
    for(auto c : s) {
        v *= 10;
        v += c - '0';
    }

    int ans = 0, cur = 0;
    while(v > 0) {
        if(v & 1) cur += 1;
        else {
            ans = max(ans, cur);
            cur = 0;
        }
        v /= 2;
    }
    ans = max(ans, cur);

    cout << ans << endl;
}
