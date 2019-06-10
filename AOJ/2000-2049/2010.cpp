#include <bits/stdc++.h>
using namespace std;

// 実装方針が壊れた
// 厳密に言うと、”きっちり”シミュレーションしてしまったので実装量が破滅した
// というかダイクストラいる？ワーシャル・フロイドで十分だったね、楽だし
// うーん、でも変に頭良くやるとバグったときにヤバそうだから難しい。
// 頭良くやってバグらせないようにするか、バグる前提でデバッグしやすい形で書くか？
// うまくやれば両方取れるんかな。わかんねー（まあこんな問題二度と出ないね

using pii = pair<int, int>;
constexpr int inf = numeric_limits<int>::max();

struct edge {
    int from, to, cost;
    edge(int f, int t, int c) : from(f), to(t), cost(c) {}
};

using edges = vector<edge>;
using graph = vector<edges>;

void add_edge(graph& g, int from, int to, int cost) {
    g[from].emplace_back(from, to, cost);
    g[to].emplace_back(to, from, cost);
}

vector<int> dijkstra(graph const& g, int s) {
    const int n = g.size();
    vector<int> dist(n, inf / 2);
    dist[s] = 0;
    priority_queue<pii, vector<pii>, greater<>> que;
    que.emplace(0, s);
    while(!que.empty()) {
        int cur_d, v; tie(cur_d, v) = que.top();
        que.pop();
        if(cur_d > dist[v]) continue;
        for(auto const& e : g[v]) {
            if(dist[e.to] > dist[v] + e.cost) {
                dist[e.to] = dist[v] + e.cost;
                que.emplace(dist[e.to], e.to);
            }
        }
    }
    return dist;
}

edge calc_next_v(graph const& g, int s, int t) {
    const auto from_s = dijkstra(g, s);
    const auto from_t = dijkstra(g, t);
    edge res{s, inf, -1};
    for(auto const& e : g[s]) {
        if(from_s[e.from] + e.cost + from_t[e.to] == from_s[t] && res.to > e.to) {
            res = e;
        }
    }
    return res;
}

struct packet {
    string name;
    int to;
    packet(string n, int t) : name(n), to(t) {}
};

struct event {
    int from, time;
    packet pkt;
    event(int f, int t, packet p) : from(f), time(t), pkt(p) {}
    bool operator>(const event& e) const {
        return time > e.time;
    }
};

struct postman {
    int idx, cur, dst, remain, ecost;
    vector<packet> ps;
    postman(int i) : idx(i), cur(i), dst(-1), remain(0), ecost(-1) {}

    void move(int cur_t, int t, vector<vector<event>>& tasks, vector<pair<int, string>>& ans) {
        while(t != 0 && dst != -1) {
            const int use = min(remain, t);
            remain -= use, t -= use;
            cur_t += use;
            if(remain == 0) {
                cur = dst;
                dst = -1;
                for(auto const& p : ps) {
                    if(p.to == cur) {
                        ans.emplace_back(cur_t, p.name);
                    } else {
                        tasks[cur].emplace_back(cur, cur_t, p);
                    }
                }
                ps.clear();
                if(cur != idx) { // return to original
                    dst = idx;
                    remain = ecost;
                }
            }
        }
        assert(t >= 0);
    }
};

int main() {
    int n, m;
    bool first = true;
    while(cin >> n >> m, n) {
        if(!first) cout << '\n';
        first = false;

        graph g(n);
        for(int i = 0; i < m; ++i) {
            int f, t, cost; cin >> f >> t >> cost;
            f--, t--;
            add_edge(g, f, t, cost);
        }
        vector<vector<edge>> sg(n);
        for(int s = 0; s < n; ++s) {
            for(int t = 0; t < n; ++t) {
                sg[s].push_back(calc_next_v(g, s, t));
            }
        }
        int l; cin >> l;
        vector<event> ev;
        for(int i = 0; i < l; ++i) {
            int s, t, time; cin >> s >> t >> time;
            string name; cin >> name;
            s--, t--;
            ev.emplace_back(s, time, packet{name, t});
        }
        sort(begin(ev), end(ev), greater<>{});

        vector<postman> man;
        for(int i = 0; i < n; ++i) {
            man.emplace_back(i);
        }
        int cur_t = 0;
        vector<vector<event>> tasks(n);
        vector<pair<int, string>> ans;
        auto is_finished = [&] () {
            if(!ev.empty()) return false;
            for(auto const& t : tasks) {
                if(!t.empty()) return false;
            }
            for(auto const& p : man) {
                if(p.dst != -1) return false;
            }
            return true;
        };
        while(!is_finished()) {
            //cout << "cur_t: " << cur_t << endl;
            // determine next time
            int nxt_t = inf;
            for(auto const& p : man) {
                if(p.dst == -1) continue;
                nxt_t = min(nxt_t, cur_t + p.remain);
            }
            if(!ev.empty()) nxt_t = min(nxt_t, ev.back().time);
            //cout << "ev.sz: " << ev.size() << endl;
            //cout << "elapsed: " << nxt_t - cur_t << endl;

            // first, resolve task
            while(!ev.empty() && ev.back().time == nxt_t) {
                tasks[ev.back().from].push_back(ev.back());
                ev.pop_back();
            }

            // second, resolve postman
            for(int i = 0; i < n; ++i) {
                man[i].move(cur_t, nxt_t - cur_t, tasks, ans);
            }
            for(int i = 0; i < n; ++i) {
                // returned to original office
                if(man[i].dst != -1) continue;
                if(!tasks[i].empty()) {
                    vector<event> nxt_ts;
                    int min_time = inf, min_to = inf, ecost = -1;
                    for(auto const& t : tasks[i]) {
                        if(make_pair(min_time, min_to) > make_pair(t.time, sg[i][t.pkt.to].to)) {
                            min_time = t.time;
                            min_to = sg[i][t.pkt.to].to;
                            ecost = sg[i][t.pkt.to].cost;
                        }
                    }
                    assert(ecost >= 1);
                    man[i].remain = man[i].ecost = ecost;
                    man[i].dst = min_to;
                    for(auto const& t : tasks[i]) {
                        if(sg[i][t.pkt.to].to == min_to) {
                            man[i].ps.push_back(t.pkt);
                        } else {
                            nxt_ts.push_back(t);
                        }
                    }
                    tasks[i] = move(nxt_ts);
                }
            }
            cur_t = nxt_t;
        }

        //cout << "finished: " << endl;
        sort(begin(ans), end(ans));
        for(auto const& p : ans) {
            cout << p.second << " " << p.first << '\n';
        }
    }
}
