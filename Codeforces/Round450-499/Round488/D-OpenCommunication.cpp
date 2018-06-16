#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    auto check = [](pii p1, pii p2) {
        set<int> s;
        for(int d = 1; d <= 9; ++d) {
            if((p1.first == d || p1.second == d) && (p2.first == d || p2.second == d)) {
                s.insert(d);
            }
        }
        if((int)s.size() != 1) return -1;
        return *s.begin();
    };
    int n, m;
    cin >> n >> m;
    vector<pii> p1(n), p2(m);
    for(int i = 0; i < n; ++i) {
        cin >> p1[i].first >> p1[i].second;
        if(p1[i].first > p1[i].second) {
            swap(p1[i].first, p1[i].second);
        }
    }
    for(int i = 0; i < m; ++i) {
        cin >> p2[i].first >> p2[i].second;
        if(p2[i].first > p2[i].second) {
            swap(p2[i].first, p2[i].second);
        }
    }

    set<int> cand;
    bool ans = true;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int t = check(p1[i], p2[j]);
            if(t != -1) {
                cand.insert(t);

                set<int> c1, c2;
                for(int k = 0; k < m; ++k) {
                    int tt = check(p1[i], p2[k]);
                    if(tt != -1) c1.insert(tt);
                }
                for(int k = 0; k < n; ++k) {
                    int tt = check(p1[k], p2[j]);
                    if(tt != -1) c2.insert(tt);
                }
                if(c1.size() != 1U || c2.size() != 1U) {
                    ans = false;
                }
            }
        }
    }
    if((int)cand.size() == 1) {
        cout << *cand.begin() << endl;
        return 0;
    }

    cout << (ans ? 0 : -1) << endl;
}
