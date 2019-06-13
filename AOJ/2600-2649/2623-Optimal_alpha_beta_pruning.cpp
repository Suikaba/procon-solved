#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
const int inf = 1e9;

template<typename T>
std::vector<T> table(int n, T v) { return std::vector<T>(n, v); }

template <class... Args>
auto table(int n, Args... args) {
    auto val = table(args...);
    return std::vector<decltype(val)>(n, std::move(val));
}

int main() {
    int n; cin >> n;
    vector<int> p(n), vs = {-inf, inf};
    for(auto& x : p) {
        cin >> x;
        vs.push_back(x);
        vs.push_back(-x);
    }
    sort(begin(vs), end(vs));
    vs.erase(unique(begin(vs), end(vs)), end(vs));
    auto get_idx = [&] (int val) -> int {
        return lower_bound(begin(vs), end(vs), val) - begin(vs);
    };
    vector<vector<int>> g(n);
    for(int i = 0; i < n; ++i) {
        int k; cin >> k;
        g[i].resize(k);
        for(auto& c : g[i]) {
            cin >> c;
            c--;
        }
    }

    auto max_dp = table(n, vs.size(), vs.size(), make_pair(-inf, 0));
    auto min_dp = table(n, vs.size(), vs.size(), make_pair(inf, 0));
    function<pii(int, int, int, bool)> dfs = [&] (int v, int alpha, int beta, bool is_min) {
        if(g[v].empty()) return make_pair(1, p[v]); // leaf

        auto& res = (is_min ? min_dp[v][alpha][beta] : max_dp[v][alpha][beta]);
        if(abs(res.first) != inf) return res;

        sort(begin(g[v]), end(g[v]));
        do {
            int talpha = alpha;
            pii cur = make_pair(0, -inf);
            for(auto const ch : g[v]) {
                auto val = dfs(ch, get_idx(-vs[beta]), get_idx(-vs[talpha]), is_min);
                val.second = -val.second;
                cur.first += val.first;
                if(val.second >= vs[beta]) {
                    cur.second = val.second;
                    break;
                }
                if(val.second > vs[talpha]) {
                    talpha = get_idx(val.second);
                }
            }
            if(cur.second == -inf) { // not occured val.second >= beta
                cur.second = vs[talpha];
            }
            if(is_min) res = min(res, cur);
            else       res = max(res, cur);
        } while(next_permutation(begin(g[v]), end(g[v])));

        return res;
    };

    cout << dfs(0, 0, vs.size() - 1, true).first << " " << dfs(0, 0, vs.size() - 1, false).first << endl;
}
