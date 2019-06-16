#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int n;
    while(cin >> n, n) {
        vector<int> low(n), high(n);
        for(int i = 0; i < n; ++i) {
            cin >> low[i] >> high[i];
        }

        // build NFA
        const int fin = n * 4; // finish node
        vector<vector<vector<int>>> nfa(n * 4 + 1, vector<vector<int>>(10));
        for(int i = 0; i < n; ++i) {
            if(low[i] < 10) { // Pi -> Pi+1
                for(int x = low[i]; x <= min(9, high[i]); ++x) {
                    nfa[i * 4][x].push_back(i * 4 + 4);
                }
            } else {
                // Pi -> Qi -> Pi+1
                nfa[i * 4][low[i] / 10].push_back(i * 4 + 1);
                const int ub = low[i] / 10 == high[i] / 10 ? high[i] % 10 : 9;
                for(int x = low[i] % 10; x <= ub; ++x) {
                    nfa[i * 4 + 1][x].push_back(i * 4 + 4);
                }
            }
            // Pi -> Ri -> Pi+1
            for(int x = low[i] / 10 + 1; x < high[i] / 10; ++ x) {
                nfa[i * 4][x].push_back(i * 4 + 2);
            }
            for(int x = 0; x <= 9; ++x) {
                nfa[i * 4 + 2][x].push_back(i * 4 + 4);
            }
            if(high[i] >= 10) {// Pi -> Si -> Pi+1
                nfa[i * 4][high[i] / 10].push_back(i * 4 + 3);
                const int lb = low[i] / 10 == high[i] / 10 ? low[i] % 10 : 0;
                for(int x = lb; x <= high[i] % 10; ++x) {
                    nfa[i * 4 + 3][x].push_back(i * 4 + 4);
                }
            }
        }

        // build DFA
        map<int, array<int, 10>> dfa;
        {
            queue<int> que;
            que.push(1);
            set<int> vis = {1};
            while(!que.empty()) {
                const int S = que.front();
                que.pop();
                for(int x = 0; x <= 9; ++x) {
                    int nS = 0;
                    for(int i = 0; i < 4 * n; ++i) {
                        if(!(S & (1 << i))) continue;
                        for(auto const to : nfa[i][x]) {
                            nS |= 1 << to;
                        }
                    }
                    dfa[S][x] = nS == 0 ? -1 : nS;
                    if(nS == 0 || vis.count(nS)) continue;
                    que.push(nS);
                    vis.insert(nS);
                }
            }
        }

        map<int, ll> memo;
        function<ll(int)> solve = [&] (int S) {
            if(memo.count(S)) return memo[S];
            if(S == (1 << fin)) return 1LL;
            for(int x = 0; x <= 9; ++x) {
                if(dfa[S][x] == -1) continue;
                memo[S] += solve(dfa[S][x]);
            }
            if(S & (1 << fin)) {
                memo[S] += 1;
            }
            return memo[S];
        };

        cout << solve(1) << endl;
    }
}
