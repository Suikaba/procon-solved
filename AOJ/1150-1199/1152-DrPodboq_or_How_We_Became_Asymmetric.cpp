#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1152

// 反省点
// 問題文に書いてある条件の実装し忘れが多発．
// こういうたくさん条件が与えられる問題では，提出する前に全部実装したか上からチェックしていくのがいいね．

constexpr double eps = 1e-8;

struct exp_tree;
using tree_ptr = shared_ptr<exp_tree>;

struct exp_tree {
    tree_ptr lch, rch;
    double asym;
    bool leaf;
    exp_tree() : lch(nullptr), rch(nullptr), asym(0), leaf(true) {}
    string to_string(bool is_sort) const {
        assert(leaf || (lch && rch));
        if(leaf) return "x";
        auto s1 = lch->to_string(is_sort), s2 = rch->to_string(is_sort);
        if(is_sort && s1 > s2) swap(s1, s2);
        return "(" + s1 + " " + s2 + ")";
    }
    double value() const {
        return asym;
    }
    bool operator<(exp_tree const& other) const { // lch.asym < rch.asym ?
        if(other.leaf) return false;
        if(leaf) return true;
        if(abs(value() - other.value()) < eps) {
            auto lmin = min(*lch, *rch);
            auto rmin = min(*other.lch, *other.rch);
            if(!(lmin < rmin) && !(rmin < lmin)) {
                auto lmax = max(*lch, *rch);
                auto rmax = max(*other.lch, *other.rch);
                return lmax < rmax;
            }
            return lmin < rmin;
        }
        return value() < other.value();
    }
    set<string> eval() {
        set<string> ss;
        if(leaf) {
            ss.insert(this->to_string(true));
            return ss;
        }
        auto ls = lch->eval(), rs = rch->eval();
        double same = 0;
        ss = move(rs);
        for(auto&& s : ls) {
            same += ss.count(s);
            ss.insert(s);
        }
        ss.insert(this->to_string(true));
        asym = same / (ss.size() - 1);
        return ss;
    }

    void swap_dfs(bool is_left) {
        if(leaf) return;
        if((*lch < *rch && !is_left) || (!(*lch < *rch) && is_left)) {
            swap(lch, rch);
        }
        lch->swap_dfs(true);
        rch->swap_dfs(false);
    }
};

tree_ptr expr(string const& s, int& p) {
    tree_ptr res = make_shared<exp_tree>();
    assert(p < (int)s.size());
    if(s[p] == 'x') {
        p += 1;
        return res;
    }
    res->leaf = false;
    res->lch = expr(s, ++p);
    res->rch = expr(s, ++p);
    p += 1;
    return res;
}

tree_ptr parse(string const& s) {
    int p = 0;
    return expr(s, p);
}

int main() {
    string s;
    while(getline(cin, s), s[0] != '0') {
        auto t = parse(s);
        t->eval();
        t->swap_dfs(true);
        cout << t->to_string(false) << endl;
    }
}
