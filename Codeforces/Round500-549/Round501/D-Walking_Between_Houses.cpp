
// http://codeforces.com/contest/1015/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ll n, k, s;
    cin >> n >> k >> s;
    int remain = k;
    ll d = s;
    vector<ll> ans;
    while(remain > 0 && remain < d) {
        ans.push_back(min(d - remain + 1, n - 1));
        d -= ans.back();
        remain--;
    }
    while(remain-- > 0) {
        ans.push_back(1);
        d -= 1;
    }

    if(d == 0) {
        cout << "YES" << endl;
        assert((int)ans.size() == k);
        int now = 1;
        for(int i = 0; i < k; ++i) {
            if(i & 1) now -= ans[i];
            else      now += ans[i];
            cout << now << " \n"[i + 1 == k];
        }
    } else {
        cout << "NO" << endl;
    }
}
