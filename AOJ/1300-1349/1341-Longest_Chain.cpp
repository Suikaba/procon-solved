#include <bits/stdc++.h>
using namespace std;

int a, b;
constexpr int C = ~(1 << 31);
constexpr int M = (1 << 16) - 1;

int r() {
    a = 36969 * (a & M) + (a >> 16);
    b = 18000 * (b & M) + (b >> 16);
    return (C & ((a << 16) + b)) % 1000000;
}

struct point {
    int y, z;

    point(int y_, int z_) : y(y_), z(z_) {}
    bool operator<(point const& p) const {
        return y < p.y;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    int m, n;
    while(cin >> m >> n >> a >> b, n + m) {
        vector<tuple<int, int, int>> ps(n + m);
        for(int i = 0; i < m; ++i) {
            int x, y, z; cin >> x >> y >> z;
            ps[i] = make_tuple(x, -y, -z);
        }
        for(int i = m; i < n + m; ++i) {
            const int x = r(), y = r(), z = r();
            ps[i] = make_tuple(x, -y, -z);
        }
        sort(begin(ps), end(ps));
        vector<point> ps2;
        for(int i = 0; i < n + m; ++i) {
            ps2.emplace_back(-get<1>(ps[i]), -get<2>(ps[i]));
        }

        int ans = 0;
        vector<set<point>> dp(n + m + 1);
        dp[0].emplace(0, 0);
        for(auto const& p : ps2) {
            auto check = [&] (int i) {
                auto it = dp[i].lower_bound(p);
                if(it == dp[i].begin()) return false;
                it = prev(it);
                return p.y > it->y && p.z > it->z;
            };
            int lb = 0, ub = n + m;
            while(ub - lb > 1) {
                const int mid = (ub + lb) >> 1;
                (check(mid) ? lb : ub) = mid;
            }
            auto it = dp[ub].lower_bound(p);
            while(it != dp[ub].end() && it->z >= p.z) {
                it = dp[ub].erase(it);
            }
            if(it == dp[ub].begin() || prev(it)->z > p.z) {
                dp[ub].insert(p);
            }
            ans = max(ans, ub);
        }

        cout << ans << endl;
    }
}
