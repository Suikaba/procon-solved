#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

constexpr int mod = 1e9 + 7;

constexpr int rev_tbl[2][4][2] = { // [mir][rot][row/col]
    {{0, 0}, {1, 0}, {1, 1}, {0, 1}},
    {{0, 1}, {1, 1}, {1, 0}, {0, 0}}
};

int main() {
    ll n, q, A, B, C, D, E, F, G;
    cin >> n >> q >> A >> B >> C >> D >> E >> F >> G;

    vector<string> op(q);
    vector<int> w(q), x(q), y(q), z(q);
    for(int i = 0; i < q; ++i) {
        cin >> op[i];
        if(op[i] == "WR") cin >> w[i] >> x[i] >> y[i];
        else if(op[i] == "CP") cin >> w[i] >> x[i] >> y[i] >> z[i];
        else if(op[i] == "SR") cin >> w[i] >> x[i];
        else if(op[i] == "SC") cin >> w[i] >> x[i];
    }

    int mir = 0, rot = 0;
    vector<int> ridx(n), cidx(n);
    iota(begin(ridx), end(ridx), 1);
    iota(begin(cidx), end(cidx), 1);
    auto get_r_idx = [&] (int r) -> int& {
        const int i = (rev_tbl[mir][rot][0] ? n - r : r - 1);
        return rot & 1 ? cidx[i] : ridx[i];
    };
    auto get_c_idx = [&] (int c) -> int& {
        const int i = (rev_tbl[mir][rot][1] ? n - c : c - 1);
        return rot & 1 ? ridx[i] : cidx[i];
    };
    auto get_orig_pos = [&] (int r, int c) {
        if(rot & 1) return make_pair(get_c_idx(c), get_r_idx(r));
        else        return make_pair(get_r_idx(r), get_c_idx(c));
    };
    map<pii, int> v;
    for(int i = 0; i < q; ++i) {
        if(op[i] == "WR") {
            int r, c; tie(r, c) = get_orig_pos(w[i], x[i]);
            v[{r, c}] = y[i];
        } else if(op[i] == "CP") {
            int r1, c1, r2, c2;
            tie(r1, c1) = get_orig_pos(w[i], x[i]);
            tie(r2, c2) = get_orig_pos(y[i], z[i]);
            if(v.count({r1, c1})) {
                v[{r2, c2}] = v[{r1, c1}];
            } else {
                v[{r2, c2}] = (r1 * A + c1 * B) % C;
            }
        } else if(op[i] == "SR") {
            swap(get_r_idx(w[i]), get_r_idx(x[i]));
        } else if(op[i] == "SC") {
            swap(get_c_idx(w[i]), get_c_idx(x[i]));
        } else if(op[i] == "RL") {
            if(mir) rot = (rot + 3) % 4;
            else    rot = (rot + 1) % 4;
        } else if(op[i] == "RR") {
            if(mir) rot = (rot + 1) % 4;
            else    rot = (rot + 3) % 4;
        } else if(op[i] == "RH") {
            mir = !mir;
            rot = (rot + 2) % 4;
        } else if(op[i] == "RV") {
            mir = !mir;
        }
    }

    ll h = 314159265;
    for(int r = D; r <= E; ++r) {
        for(int c = F; c <= G; ++c) {
            int rr, cc; tie(rr, cc) = get_orig_pos(r, c);
            const ll val = v.count({rr, cc}) ? v[{rr, cc}] : (rr * A + cc * B) % C;
            h = (h * 31 + val) % mod;
        }
    }
    cout << h << endl;
}
