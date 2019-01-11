#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n; cin >> n;
    vector<int> x(n);
    for(int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    vector<pii> segs;
    for(int i = 0; i + 1 < n; ++i) {
        int x1 = x[i], x2 = x[i + 1];
        if(x1 > x2) swap(x1, x2);
        segs.emplace_back(x1, x2);
    }

    const int m = segs.size();
    bool ng = false;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < m; ++j) {
            ng |= segs[i].first < segs[j].first && segs[j].first < segs[i].second && segs[i].second < segs[j].second;
        }
    }

    cout << (ng ? "yes" : "no") << endl;
}
