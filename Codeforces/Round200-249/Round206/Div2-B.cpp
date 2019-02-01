#include <bits/stdc++.h>
using namespace std;

int main() {
    int c1, c2, c3, c4; cin >> c1 >> c2 >> c3 >> c4;
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for(int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    auto calc_cost = [c1, c2, c3] (vector<int> c) {
        const int n = c.size();
        int cost = 0;
        for(int i = 0; i < n; ++i) {
            cost += min(c[i] * c1, c2);
        }
        return min(cost, c3);
    };

    cout << min(c4, calc_cost(a) + calc_cost(b)) << endl;
}
