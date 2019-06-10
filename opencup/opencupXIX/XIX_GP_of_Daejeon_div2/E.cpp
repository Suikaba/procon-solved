#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class convex_hull_trick {
    using T = long long;

    bool check(int f1, int f2, T aa, T bb) {
        return (a[f2] - a[f1]) * (bb - b[f2]) >= (b[f2] - b[f1]) * (aa - a[f2]);
    }
    bool check(int f1, int f2, int f3) {
        return (a[f2] - a[f1]) * (b[f3] - b[f2]) >= (b[f2] - b[f1]) * (a[f3] - a[f2]);
    }

    T f(int idx, T x) {
        return a[idx] * x + b[idx];
    }

public:
    convex_hull_trick() = default;
    // a : sorted sequence, a[i] >= a[i + 1] >= a[i + 2] ...
    convex_hull_trick(std::vector<T> const& a_, std::vector<T> const& b_) {
        assert(a_.size() == b_.size());
        for(int i = 0; i < (int)a_.size(); ++i) {
            add_f(a_[i], b_[i]);
        }
    }

    void add_f(T aa, T bb) {
        while(a.size() >= 2 && check(a.size() - 2, a.size() - 1, aa, bb)) {
            a.pop_back();
            b.pop_back();
        }
        a.push_back(aa);
        b.push_back(bb);
    }
    ll min(T x) { // return index
        assert(a.size() > 0);
        while(a.size() >= 2 && f(0, x) >= f(1, x)) {
            a.pop_front();
            b.pop_front();
        }
        return a[0] * x + b[0];
    }

private:
    std::deque<T> a, b; // functions
};

struct rect {
    ll w, h;
    rect(ll w_, ll h_) : w(min(w_, h_)), h(max(w_, h_)) {}
    bool operator>(const rect& r) const {
        return h > r.h;
    }
};

int main() {
    int n; cin >> n;
    vector<rect> rs;
    vector<ll> ssum(1 << 20), wsum(1 << 20);
    for(int i = 0; i < n; ++i) {
        ll w, h; cin >> w >> h;
        if(w > h) swap(w, h);
        rs.emplace_back(w, h);
        ssum[w] += w * h;
        wsum[w] += h;
    }
    for(int i = 0; i < 1 << 20; ++i) {
        ssum[i + 1] += ssum[i];
        wsum[i + 1] += wsum[i];
    }
    sort(begin(rs), end(rs), greater<>{});

    ll ans = 0;
    convex_hull_trick cht;
    cht.add_f(rs[0].h, -rs[0].h * rs[0].w);
    for(int i = 1; i < n; ++i) {
        const ll h = rs[i].h;
        ll tans = h * wsum[h] - ssum[h];
        tans -= (h - rs[i].w) * h; // self
        tans -= max(0LL, cht.min(h));
        ans = max(ans, tans);
        cht.add_f(h, -rs[i].w * rs[i].h);
    }

    cout << ans << endl;
}
