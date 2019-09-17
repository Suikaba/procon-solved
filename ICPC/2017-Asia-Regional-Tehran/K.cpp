#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

const ll b[2] = {17LL, 19LL}, mod[2] = {999999937LL, 1000000007LL};
ll p[10004][2];

void init() {
    p[0][0] = p[0][1] = 1;
    for(int i = 1; i <= 10002; ++i) {
        for(int j = 0; j < 2; ++j) {
            p[i][j] = p[i - 1][j] * b[j] % mod[j];
        }
    }
}

class rolling_hash {
    using ll = long long;
public:
    rolling_hash(string const& s)
        : n(s.size()),
          hs{{vector<ll>(n + 1), vector<ll>(n + 1)}}
    {
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < n; ++j) {
                hs[i][j + 1] = (hs[i][j] * b[i] + s[j]) % mod[i];
            }
        }
    }

    ll query(int l, int r, int i) const {
        return ((hs[i][r] - hs[i][l] * p[r - l][i]) % mod[i] + mod[i]) % mod[i];
    }
    pll query(int l, int r) const {
        return make_pair(query(l, r, 0), query(l, r, 1));
    }

private:
    const int n;
    array<vector<ll>, 2> hs;
};

void change(const int tot_len, char& c, pll& hs, int i) {
    if(c == '0') {
        c = '1';
        (hs.first += p[tot_len - i - 1][0]) %= mod[0];
        (hs.second += p[tot_len - i - 1][1]) %= mod[1];
    } else {
        c = '0';
        (hs.first += mod[0] - p[tot_len - i - 1][0]) %= mod[0];
        (hs.second += mod[1] - p[tot_len - i - 1][1]) %= mod[1];
    }
}

bool check(vector<pll> const& hs, int i, string& s, pll cur_hs, int len) {
    if(i == (int)s.size()) {
        const auto it = lower_bound(begin(hs), end(hs), cur_hs);
        if(it == end(hs) || *it != cur_hs) return true;
        return false;
    } else {
        bool res = false;
        if((int)s.size() - i <= len) {
            change(s.size(), s[i], cur_hs, i);
            res = check(hs, i + 1, s, cur_hs, len - 1);
            change(s.size(), s[i], cur_hs, i);
        } else {
            res |= check(hs, i + 1, s, cur_hs, len);
            if(!res && len >= 1) {
                change(s.size(), s[i], cur_hs, i);
                res = check(hs, i + 1, s, cur_hs, len - 1);
                change(s.size(), s[i], cur_hs, i);
            }
        }
        return res;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    init();

    int n, q;
    while(cin >> n >> q, n) {
        string s; cin >> s;
        rolling_hash hs(s);

        vector<int> l(q), r(q);
        set<int> lens;
        for(int i = 0; i < q; ++i) {
            cin >> l[i] >> r[i];
            l[i]--;
            lens.insert(r[i] - l[i]);
        }

        vector<vector<pll>> hss(n + 1);
        for(auto le : lens) {
            for(int i = 0; i + le <= n; ++i) {
                hss[le].push_back(hs.query(i, i + le));
            }
            sort(begin(hss[le]), end(hss[le]));
            hss[le].erase(unique(begin(hss[le]), end(hss[le])), end(hss[le]));
        }

        for(int qi = 0; qi < q; ++qi) {
            string t = s.substr(l[qi], r[qi] - l[qi]);
            const pll ths = hs.query(l[qi], r[qi]);

            int ans = -1;
            if(t.size() >= 110u) {
                if(check(hss[t.size()], 0, t, ths, 1)) {
                    ans = 1;
                } else {
                    ans = 2;
                }
            } else {
                for(int len = 1; len <= (int)t.size(); ++len) {
                    if(check(hss[t.size()], 0, t, ths, len)) {
                        ans = len;
                        break;
                    }
                }
            }

            if(ans == -1) {
                cout << "Impossible\n";
            } else {
                cout << ans << "\n";
            }
        }
    }
}