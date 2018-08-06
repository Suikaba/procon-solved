
// http://codeforces.com/contest/551/problem/E

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    vector<ll> a(n);
    for(int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
    }
    constexpr int B = 512;
    vector<ll> lazy_add((n + B - 1) / B);
    const int b_sz = lazy_add.size();
    vector<vector<pair<ll, int>>> pos(b_sz);
    for(int i = 0; i < n; ++i) {
        pos[i / B].emplace_back(a[i], i);
    }
    for(auto& v : pos) {
        sort(begin(v), end(v));
    }
    auto get_range = [&] (vector<pair<ll, int>> const& vs, ll val) {
        auto lb = lower_bound(begin(vs), end(vs), make_pair(val, -1));
        if(lb == end(vs) || lb->first != val) return make_pair(n, 0);
        auto ub = lower_bound(begin(vs), end(vs), make_pair(val + 1, -1));
        return make_pair(lb->second, prev(ub)->second);
    };
    while(q--) {
        int com; scanf("%d", &com);
        if(com == 1) {
            int l, r, x;
            scanf("%d %d %d", &l, &r, &x);
            l--;
            for(int b = 0; b < b_sz; ++b) {
                const int l2 = b * B, r2 = min(n, (b + 1) * B);
                if(r <= l2 || r2 <= l) continue;
                if(l <= l2 && r2 <= r) {
                    lazy_add[b] += x;
                } else {
                    pos[b].clear();
                    for(int i = l2; i < r2; ++i) {
                        a[i] += lazy_add[b];
                        if(l <= i && i < r) {
                            a[i] += x;
                        }
                        pos[b].emplace_back(a[i], i);
                    }
                    lazy_add[b] = 0;
                    sort(begin(pos[b]), end(pos[b]));
                }
            }
        } else {
            int y; scanf("%d", &y);
            int l = n, r = 0;
            for(int b = 0; b < b_sz; ++b) {
                auto p = get_range(pos[b], y - lazy_add[b]);
                l = min(l, p.first), r = max(r, p.second);
            }
            printf("%d\n", max(-1, r - l));
        }
    }
}
