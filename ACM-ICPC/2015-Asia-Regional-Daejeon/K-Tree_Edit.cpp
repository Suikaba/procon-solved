#include <bits/stdc++.h>
using namespace std;

struct node;
using node_ptr = shared_ptr<node>;

constexpr int inf = 1e9;

struct node {
    node(char lbl) : sz(1), label(lbl) {}
    int sz;
    char label;
    std::vector<node_ptr> ch;

    void debug_print() {
        cout << "cur: " << label << endl;
        for(int i = 0; i < (int)ch.size(); ++i) {
            cout << "  -- ch: " << ch[i]->label << endl;
        }
        for(int i = 0; i < (int)ch.size(); ++i) {
            ch[i]->debug_print();
        }
    }
};

// [l..r]
node_ptr parse_impl(string const& s, int l, int r, vector<int> const& to) {
    assert(s[l] == '(' && s[r] == ')');
    auto res = make_shared<node>(s[l + 1]);
    int lp = l + 2;
    while(lp < r) {
        const int rp = to[lp];
        assert(rp != -1);
        res->ch.push_back(parse_impl(s, lp, rp, to));
        res->sz += res->ch.back()->sz;
        lp = rp + 1;
    }
    return res;
}

node_ptr parse(string const& s) {
    const int n = s.size();
    stack<int> lparen;
    vector<int> to(n, -1);
    for(int i = 0; i < n; ++i) {
        if(s[i] == '(') lparen.push(i);
        else if(s[i] == ')') {
            assert(!lparen.empty());
            to[lparen.top()] = i;
            lparen.pop();
        }
    }

    return parse_impl(s, 0, n - 1, to);
}

int main() {
    int T; cin >> T;
    while(T--) {
        string s, t; cin >> s >> t;
        auto g = parse(s), tg = parse(t);

        function<int(node_ptr, node_ptr)> solve = [&] (node_ptr n1, node_ptr n2) {
            const int sz1 = n1->ch.size(), sz2 = n2->ch.size();
            vector<int> dp(sz2 + 1, inf);
            dp[0] = (n1->label != n2->label);
            for(int i = 0; i < sz1; ++i) {
                // insert
                for(int j = 0; j < sz2; ++j) {
                    dp[j + 1] = min(dp[j + 1], dp[j] + n2->ch[j]->sz);
                }
                vector<int> nxt(sz2 + 1, inf);
                // delete
                for(int j = 0; j <= sz2; ++j) {
                    nxt[j] = min(nxt[j], dp[j] + n1->ch[i]->sz);
                }
                // use
                for(int j = 0; j < sz2; ++j) {
                    nxt[j + 1] = min(nxt[j + 1], dp[j] + solve(n1->ch[i], n2->ch[j]));
                }
                dp = move(nxt);
            }
            for(int j = 0; j < sz2; ++j) {
                dp[j + 1] = min(dp[j + 1], dp[j] + n2->ch[j]->sz);
            }
            return dp.back();
        };

        cout << solve(g, tg) << endl;
    }
}
