#include <bits/stdc++.h>
using namespace std;

// Memory: O(nlogn)
// Time Complexity: initialization -> O(nlogn), query -> O(1)
// Requirement: op is idempotent, that is op(s, s) = s (forall s)
template <typename IdempotentType>
class sparse_table {
    using T = typename IdempotentType::type;
public:
    sparse_table(std::vector<T> const& v)
        : sz(v.size()), dat(1, v)
    {
        for(int i = 2, j = 1, p = 0; i <= sz; i <<= 1, ++j, p = 0) {
            dat.emplace_back(sz);
            for(int k = 0; k + i <= sz; ++k) {
                dat[j][p++] = IdempotentType::op(dat[j - 1][k], dat[j - 1][k + (i >> 1)]);
            }
        }
    }

    // [l, r) (0-indexed)
    T query(int l, int r) {
        assert(0 <= l && l < r && r <= sz);
        const int i = 31 - __builtin_clz(r - l);
        return IdempotentType::op(dat[i][l], dat[i][r - (1 << i)]);
    }

private:
    const int sz;
    std::vector<std::vector<T>> dat;
};

// examples
struct RMQ {
    using type = int;
    static int op(int a, int b) {
        return std::min(a, b);
    }
};

struct RGCDQ {
    using type = int;
    static type op(int a, int b) {
        return __gcd(a, b);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sparse_table<RMQ> min_seg(a);
    sparse_table<RGCDQ> gcd_seg(a);
    auto check = [&] (int len) {
        for(int i = 0; i + len <= n; ++i) {
            if(min_seg.query(i, i + len) == gcd_seg.query(i, i + len)) return true;
        }
        return false;
    };
    int lb = 1, ub = n + 1;
    while(ub - lb > 1) {
        const int mid = (ub + lb) >> 1;
        (check(mid) ? lb : ub) = mid;
    }

    vector<int> ans;
    for(int i = 0; i + lb <= n; ++i) {
        if(min_seg.query(i, i + lb) == gcd_seg.query(i, i + lb)) {
            ans.push_back(i + 1);
        }
    }
    cout << ans.size() << ' ' << lb - 1 << endl;
    for(int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
    }
}
