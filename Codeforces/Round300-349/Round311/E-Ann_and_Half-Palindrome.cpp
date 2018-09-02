
// http://codeforces.com/contest/557/problem/E

#include <bits/stdc++.h>

struct alphabet_t { // default: 'a' - 'z'
    static constexpr int size = 2;
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

    bool find(std::string const& s) const {
        auto cur_node = this;
        for(int p = 0; p < static_cast<int>(s.size()); ++p) {
            const auto c = Alpha::char_to_index(s[p]);
            if(!next[c]) return false;
            cur_node = next[c].get();
        }
        return cur_node->terminate;
    }

    std::string kth_element(cnt_t k) const { // 1-indexed
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

    // ===
    trie<Alpha>* insert_special(std::string const& s) {
        auto cur_node = this;
        for(int p = 0; p < static_cast<int>(s.size()); ++p) {
            const auto c = Alpha::char_to_index(s[p]);
            if(!cur_node->next[c]) cur_node->next[c] = std::make_unique<trie<Alpha>>();
            cur_node = cur_node->next[c].get();
        }
        cur_node->terminate = true;
        cur_node->cnt += 1;
        return cur_node;
    }
    cnt_t calc_count_subtree() {
        cnt_subt = cnt;
        for(auto& p : next) {
            if(p) cnt_subt += p->calc_count_subtree();
        }
        return cnt_subt;
    }

private:
    std::array<std::unique_ptr<trie<Alpha>>, alpha_sz> next;
    cnt_t cnt, cnt_subt;
    bool terminate;
};


using namespace std;

using ll = long long;

int main() {
    string s;
    int k; cin >> s >> k;
    const int n = s.size();

    vector<vector<bool>> dp(n, vector<bool>(n)); // dp[i][j] := s[i..j] is half-palindrome ?
    constexpr int dl[4] = {0, -1, -1, 0};
    constexpr int dr[4] = {0, 1, 2, 1};
    for(int mid = 0; mid < n; ++mid) {
        for(int t = 0; t < 4; ++t) {
            int l = mid + dl[t], r = mid + dr[t];
            while(l >= 0 && r < n && s[l] == s[r]) {
                dp[l][r] = true;
                l -= 2, r += 2;
            }
        }
    }

    trie<alphabet_t> t;
    for(int l = 0; l < n; ++l) {
        string tmp;
        auto cur = &t;
        for(int r = l; r < n; ++r) {
            tmp += s[r];
            if(dp[l][r]) {
                cur = cur->insert_special(tmp);
                tmp.clear();
            }
        }
    }
    t.calc_count_subtree();

    cout << t.kth_element(k) << endl;
}