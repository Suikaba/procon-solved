
// @author kazuma8128

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using edge = pair<int, int>;
using graph = vector<vector<edge>>;

class union_find {
	vector<int> par;
public:
	union_find(int n) : par(n, -1) {}
	int find(int a) {
		return par[a] < 0 ? a : par[a] = find(par[a]);
	}
	bool same(int a, int b) {
		return find(a) == find(b);
	}
	void unite(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return;
		if (par[a] < par[b]) {
			par[a] += par[b];
			par[b] = a;
		}
		else {
			par[b] += par[a];
			par[a] = b;
		}
	}
	int size(int a) {
		return -par[find(a)];
	}
};

const int MAX = 1e5;

int used[MAX];
int usin[MAX];

vector<int> rps[MAX * 2];

ll cost[MAX * 3];

void dfs(int v, int prev, const graph& G, vector<int>& vs, vector<int>& es, union_find& uf) {
	vs.push_back(v);
	used[v] = true;
	usin[v] = true;
	for (auto e : G[v]) if (e.first != prev) {
		if (usin[e.first]) {
			int id = e.second;
			for (int i = vs.size() - 1; vs[i] != e.first; i--) {
				uf.unite(es[i - 1], id);
			}
			id = uf.find(id);
			rps[id].clear();
			rps[id].push_back(e.first);
			for (int i = vs.size() - 1; vs[i] != e.first; i--) {
				rps[id].push_back(vs[i]);
			}
			continue;
		}
		if (used[e.first]) continue;
		es.push_back(e.second);
		dfs(e.first, v, G, vs, es, uf);
		es.pop_back();
	}
	vs.pop_back();
	usin[v] = false;
}

unordered_map<int, unordered_map<int, ll>> wei;

ll dfs2(int v, int prev, const vector<vector<int>>& G) {
	ll res = cost[v];
	for (auto to : G[v]) if (to != prev) {
		res += (wei[v][to] = dfs2(to, v, G));
	}
	return res;
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(0);
	int n, m;
	cin >> n >> m;
	graph G(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v; --u, --v;
		G[u].emplace_back(v, i);
		G[v].emplace_back(u, i);
	}
	union_find uf(m);
	vector<int> vs, es;
	dfs(0, -1, G, vs, es, uf);
	vector<int> eid(m);
	int teid = 0;
	vector<int> aa;
	for (int i = 0; i < m; i++) if (uf.find(i) == i) {
		aa.push_back(i);
		eid[i] = teid++;
	}
	for (int i = 0; i < m; i++) {
		eid[i] = eid[uf.find(i)];
	}
	vector<vector<int>> T(n + teid);
	for (int i = 0; i < n; i++) {
		for (auto e : G[i]) {
			int id = eid[e.second] + n;
			T[id].push_back(i);
			T[i].push_back(id);
		}
	}
	for (int i = 0; i < n + teid; i++) {
		sort(T[i].begin(), T[i].end());
		T[i].erase(unique(T[i].begin(), T[i].end()), T[i].end());
	}
	for (int i = 0; i < n; i++) cost[i] = 1;
	ll all = dfs2(0, -1, T);
	ll res = 0;
	for (int v = n; v < n + teid; v++) {
		vector<ll> ws;
		if (rps[aa[v - n]].empty()) {
			for (auto to : T[v]) if (to < n) {
				if (!wei.count(v) || !wei[v].count(to)) {
					assert(wei.count(to) && wei[to].count(v));
					wei[v][to] = all - wei[to][v];
				}
				ws.push_back(wei[v][to]);
			}
		}
		for (auto to : rps[aa[v - n]]) {
			if (!wei.count(v) || !wei[v].count(to)) {
				assert(wei.count(to) && wei[to].count(v));
				wei[v][to] = all - wei[to][v];
			}
			ws.push_back(wei[v][to]);
		}
		int sz = ws.size();
		for (int i = 0; i < sz; i++) ws.push_back(ws[i]);
		vector<ll> sum(sz * 2 + 1), lsum(sz * 2 + 1);
		for (int i = 0; i < sz * 2; i++) {
			sum[i + 1] = sum[i] + ws[i];
		}
		for (int i = 0; i < sz * 2; i++) {
			lsum[i + 1] = lsum[i] + (sum[i + 1] - sum[0]);
		}
		auto get = [&](int l, int r) {
			return (lsum[r] - lsum[l]) - (sum[l] - sum[0]) * (r - l);
		};
		int dz = sz / 2;
		for (int i = 0; i < sz; i++) {
			res += ws[i] * get(sz + i - dz, sz + i);
		}
		if (sz % 2 == 0) {
			for (int i = 0; i < dz; i++) {
				res -= ws[i] * ws[i + dz] * dz;
			}
		}
	}
	cout << res << endl;
	return 0;
}

