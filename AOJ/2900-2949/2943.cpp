// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2943

// ��@
// �����̔R�₷���߂�i�ŏ��J�b�g�j�B
// S���Ȃ���Ȃ��AT ���Ȃ����A�̃C���[�W�ŕӂɃR�X�g�����߂��i����͂�����ƈႤ���j�B
// �O���t�̍����͍H�v���K�v�B
// ���u�ƏƖ���ʂɎ��ƃJ�b�g�ɂ��܂��Ӗ������������Ȃ��B
// �����ő��u�������c���āA4�̏Ɩ��̗��v��1�̕ӂɂ܂Ƃ߂Ă��܂����O���t���l���Ă݂�B
// S -> �Ɩ� -> T �͓��R�����悤�ɈӖ����Ȃ��Ȃ����A�����
// ����Ɩ���2�̈قȂ鑕�u�ɉe������邩��ł���B
// ���u�̊Ԃɂ���e���́A�אڂ���s�̑��u���m�ł����������Ȃ��B
// ���̈Ӗ��ő��u�͓񕔃O���t�ł���ƌ�����B
// �����s�ڂ̂��鑕�u�ɒ��ڂ���B
// ���̑��u�ƏƖ����Ƃ��ɂ���4�̒��_����A���̏Ɩ��i1�j�̗��v���̕ӂ𒍖ڂ������u�ɂ͂�B
// �܂��A�����s�ڂ̑��u�̒��_ v �ɂ��āAS -> v �� W ���Av -> T ��4�̏Ɩ��̑��a�̕ӂ��͂�B
// ��s�ڂ͋t�� S -> v ��4�̏Ɩ��̑��a���Av -> T �� W ���͂�B
// S -> v�Av -> T �̃J�b�g�̈Ӗ��͍ŏ��ɍs�����̂Ɠ��������A��s�ڂƋ����s�ڂňӖ����t�ɂȂ��Ă���B
// �R�₷���߂�ł́A0 or 1 ���������_�Ɋ��肠�Ă�C���[�W�����A
// 2�̑��u�𓯎��ɗ��p�����Ƃ��ɁA�d�����ĉ��Z���Ă���Ɩ��̗��v�������K�v������B
// �܂�A�ǂ���̑��u�ɂ� 1 �����蓖�Ă�ꂽ�Ƃ��̂݁A�d�����v�����������B
// ��̂悤�ɈӖ����t�ɂ��Ă������ƂŁA���u�Ԃ̕ӂ̈Ӗ����u����� 0 �ł�������� 1�̂Ƃ��v�̃R�X�g�A
// �܂�i�Е��̈Ӗ����t�]���Ă��邱�Ƃ��l����΁j�ǂ���� 1 �̂Ƃ��̃R�X�g�A�Ƃ�����B
// ���̃O���t�ɂ�����ŏ��J�b�g���A���u���֌W����4�̏Ɩ��̘a�̑��a������������̂������B
// �񕔃O���t���Ƃ������ƂɋC�Â��ƌ������́A�d���������悤�ȕӂ𒣂�Ƃ���
// ���R�񕔃O���t�ł��邱�Ƃ��g���ă��b�L�[�Ƃ��������߂������B

// ������̒���
// long long ���g���܂��傤


#include <bits/stdc++.h>
using namespace std;

template <typename Edge>
class graph {
    using graph_t = std::vector<std::vector<Edge>>;
public:
    using reference = std::vector<Edge>&;
    using const_reference = std::vector<Edge> const&;
    using iterator = typename graph_t::iterator;
    using const_iterator = typename graph_t::const_iterator;
    using reverse_iterator = typename graph_t::reverse_iterator;

    graph() : g() {}
    graph(int n) : g(n) {}

    reference operator[](int x) { return g[x]; }
    const_reference operator[](int x) const { return g[x]; }

