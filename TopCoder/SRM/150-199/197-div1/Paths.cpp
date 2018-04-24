#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9;
using pii = pair<int, int>;

class Paths {
public:
    int secondBest(vector <string> graph, int from, int to) {
        const int n = graph.size();
        vector<int> d(n, inf);
        vector<int> d2(n, inf);
        priority_queue<pii, vector<pii>, greater<pii>> que;
        d[from] = 0;
        que.emplace(0, from);
        while(!que.empty()) {
            auto p = que.top();
            que.pop();
            const int v = p.second;
            if(p.first > d2[p.second]) {
                continue;
            }
            for(int i = 0; i < n; ++i) {
                if(graph[v][i] == 'X') continue;
                const int nd = p.first + (graph[v][i] - '0');
                if(d[i] > nd) {
                    d2[i] = d[i];
                    d[i] = nd;
                    que.emplace(nd, i);
                } else if(d2[i] > nd && nd > d[i]) {
                    d2[i] = nd;
                    que.emplace(nd, i);
                }
            }
        }

        return (d2[to] == inf ? -1 : d2[to]);
    }
};

