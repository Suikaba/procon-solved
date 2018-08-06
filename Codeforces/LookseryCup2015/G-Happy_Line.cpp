#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n;
    cin >> n;
    vector<pii> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(begin(a), end(a), [](auto const& p1, auto const& p2) {
            return make_pair(p1.first + p1.second, p1.second) < make_pair(p2.first + p2.second, p2.second);
        });
    for(int i = 0; i < n; ++i) {
        a[i].first += a[i].second - i;
    }
    bool check = true;
    for(int i = 0; i + 1 < n; ++i) {
        check &= a[i].first <= a[i + 1].first;
    }
    if(!check) {
        cout << ":(" << endl;
    } else {
        for(int i = 0; i < n; ++i) {
            cout << a[i].first << " \n"[i + 1 == n];
        }
    }
}
