// http://codeforces.com/contest/584/problem/E

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n), b(n), p(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i]; a[i]--;
    }
    for(int i = 0; i < n; ++i) {
        cin >> b[i]; b[i]--;
        p[b[i]] = i;
    }

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        ans += abs(p[a[i]] - i);
    }
    vector<pii> sw;
    for(int i = 0; i < n; ++i) {
        if(a[i] == b[i]) continue;
        int idx = find(begin(a), end(a), b[i]) - begin(a);
        while(idx != i) {
            for(int j = i; j < idx; ++j) {
                if(p[a[j]] >= idx) {
                    swap(idx, j);
                    swap(a[idx], a[j]);
                    sw.emplace_back(idx + 1, j + 1);
                    break;
                }
            }
        }
    }
    cout << ans / 2 << endl;
    cout << sw.size() << endl;
    for(auto& s : sw) {
        cout << s.first << " " << s.second << endl;
    }
}
