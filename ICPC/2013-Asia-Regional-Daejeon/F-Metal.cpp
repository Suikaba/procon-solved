#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

constexpr double inf = 2e9;

int main() {
    cout << fixed << setprecision(1);

    int T; cin >> T;
    while(T--) {
        int n, k; cin >> n >> k;
        vector<pii> ps(n);
        for(int i = 0; i < n; ++i) {
            cin >> ps[i].first >> ps[i].second;
        }

        auto check =
            [&] (double X) {
                int limit = k - 1;
                int mini = ps[0].second, maxi = ps[0].second;
                for(int i = 1; i < n; ++i) {
                    int nmini = min(mini, ps[i].second);
                    int nmaxi = max(maxi, ps[i].second);
                    if((nmaxi - nmini) / 2.0 > X) {
                        limit--;
                        if(limit < 0) return false;
                        mini = ps[i].second;
                        maxi = ps[i].second;
                        continue;
                    }
                    mini = nmini;
                    maxi = nmaxi;
                }
                return true;
            };
        double lb = 0, ub = inf;
        for(int lp = 0; lp < 100; ++lp) {
            const auto mid = (lb + ub) / 2;
            (check(mid) ? ub : lb) = mid;
        }

        cout << ub << endl;
    }
}
