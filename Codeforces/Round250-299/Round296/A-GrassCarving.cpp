#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using ll = long long;

// http://codeforces.com/problemset/problem/528/A

// 反省点
// 最初閉区間で書いてたけど半開区間で良かった（なぜ閉区間にした？
// 20分ぐらいかかってて最悪，5分で書いてどうぞ

int main() {
    ll w, h;
    int n;
    cin >> w >> h >> n;
    set<pair<ll, ll>> vert, hori;
    multiset<ll> vlen, hlen;
    hori.emplace(0, h);
    vert.emplace(0, w);
    hlen.insert(h);
    vlen.insert(w);
    while(n--) {
        char dir;
        int p;
        cin >> dir >> p;
        auto& s = (dir == 'H' ? hori : vert);
        auto& len = (dir == 'H' ? hlen : vlen);
        auto it = *prev(s.lower_bound(make_pair(p, -1)));
        len.erase(len.lower_bound(it.second - it.first));
        s.emplace(it.first, p);
        s.emplace(p, it.second);
        len.insert(p - it.first);
        len.insert(it.second - p);
        s.erase(s.lower_bound(it));

        auto y = *prev(vlen.end());
        auto x = *prev(hlen.end());
        cout << y * x << endl;
    }
}
