// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0301

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m, q; cin >> n >> m >> q;
    set<int> s;
    for(int i = 0; i < n; ++i) s.insert(i);
    auto now = begin(s);
    auto pass = [&] (auto it, bool rev) {
        if(rev) {
            if(it == begin(s)) return prev(end(s));
            else               return prev(it);
        } else {
            auto res = next(it);
            return (res == end(s) ? begin(s) : res);
        }
    };
    for(int i = 0; i < m; ++i) {
        int a; cin >> a;
        const bool pre = a & 1;
        while(a--) {
            now = pass(now, pre);
        }
        auto nxt = pass(now, false);
        s.erase(now);
        now = nxt;
    }
    for(int i = 0; i < q; ++i) {
        int x; cin >> x;
        cout << s.count(x) << endl;
    }
}
