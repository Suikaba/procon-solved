
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1345

#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;

int main() {
    int n, m; cin >> n >> m;
    vector<int> b(n), p(m);
    for(int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    for(int i = 0; i < m; ++i) {
        cin >> p[i];
    }

    auto solve = [&] (int st) {
        auto a = b;
        int res = 0;
        for(int i = 0, pos = 0; i < m; ++i) {
            for(int j = 0; j < p[i]; ++j, ++pos) {
                const int k = find(begin(a) + pos, end(a), st) - begin(a);
                if(k == n) return inf; // no solution
                res += k - pos;
                for(int l = k; l - 1 >= pos; --l) {
                    swap(a[l - 1], a[l]);
                }
            }
            st = !st;
        }
        return res;
    };

    cout << min(solve(0), solve(1)) << endl;
}
