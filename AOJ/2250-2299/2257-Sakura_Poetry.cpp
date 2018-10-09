// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2257

// 本質がDPテーブルが実はスパースなことに気づけるかどうかなんだけど、
// うーん（それ以外はやるだけ）

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
constexpr int mod = 1e9 + 7;

template<typename T>
std::vector<T> table(int n, T v) { return std::vector<T>(n, v); }

template <class... Args>
auto table(int n, Args... args) {
    auto val = table(args...);
    return std::vector<decltype(val)>(n, std::move(val));
}

struct alphabets { // example: lower letters
    static int const size = 26;
    static int convert(char c) {
		assert('a' <= c && c <= 'z');
		return c - 'a';
    }
    static char convert_inv(int i) {
		assert(0 <= i && i < size);
		return 'a' + i;
    }
};

template <typename Alphabets>
class aho_corasick {
    static const int invalid_idx = -1;

    struct PMA {
        int fail;
        std::vector<int> next, accept;

        PMA() : fail(invalid_idx), next(Alphabets::size, invalid_idx) {}
    };

public:
    aho_corasick(std::vector<std::string> const& ts)
    : K(ts.size()) {
        const int root_idx = 0;
        nodes.push_back(std::make_unique<PMA>()); // root node
        nodes[root_idx]->fail = root_idx; // root idx
        for(int i = 0; i < K; ++i) {
            int now = root_idx;
            for(auto cc : ts[i]) {
                int c = Alphabets::convert(cc);
                if(nodes[now]->next[c] == invalid_idx) {
                    nodes[now]->next[c] = static_cast<int>(nodes.size());
                    nodes.push_back(std::make_unique<PMA>());
                }
                now = nodes[now]->next[c];
            }
            nodes[now]->accept.push_back(i);
        }

        std::queue<int> que;
        for(int c = 0; c < Alphabets::size; ++c) {
            if(nodes[root_idx]->next[c] != invalid_idx) {
                nodes[nodes[root_idx]->next[c]]->fail = root_idx;
                que.push(nodes[root_idx]->next[c]);
            }
        }
        while(!que.empty()) {
            int now = que.front();
            que.pop();
            for(int c = 0; c < Alphabets::size; ++c) {
                if(nodes[now]->next[c] != invalid_idx) {
                    que.push(nodes[now]->next[c]);
                    int nxt = transition(nodes[now]->fail, Alphabets::convert_inv(c));
                    nodes[nodes[now]->next[c]]->fail = nxt;
                    for(auto ac : nodes[nxt]->accept) {
                        nodes[nodes[now]->next[c]]->accept.push_back(ac);
                    }
                }
            }
        }
    }

    int transition(int node_idx, char cc) {
        assert(0 <= node_idx && node_idx < static_cast<int>(nodes.size()));
        int c = Alphabets::convert(cc);
        int now = node_idx;
        while(nodes[now]->next[c] == invalid_idx && now != 0) {
            now = nodes[now]->fail;
        }
        now = nodes[now]->next[c];
        if(now == invalid_idx) now = 0;
        return now;
    }

    int accept_size(int node_idx) const {
        assert(0 <= node_idx && node_idx < static_cast<int>(nodes.size()));
        return nodes[node_idx]->accept.size();
    }

    int node_size() const {
        return static_cast<int>(nodes.size());
    }

private:
    const int K;
    std::vector<std::unique_ptr<PMA>> nodes;
};

int main() {
    int n, m, k;
    while(cin >> n >> m >> k, n) {
        vector<string> ss = {""}; // empty (start node)
        vector<string> from(n), to(n), seasonwords(k);
        for(int i = 0; i < n; ++i) {
            cin >> from[i] >> to[i];
            ss.push_back(from[i]), ss.push_back(to[i]);
        }
        for(int i = 0; i < k; ++i) {
            cin >> seasonwords[i];
        }
        sort(begin(ss), end(ss));
        ss.erase(unique(begin(ss), end(ss)), end(ss));
        const int s_sz = ss.size();
        vector<vector<int>> g(s_sz);
        for(int i = 0; i < n; ++i) {
            const int s = lower_bound(begin(ss), end(ss), from[i]) - begin(ss);
            const int t = lower_bound(begin(ss), end(ss), to[i]) - begin(ss);
            g[s].push_back(t);
        }
        for(int i = 1; i < s_sz; ++i) {
            g[0].push_back(i);
        }

        aho_corasick<alphabets> aho(seasonwords);
        vector<vector<map<pii, int>>> dp(m + 1, vector<map<pii, int>>(2));
        dp[0][0][make_pair(0, 0)] = 1;
        for(int len = 0; len < m; ++len) {
            for(int s = 0; s < 2; ++s) {
                for(auto& p : dp[len][s]) {
                    const int nid = p.first.first, sid = p.first.second;
                    for(auto t : g[sid]) {
                        auto& to_str = ss[t];
                        if((int)to_str.size() + len > m) continue;
                        int now = nid, ac_sz = s;
                        for(auto c : to_str) {
                            now = aho.transition(now, c);
                            ac_sz += aho.accept_size(now);
                        }
                        if(ac_sz >= 2) continue;
                        (dp[to_str.size() + len][ac_sz][make_pair(now, t)] += p.second) %= mod;
                    }
                }
            }
        }

        int ans = 0;
        for(auto& p : dp[m][1]) {
            (ans += p.second) %= mod;
        }
        cout << ans << endl;
    }
}
