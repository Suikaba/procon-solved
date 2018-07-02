
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0343

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

unsigned xor128() {
    static unsigned x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    unsigned t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}

struct node;
using T = pair<ll, int>;
using node_ptr = std::shared_ptr<node>;

struct node {
    T val;
    node_ptr lch, rch;
    int size;
    node(T val, node_ptr l = nullptr, node_ptr r = nullptr)
        : val(val), lch(l), rch(r), size(1)
    {}
};

node_ptr create_node(T val) {
    return std::make_shared<node>(val);
}


int count(node_ptr t) {
    return !t ? 0 : t->size;
}

node_ptr update(node_ptr t) {
    t->size = count(t->lch) + count(t->rch) + 1;
    return t;
}

node_ptr merge(node_ptr l, node_ptr r) {
    if(!l || !r) return !l ? r : l;
    if(xor128() % (l->size + r->size) < (unsigned)l->size) {
        l->rch = merge(l->rch, r);
        return update(l);
    } else {
        r->lch = merge(l, r->lch);
        return update(r);
    }
}

std::pair<node_ptr, node_ptr> split(node_ptr t, int k) {
    assert(0 <= k && k <= count(t));
    if(!t) return std::make_pair(nullptr, nullptr);
    if(k <= count(t->lch)) {
        auto s = split(t->lch, k);
        t->lch = s.second;
        return std::make_pair(s.first, update(t));
    } else {
        auto s = split(t->rch, k - count(t->lch) - 1);
        t->rch = s.first;
        return std::make_pair(update(t), s.second);
    }
}

void insert(node_ptr& t, int k, T val) {
    auto x = split(t, k);
    t = merge(merge(x.first, create_node(val)), x.second);
}
void erase(node_ptr& t, int k) {
    auto x = split(t, k);
    t = merge(x.first, split(x.second, 1).second);
}

T kth_element(node_ptr t, int k) {
    assert(k < t->size);
    if(k < count(t->lch)) return kth_element(t->lch, k);
    if(k == count(t->lch)) return t->val;
    return kth_element(t->rch, k - count(t->lch) - 1);
}

int lower_bound(node_ptr t, const T& v) {
    if(!t) return 0;
    if(v <= t->val) return lower_bound(t->lch, v);
    return lower_bound(t->rch, v) + count(t->lch) + 1;
}

void insert_key(node_ptr& t, const T& v) {
    insert(t, lower_bound(t, v), v);
}
void erase_key(node_ptr& t, const T& v) {
    erase(t, lower_bound(t, v));
}

int main() {
    int n, c;
    cin >> n >> c;
    node_ptr s;
    vector<ll> score(n);
    for(int i = 0; i < n; ++i) {
        insert_key(s, make_pair(0, i + 1));
    }
    for(int i = 0; i < c; ++i) {
        int type;
        cin >> type;
        if(type == 0) {
            int t, p;
            cin >> t >> p;
            erase_key(s, make_pair(score[t - 1], t));
            score[t - 1] -= p;
            insert_key(s, make_pair(score[t - 1], t));
        } else {
            int m;
            cin >> m;
            auto res = kth_element(s, m - 1);
            cout << res.second << ' ' << -res.first << endl;
        }
    }
}
