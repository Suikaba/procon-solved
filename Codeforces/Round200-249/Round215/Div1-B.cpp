#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, p; cin >> n >> m >> p;
    vector<int> a(n), b(m);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    map<int, int> bcnt;
    for(int i = 0; i < m; ++i) {
        cin >> b[i];
        bcnt[b[i]] += 1;
    }

    vector<vector<int>> c(p);
    for(int i = 0; i < n; ++i) {
        c[i % p].push_back(a[i]);
    }

    vector<int> ans;
    for(int i = 0; i < p; ++i) {
        map<int, int> cnt;
        int ok_cnt = 0;
        auto add = [&] (int x) {
            ok_cnt -= bcnt.count(x) && cnt[x] == bcnt[x];
            cnt[x] += 1;
            ok_cnt += bcnt.count(x) && cnt[x] == bcnt[x];
        };
        auto erase = [&] (int x) {
            ok_cnt -= bcnt.count(x) && cnt[x] == bcnt[x];
            cnt[x] -= 1;
            ok_cnt += bcnt.count(x) && cnt[x] == bcnt[x];
        };
        for(int j = 0; j < m && j < (int)c[i].size(); ++j) {
            add(c[i][j]);
        }
        if(ok_cnt == (int)bcnt.size()) {
            ans.push_back(i + 1);
        }
        for(int j = m; j < (int)c[i].size(); ++j) {
            erase(c[i][j - m]);
            add(c[i][j]);
            if(ok_cnt == (int)bcnt.size()) {
                ans.push_back(i + 1 + p * (j - m + 1));
            }
        }
    }

    sort(begin(ans), end(ans));
    const int sz = ans.size();
    cout << sz << endl;
    for(int i = 0; i < sz; ++i) {
        cout << ans[i] << " \n"[i + 1 == sz];
    }
}
