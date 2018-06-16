#include <bits/stdc++.h>
using namespace std;

// http://codeforces.com/contest/605/problem/B

// 反省点
// operator < が strict weak ordering を満たしておらず，(return used って書いてた)
// TLEをもらっていた．ちゃんと順序つけるようにしましょう．

using pii = pair<int, int>;

struct edge {
    int id;
    int weight;
    int used;

    bool operator<(const edge& other) const {
        if(weight == other.weight) {
            return used > other.used;
        }
        return weight < other.weight;
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<edge> es(m);
    for(int i = 0; i < m; ++i) {
        scanf("%d %d", &es[i].weight, &es[i].used);
        es[i].id = i;
    }
    sort(begin(es), end(es));

    int cnt = 0;
    int idx = 0;
    vector<int> a(m), b(m);
    for(int i = 0; i < n && idx < m; ++i) {
        for(int j = 0; j < i - 1 && idx < m; ++j) {
            a[idx] = j + 1;
            b[idx++] = i + 1;
        }
    }
    idx = 0;

    int can_use_num = 0;
    vector<pii> ans(m);
    for(auto& e : es) {
        if(e.used) {
            cnt += 1;
            can_use_num += cnt - 1;
            ans[e.id] = make_pair(cnt, cnt + 1);
        } else {
            if(can_use_num == 0) {
                ans.clear();
                break;
            } else {
                can_use_num--;
                ans[e.id] = make_pair(a[idx], b[idx]);
                idx++;
            }
        }
    }

    if(ans.empty()) {
        cout << -1 << endl;
    } else {
        for(auto& p : ans) {
            printf("%d %d\n", p.first, p.second);
        }
    }
}
