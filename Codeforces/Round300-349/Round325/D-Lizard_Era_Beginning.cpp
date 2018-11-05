#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

constexpr int inf = 1e9;

int main() {
    int n; cin >> n;
    vector<int> l(n), m(n), w(n);
    for(int i = 0; i < n; ++i) {
        cin >> l[i] >> m[i] >> w[i];
    }

    const int n1 = n / 2;
    // const int n2 = n - n1;

    map<pii, pair<int, vector<string>>> ans1;
    vector<string> tmp;
    function<void(int, int, int, int)> dfs1 = [&] (int i, int tsub2, int tsub3, int sum) {
        if(i == n1) {
            const auto p = make_pair(tsub2, tsub3);
            if(ans1.count(p) == 0) {
                ans1[p] = make_pair(sum, tmp);
            } else {
                ans1[p] = max(ans1[p], make_pair(sum, tmp));
            }
            return;
        }
        tmp.push_back("LM"); dfs1(i + 1, tsub2 + l[i] - m[i], tsub3 + l[i], sum + l[i]); tmp.pop_back();
        tmp.push_back("MW"); dfs1(i + 1, tsub2 - m[i], tsub3 - w[i], sum); tmp.pop_back();
        tmp.push_back("LW"); dfs1(i + 1, tsub2 + l[i], tsub3 + l[i] - w[i], sum + l[i]); tmp.pop_back();
    };
    dfs1(0, 0, 0, 0);

    int ans_sum = -inf;
    vector<string> ans;
    function<void(int, int, int, int)> dfs2 = [&] (int i, int tsub2, int tsub3, int sum) {
        if(i == n) {
            const auto p = make_pair(-tsub2, -tsub3);
            if(ans1.count(p) && ans1[p].first + sum > ans_sum) {
                ans.clear();
                ans_sum = ans1[p].first + sum;
                for(auto& x : ans1[p].second) {
                    ans.push_back(x);
                }
                for(auto& x : tmp) {
                    ans.push_back(x);
                }
            }
            return;
        }
        tmp.push_back("LM"); dfs2(i + 1, tsub2 + l[i] - m[i], tsub3 + l[i], sum + l[i]); tmp.pop_back();
        tmp.push_back("MW"); dfs2(i + 1, tsub2 - m[i], tsub3 - w[i], sum); tmp.pop_back();
        tmp.push_back("LW"); dfs2(i + 1, tsub2 + l[i], tsub3 + l[i] - w[i], sum + l[i]); tmp.pop_back();
    };
    dfs2(n1, 0, 0, 0);

    if(ans.empty()) {
        cout << "Impossible" << endl;
    } else {
        for(auto& x : ans) {
            cout << x << endl;
        }
    }
}
