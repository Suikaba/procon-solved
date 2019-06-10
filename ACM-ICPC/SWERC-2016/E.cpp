#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1000003;
//constexpr int mod = 1e9 + 7;

//template<typename T>
//std::vector<T> table(int n, T v) { return std::vector<T>(n, v); }
//
//template <class... Args>
//auto table(int n, Args... args) {
//    auto val = table(args...);
//    return std::vector<decltype(val)>(n, std::move(val));
//}

struct alphabets { // example: lower letters
    static int const size = 26;
    static int convert(char c) {
        return c - 'a';
    }
    static char convert_inv(int i) {
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
        nodes.push_back(std::unique_ptr<PMA>(new PMA())); // root node
        nodes[root_idx]->fail = root_idx; // root idx
        for(int i = 0; i < K; ++i) {
            int now = root_idx;
            for(auto cc : ts[i]) {
                int c = Alphabets::convert(cc);
                if(nodes[now]->next[c] == invalid_idx) {
                    nodes[now]->next[c] = static_cast<int>(nodes.size());
                    nodes.push_back(std::unique_ptr<PMA>(new PMA()));
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

    bool is_accept(int node_idx) const {
        assert(0 <= node_idx && node_idx < static_cast<int>(nodes.size()));
        return nodes[node_idx]->accept.size() != 0;
    }


    std::vector<int> accept_list(int node_idx) const {
        assert(0 <= node_idx && node_idx < static_cast<int>(nodes.size()));
        return nodes[node_idx]->accept;
    }

    std::vector<std::vector<int>> match(std::string const& s) {
        std::vector<std::vector<int>> res(K);
        int now = 0;
        for(int i = 0; i < static_cast<int>(s.size()); ++i) {
            now = transition(now, s[i]);
            for(auto k : nodes[now]->accept) {
                res[k].push_back(i);
            }
        }
        return res;
    }

    int node_size() const {
        return static_cast<int>(nodes.size());
    }

private:
    const int K;
    std::vector<std::unique_ptr<PMA>> nodes;
};

int main() {
    int a, b;
    while(cin >> a >> b) {
        int n; cin >> n;
        vector<string> ban(n);
        for(int i = 0; i < n; ++i) {
            cin >> ban[i];
        }

        aho_corasick<alphabets> aho(ban);
        const int m = aho.node_size();
        vector<vector<vector<vector<int>>>> dp(m, vector<vector<vector<int>>>(2, vector<vector<int>>(2, vector<int>(2))));
        dp[0][0][0][0] = 1;
        int ans = 0;
        for(int i = 0; i < b; ++i) {
            vector<vector<vector<vector<int>>>> nxt(m, vector<vector<vector<int>>>(2, vector<vector<int>>(2, vector<int>(2))));
            for(int cur = 0; cur < m; ++cur) {
                if(aho.is_accept(cur)) continue;
                for(int b1 = 0; b1 < 2; ++b1) { // small
                    for(int b2 = 0; b2 < 2; ++b2) { // capital
                        for(int b3 = 0; b3 < 2; ++b3) { // number
                            for(int k = 0; k < 26; ++k) {
                                {
                                    const int nxt1 = aho.transition(cur, 'a' + k);
                                    (nxt[nxt1][1][b2][b3] += dp[cur][b1][b2][b3]) %= mod;
                                }
                                {
                                    const int nxt2 = aho.transition(cur, 'a' + k);
                                    (nxt[nxt2][b1][1][b3] += dp[cur][b1][b2][b3]) %= mod;
                                }
                            }
                            for(int k = 0; k < 10; ++k) {
                                if(k == 0) { // o
                                    const int nx = aho.transition(cur, 'o');
                                    (nxt[nx][b1][b2][1] += dp[cur][b1][b2][b3]) %= mod;
                                } else if(k == 1) { // i
                                    const int nx = aho.transition(cur, 'i');
                                    (nxt[nx][b1][b2][1] += dp[cur][b1][b2][b3]) %= mod;
                                } else if(k == 3) { // e
                                    const int nx = aho.transition(cur, 'e');
                                    (nxt[nx][b1][b2][1] += dp[cur][b1][b2][b3]) %= mod;
                                } else if(k == 5) { // s
                                    const int nx = aho.transition(cur, 's');
                                    (nxt[nx][b1][b2][1] += dp[cur][b1][b2][b3]) %= mod;
                                } else if(k == 7) { // t
                                    const int nx = aho.transition(cur, 't');
                                    (nxt[nx][b1][b2][1] += dp[cur][b1][b2][b3]) %= mod;
                                } else {
                                    (nxt[0][b1][b2][1] += dp[cur][b1][b2][b3]) %= mod;
                                }
                            }
                        }
                    }
                }
            }
            dp = move(nxt);
            if(a - 1 <= i) {
                for(int cur = 0; cur < m; ++cur) {
                    if(aho.is_accept(cur)) continue;
                    (ans += dp[cur][1][1][1]) %= mod;
                }
            }
        }

        cout << ans << endl;
    }
}