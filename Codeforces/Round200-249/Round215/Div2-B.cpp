#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<pii> l(m);
    for(int i = 0; i < m; ++i) {
        cin >> l[i].first;
        l[i].first--;
        l[i].second = i;
    }
    sort(rbegin(l), rend(l));

    int it = n;
    set<int> s;
    vector<int> ans(m);
    for(int i = 0; i < m; ++i) {
        while(it > l[i].first) {
            s.insert(a[--it]);
        }
        ans[l[i].second] = s.size();
    }

    for(int i = 0; i < m; ++i) {
        cout << ans[i] << endl;
    }
}
