
// http://codeforces.com/contest/558/problem/C

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    int n; scanf("%d", &n);
    unordered_map<int, int> cnt, a_cnt;
    for(int i = 0; i < n; ++i) {
        int a; scanf("%d", &a);
        a_cnt[a] += 1;
    }
    for(auto& aa : a_cnt) {
        int a = aa.first, num = aa.second;
        vector<pii> v = {make_pair(a, 0)};
        while(v.back().first != 1) {
            v.emplace_back(v.back().first / 2, v.back().second + num);
        }
        unordered_map<int, int> tmp_cnt;
        for(int j = 0; j < (int)v.size(); ++j) {
            auto& p = v[j];
            int t = p.first, c = p.second;
            if(cnt.size() != 0 && cnt.count(t) == 0) continue;
            if(tmp_cnt.count(t)) {
                tmp_cnt[t] = min(tmp_cnt[t], c);
            } else {
                tmp_cnt[t] = c;
            }
            c += num;
            if(j != 0 && v[j - 1].first == v[j].first * 2) continue;
            while((t *= 2) < (1 << 18)) {
                if(tmp_cnt.count(t)) {
                    tmp_cnt[t] = min(tmp_cnt[t], c);
                } else {
                    tmp_cnt[t] = c;
                }
                c += num;
            }
        }
        for(auto& p : tmp_cnt) {
            p.second += cnt[p.first];
        }
        cnt = move(tmp_cnt);
    }

    int ans = 1e9;
    for(auto& p : cnt) {
        ans = min(ans, p.second);
    }
    cout << ans << endl;
}