    iterator begin() { return std::begin(g); }
    const_iterator begin() const { return std::begin(g); }
    iterator end() { return std::end(g); }
    const_iterator end() const { return std::end(g); }
    reverse_iterator rbegin() { return std::rbegin(g); }
    reverse_iterator rend() { return std::rend(g); }

    int size() const { return g.size(); }

    void add_node(std::vector<Edge> es) {
        g.push_back(std::move(es));
    }

private:
    std::vector<std::vector<Edge>> g;
};

// ============================================================================
// capacity graph (for maximum flow)
template <typename Capacity>
struct capacity_edge {
    using capacity_type = Capacity;
    int to, rev;
    capacity_type cap;
    capacity_edge(int t, int r, capacity_type c) : to(t), rev(r), cap(c) {}
};

template <typename Capacity>
using capacity_graph = graph<capacity_edge<Capacity>>;

template <typename Capacity>
void add_edge(capacity_graph<Capacity>& g, int from, int to, Capacity cap) {
    g[from].emplace_back(to, static_cast<int>(g[to].size()), cap);
    g[to].emplace_back(from, static_cast<int>(g[from].size() - 1), Capacity{0});
}


template <typename Edge, typename Capacity = typename Edge::capacity_type>
Capacity augment(graph<Edge>& g, std::vector<int> level, std::vector<int>& iter, int v, int t, Capacity f) {
    if(v == t) return f;
    for(int i = iter[v]; i < (int)g[v].size(); ++i) {
        auto& e = g[v][i];
        if(e.cap > 0 && level[v] < level[e.to]) {
            const auto d = augment(g, level, iter, e.to, t, std::min(f, e.cap));
            if(d > 0) {
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

template <typename Edge, typename Capacity = typename Edge::capacity_type>
Capacity max_flow(graph<Edge>& g, int s, int t) {
    const auto inf = std::numeric_limits<Capacity>::max() / 2;
    Capacity flow = 0;
    while(true) {
        std::vector<int> level(g.size(), -1);
        level[s] = 0;
        std::queue<int> que;
        que.push(s);
        while(!que.empty()) {
            const int v = que.front();
            que.pop();
            for(auto const& e : g[v]) {
                if(e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }

        if(level[t] < 0) return flow;
        std::vector<int> iter(g.size());
        Capacity f{0};
        while((f = augment(g, level, iter, s, t, inf)) > 0) {
            flow += f;
        }
    }
}

using ll = long long;

constexpr ll inf = 1e18;

int main() {
    int h, w, W; cin >> h >> w >> W;
    vector<vector<ll>> b(h, vector<ll>(w));
    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            cin >> b[i][j];
        }
    }

    const int source = (h - 1) * (w - 1);
    const int sink = source + 1;
    capacity_graph<ll> g((h - 1) * (w - 1) + 2);
    ll sum = 0;
    for(int i = 0; i < h - 1; ++i) {
        for(int j = 0; j < w - 1; ++j) {
            if((i + j) % 2 != 0) continue;
            const int v = i * (w - 1) + j;
            const ll c = b[i][j] + b[i + 1][j] + b[i][j + 1] + b[i + 1][j + 1];
            sum += c;
            if(i & 1) {
                add_edge(g, source, v, (ll)W);
                add_edge(g, v, sink, (ll)c);
                add_edge(g, (i - 1) * (w - 1) + j - 1, v, (ll)b[i][j]);
                add_edge(g, (i - 1) * (w - 1) + j + 1, v, (ll)b[i][j + 1]);
                if(i + 1 >= h - 1) continue;
                add_edge(g, (i + 1) * (w - 1) + j - 1, v, (ll)b[i + 1][j]);
                add_edge(g, (i + 1) * (w - 1) + j + 1, v, (ll)b[i + 1][j + 1]);
            } else {
                add_edge(g, source, v, (ll)c);
                add_edge(g, v, sink, (ll)W);
            }
            
        }
    }

    cout << sum - max_flow(g, source, sink) << endl;
}