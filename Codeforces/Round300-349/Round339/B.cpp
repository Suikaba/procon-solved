#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

int main() {
    ll n, A, cf, cm, m; cin >> n >> A >> cf >> cm >> m;
    vector<pll> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(begin(a), end(a), greater<>{});

    ll ans_v = 0, rest = m, mi = 0, ans_mi = 0;
    ll rest_cnt = 0; // 減らす余地のある要素数
    int itr = n;
    { // initial
        auto check = [&] (ll val) {
            ll need = 0;
            for(int i = 0; i < n; ++i) {
                need += max(0LL, val - a[i].first);
            }
            return need <= m;
        };
        int lb = 0, ub = A + 1;
        while(ub - lb > 1) {
            const int mid = (ub + lb) >> 1;
            (check(mid) ? lb : ub) = mid;
        }
        mi = lb;
        ans_v = cm * mi;
        for(int i = 0; i < n; ++i) {
            if(mi > a[i].first) {
                rest -= mi - a[i].first;
                rest_cnt += 1;
                itr = min(itr, i);
            }
        }
        ans_mi = mi;
    }

    int ans_idx = 0;
    for(int i = 0; i < n; ++i) {
        //cout << "i => " << i << endl;
        if(itr == i) {
            rest += mi - a[i].first;
            rest_cnt -= 1;
            itr = i + 1;
        }
        ll need = A - a[i].first;
        { // use rest
            const ll use = min(rest, need);
            need -= use;
            rest -= use;
        }
        const ll tneed = need;
        if(need > 0) {
            ll total_sub = 0;
            while(itr < n && rest_cnt > 0 && (need + rest_cnt - 1) / rest_cnt >= mi - a[itr].first) {
                need -= (mi - a[itr].first) * rest_cnt;
                total_sub += (mi - a[itr].first) * rest_cnt;
                const ll rm_val = a[itr].first;
                while(itr < n && a[itr].first == rm_val) {
                    itr += 1;
                    rest_cnt -= 1;
                }
                mi = rm_val;
            }
            if(rest_cnt == 0) break;
            const ll dec = (need + rest_cnt - 1) / rest_cnt;
            total_sub += dec * rest_cnt;
            mi -= dec;
            rest = total_sub - tneed;
        }
        const ll t = (i + 1) * cf + cm * mi;
        if(ans_v < t) {
            ans_idx = i + 1;
            ans_mi = mi;
            ans_v = t;
        }
    }

    vector<int> ans(n);
    for(int i = 0; i < ans_idx; ++i) {
        ans[a[i].second] = A;
    }
    for(int i = ans_idx; i < n; ++i) {
        ans[a[i].second] = max((ll)ans_mi, a[i].first);
    }

    cout << ans_v << endl;
    for(int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i + 1 == n];
    }
}