// http://codeforces.com/contest/576/problem/C

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    constexpr int B = 1000;
    int n; cin >> n;
    vector<tuple<int, int, int>> ps(n);
    for(int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        ps[i] = make_tuple(x, y, i + 1);
    }
    sort(begin(ps), end(ps),
         [&] (auto const& p1, auto const& p2) {
             if(get<0>(p1) / B != get<0>(p2) / B) return get<0>(p1) < get<0>(p2);
             if((get<0>(p1) / B) & 1) return get<1>(p1) > get<1>(p2);
             else                     return get<1>(p1) < get<1>(p2);
         });
    for(int i = 0; i < n; ++i) {
        cout << get<2>(ps[i]) << " \n"[i + 1 == n];
    }
}
