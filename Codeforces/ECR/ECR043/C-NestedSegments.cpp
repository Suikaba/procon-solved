#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

struct segment {
    int l, r;
    int id;
    segment(int l, int r, int id) : l(l), r(r), id(id) {}
    bool operator<(segment const& s) const {
        if(l == s.l) {
            return r > s.r;
        }
        return l < s.l;
    }
};

int main() {
    int n;
    cin >> n;
    vector<segment> seg;
    for(int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        seg.emplace_back(l, r, i);
    }
    sort(begin(seg), end(seg));
    int ma = -1, ma_idx = -1;
    int ans1 = -1, ans2 = -1;
    for(int i = 0; i < n; ++i) {
        if(seg[i].r <= ma) {
            ans2 = ma_idx + 1, ans1 = seg[i].id + 1;
            break;
        }
        if(ma < seg[i].r) {
            ma = seg[i].r;
            ma_idx = seg[i].id;
        }
    }

    assert(ans1 != 0 && ans2 != 0);
    cout << ans1 << ' ' << ans2 << endl;
}
