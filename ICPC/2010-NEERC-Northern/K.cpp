
// n と k が両方奇数なので、k 色以下で塗る方法は必ず存在することが示せる。
//（ちなみに、両方偶数でもいける気がするが、偶奇が異なる場合は成り立たないことがある）
//次数の大きい方からとっていくだけだとうまくいかない。
//そこで、以下のアルゴリズムを考える。
// 1. S をすべての頂点からなる集合とする
// 2. S が空でないなら、S で deg(v) が最小のものを取り出し、v とする
// 3. 配列 ord の末尾に v を追加
// 4. v の隣接頂点の次数をデクリメントする
// 5. 2 に戻る
//このとき、ord[i] について以下の不変条件が成り立つ。
//「頂点 ord[i] は、j < i なる任意の頂点 ord[j] に色が塗られていなければ、ほかはどのように彩色されていても、ある色で塗ることができる」
//以下、大雑把な証明。
//deg(ord[i]) < k ならば、そもそも好きに色をぬることができる。
//deg(ord[i]) = k となることはない。もし成り立つとすると ord[i] の隣接頂点は一度も v として選ばれておらず、deg(u) = k (u は隣接頂点) が成り立つ。同様に u の隣接頂点も選ばれていないから…と議論が続き、結局この段階では ord[i] 以外の任意の頂点が選ばれていないことになる。すなわち、G は完全グラフである。k が奇数なので、G は偶数個の頂点を含むが、これは矛盾である。
//よって、あとは ord[i] の逆順に色を適当に塗っていけばうまくいく。
//要は自由に塗れるやつは後回しにする、という発想でしかない。

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
    ifstream ifs("kgraph.in");
    int n, m; ifs >> n >> m;
    vector<vector<int>> g(n);
    vector<int> deg(n);
    int k = 0;
    for(int i = 0; i < m; ++i) {
        int a, b; ifs >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
        deg[a] += 1;
        deg[b] += 1;
        k = max({k, deg[a], deg[b]});
    }
    k += k % 2 == 0;

    set<pii> s; // (deg, v)
    vector<int> ord(n);
    for(int v = 0; v < n; ++v) s.emplace(deg[v], v);
    for(int i = 0; i < n; ++i) {
        const int v = s.begin()->second;
        s.erase(s.begin());
        ord[i] = v;
        for(auto to : g[v]) {
            if(s.count(make_pair(deg[to], to))) {
                s.erase(make_pair(deg[to], to));
                deg[to]--;
                s.emplace(deg[to], to);
            }
        }
    }

    vector<int> ans(n, -1);
    for(int i = n - 1; i >= 0; --i) {
        const int v = ord[i];
        vector<bool> used(k + 1);
        for(auto to : g[v]) {
            if(ans[to] == -1) continue;
            used[ans[to]] = true;
        }
        for(int j = 1; j <= k; ++j) {
            if(!used[j]) {
                ans[v] = j;
                break;
            }
        }
    }

    ofstream ofs("kgraph.out");
    ofs << k << '\n';
    for(int i = 0; i < n; ++i) {
        ofs << ans[i] << '\n';
    }
}
