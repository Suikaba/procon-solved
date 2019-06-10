#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

constexpr int mod = 1e9 + 7;

class union_find {
public:
    union_find(int n) : par(n, -1) {}

    int root(int x) {
        return par[x] < 0 ? x : par[x] = root(par[x]);
    }

    void unite(int x, int y) {
        x = root(x), y = root(y);
        if(x == y) return;
        if(par[x] < par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
    }

private:
    vector<int> par;
};

int main() {
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vector<char> var(m);
    vector<int> u(m);
    for(int i = 0; i < m; ++i) {
        cin >> var[i] >> u[i];
    }

    ll ans = 0;
    for(int S1 = 0; S1 < (1 << m); ++S1) { // determine 1 digit or 2 digits
        {
            bool check = true;
            for(int i = 0; i < m; ++i) {
                check &= !(S1 & (1 << i)) || (u[i] >= 10);
            }
            if(!check) continue;
        }
        vector<pii> vs;
        for(int i = 0; i < n; ++i) {
            if(isdigit(s[i])) {
                vs.emplace_back(-1, s[i] - '0');
            } else {
                const int id = find(begin(var), end(var), s[i]) - begin(var);
                if(S1 & (1 << id)) {
                    vs.emplace_back(id, 2);
                }
                vs.emplace_back(id, 1);
            }
        }

        // integrate
        auto ss = vs;
        sort(begin(ss), end(ss));
        ss.erase(unique(begin(ss), end(ss)), end(ss));
        const int vsz = vs.size();
        const int sz = ss.size();
        union_find uf(sz);
        for(int i = 0; i < vsz; ++i) {
            const int id1 = lower_bound(begin(ss), end(ss), vs[i]) - begin(ss);
            const int id2 = lower_bound(begin(ss), end(ss), vs[vsz - i - 1]) - begin(ss);
            uf.unite(id1, id2);
        }

        // determine 2nd digit
        for(int S2 = 0; S2 < (1 << m); ++S2) {
            {
                bool check = (S1 & S2) == S2;
                for(int i = 0; i < m; ++i) {
                    check &= !(S2 & (1 << i)) || u[i] >= 10;
                }
                if(!check) continue;
            }
            vector<ll> lb(sz, 0), ub(sz, mod);
            for(int i = 0; i < sz; ++i) {
                const int id = uf.root(i);
                const int midx = ss[i].first;
                ub[id] = min(ub[id], 9LL);
                if(midx == -1) {
                    lb[id] = max(lb[id], (ll)ss[i].second);
                    ub[id] = min(ub[id], (ll)ss[i].second);
                } else if(ss[i].second == 2) {
                    lb[id] = max(lb[id], 1LL);
                    if(S2 & (1 << midx)) {
                        lb[id] = max(lb[id], (ll)(u[midx] / 10));
                        ub[id] = min(ub[id], (ll)(u[midx] / 10));
                    } else {
                        ub[id] = min(ub[id], (ll)(u[midx] / 10 - 1));
                    }
                } else {
                    if(S2 & (1 << midx) || u[midx] < 10) {
                        ub[id] = min(ub[id], (ll)(u[midx] % 10));
                    }
                }
            }

            ll tans = 1;
            for(int i = 0; i < sz; ++i) {
                if(ub[i] == mod) continue;
                (tans *= max(0LL, ub[i] - lb[i] + 1)) %= mod;
            }
            (ans += tans) %= mod;
        }
    }

    cout << ans << endl;
}
