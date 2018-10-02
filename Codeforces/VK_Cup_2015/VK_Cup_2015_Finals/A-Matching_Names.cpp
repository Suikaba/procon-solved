// http://codeforces.com/contest/566/problem/A

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

struct alphabet_t { // default: 'a' - 'z'
    static constexpr int size = 26;
    static constexpr int char_to_index(char c) {
        assert('a' <= c && c <= 'z');
        return c - 'a';
    }
    static constexpr char index_to_char(int idx) {
        assert(0 <= idx && idx < size);
        return 'a' + idx;
    }
};

template <typename Alpha>
class trie {
    static constexpr int alpha_sz = Alpha::size;
    using cnt_t = int;

public:
    trie() : cnt(0), cnt_subt(0), terminate(false) {}

    void insert(std::string const& s, int tag, int idx) {
        //if(find(s)) return; // when multiset, comment out this line
        auto cur_node = this;
        cur_node->cnt_subt += 1;
        for(int p = 0; p < static_cast<int>(s.size()); ++p) {
            const auto c = Alpha::char_to_index(s[p]);
            if(!cur_node->next[c]) cur_node->next[c] = std::make_unique<trie<Alpha>>();
            cur_node = cur_node->next[c].get();
            cur_node->cnt_subt += 1;
        }
        cur_node->idxs[tag].push_back(idx);
        cur_node->terminate = true;
        cur_node->cnt += 1;
    }

    bool find(std::string const& s) const { // Not verified
        auto cur_node = this;
        for(int p = 0; p < static_cast<int>(s.size()); ++p) {
            const auto c = Alpha::char_to_index(s[p]);
            if(!cur_node->next[c]) return false;
            cur_node = next[c].get();
        }
        return cur_node->terminate;
    }

    std::string kth_element(cnt_t k) const { // 1-indexed, Not verified
        assert(cnt_subt >= k);
        k -= cnt;
        while(k > 0) {
            for(int i = 0; i < alpha_sz; ++i) {
                if(next[i] && next[i]->cnt_subt >= k) {
                    return Alpha::index_to_char(i) + next[i]->kth_element(k);
                }
                k -= next[i] ? next[i]->cnt_subt : 0;
            }
        }
        return "";
    }

    pair<int, array<vector<int>, 2>> solve(std::vector<pii>& ans) {
        auto res = make_pair(0, idxs);
        for(int i = 0; i < alpha_sz; ++i) {
            if(!next[i]) continue;
            auto ch = next[i]->solve(ans);
            res.second[0].insert(end(res.second[0]), begin(ch.second[0]), end(ch.second[0]));
            res.second[1].insert(end(res.second[1]), begin(ch.second[1]), end(ch.second[1]));
            res.first += ch.first;
        }
        while(!res.second[0].empty() && !res.second[1].empty()) {
            ans.emplace_back(res.second[0].back(), res.second[1].back());
            res.second[0].pop_back();
            res.second[1].pop_back();
        }
        assert(res.second[0].empty() || res.second[1].empty());
        res.first += res.second[0].size() + res.second[1].size();
        return res;
    }

private:
    std::array<std::unique_ptr<trie<Alpha>>, alpha_sz> next;
    cnt_t cnt, cnt_subt;
    bool terminate;
    array<vector<int>, 2> idxs;
};


int main() {
    int n; cin >> n;
    trie<alphabet_t> t;
    int total_len = 0;
    for(int i = 0; i < 2 * n; ++i) {
        string s; cin >> s;
        t.insert(s, i >= n, (i >= n ? i - n + 1 : i + 1));
        total_len += s.size();
    }
    vector<pii> ans;
    cout << (total_len - t.solve(ans).first) / 2 << endl;
    for(auto& p : ans) {
        cout << p.first << " " << p.second << endl;
    }
}
