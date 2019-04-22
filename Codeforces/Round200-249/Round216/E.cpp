#include <bits/stdc++.h>
using namespace std;

template <typename T>
class fenwick_tree {
public:
    fenwick_tree(int n_) : n(n_), dat(n, 0) {}

    void add(int i, T value) {
        for(; i < n; i |= i + 1) {
            dat[i] += value;
        }
    }

    T sum(int i) const {
        T res = 0;
        for(; i >= 0; i = (i & (i + 1)) - 1) {
            res += dat[i];
        }
        return res;
    }
    // [l, r)
    T sum(int l, int r) const {
        return sum(r - 1) - sum(l - 1);
    }

private:
    const int n;
    std::vector<T> dat;
};

constexpr int add_id = -1e9;
constexpr int remove_id = 1e9;

struct query {
    int id, pos, next_pos;
    query(int i, int p, int np) : id(i), pos(p), next_pos(np) {}
    bool operator<(const query& other) const {
        return make_tuple(pos, id, next_pos) < make_tuple(other.pos, other.id, other.next_pos);
    }
};


int main() {
    int n, m; cin >> n >> m;
    vector<query> qs;
    for(int i = 0; i < n; ++i) {
        int l, r; cin >> l >> r;
        qs.emplace_back(add_id, l, r);
        qs.emplace_back(remove_id, r, -1);
    }
    for(int i = 0; i < m; ++i) {
        int cnt; cin >> cnt;
        vector<int> ps(cnt + 1);
        for(int j = 0; j < cnt; ++j) {
            cin >> ps[j];
        }
        ps[cnt] = 1 << 20;
        for(int j = 0; j < cnt; ++j) {
            qs.emplace_back(i, ps[j], ps[j + 1]);
        }
    }
    sort(begin(qs), end(qs));

    vector<int> ans(m);
    fenwick_tree<int> bit(1 << 20);
    for(const auto& q : qs) {
        if(q.id == add_id) {
            bit.add(q.next_pos, 1);
        } else if(q.id == remove_id) {
            bit.add(q.pos, -1);
        } else {
            ans[q.id] += bit.sum(q.next_pos - 1);
        }
    }

    for(int i = 0; i < m; ++i) {
        cout << ans[i] << "\n";
    }
}
