#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int dy[4] = {0, 1, 0, -1};
constexpr int dx[4] = {1, 0, -1, 0};

int main() {
    int w, h;
    while(cin >> w >> h, w) {
        vector<vector<int>> r(h, vector<int>(w)), idx(h, vector<int>(w, -1));
        vector<int> xs, ys;
        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < w; ++j) {
                cin >> r[i][j];
                if(r[i][j] == 1) {
                    idx[i][j] = ys.size();
                    ys.push_back(i);
                    xs.push_back(j);
                }
            }
        }
        const int n = xs.size();
        if(n & 1) {
            cout << "NO" << endl;
            continue;
        }

        auto in_range = [&] (int y, int x) {
            return 0 <= y && y < h && 0 <= x && x < w;
        };
        auto calc_dy = [] (int mir, int rot, int s_dy, int s_dx) {
            if(rot == 0)      return s_dy;
            else if(rot == 1) return (mir ? -s_dx : s_dx);
            else if(rot == 2) return -s_dy;
            else              return (mir ? s_dx : -s_dx);
        };
        auto calc_dx = [] (int mir, int rot, int s_dy, int s_dx) {
            if(rot == 0)      return (mir ? -s_dx : s_dx);
            else if(rot == 1) return s_dy;
            else if(rot == 2) return (mir ? s_dx : -s_dx);
            else              return -s_dy;
        };

        auto solve = [&] () {
            for(int j = 1; j < n; ++j) {
                for(int rot = 0; rot < 4; ++rot) {
                    for(int mir = 0; mir < 2; ++mir) {
                        unordered_set<ll> vis;
                        stack<pair<ll, ll>> st;
                        vis.insert(1);
                        st.emplace(1, 1LL << j);
                        while(!st.empty()) {
                            const ll used1 = st.top().first, used2 = st.top().second;
                            //cout << "  " << used1 << " " << used2 << endl;
                            if(__builtin_popcountll(used1) * 2 == n) {
                                return true;
                            }
                            st.pop();
                            for(int k = 0; k < n; ++k) {
                                if(!(used1 & (1LL << k))) continue;
                                for(int d = 0; d < 4; ++d) {
                                    const int ny1 = ys[k] + dy[d], nx1 = xs[k] + dx[d];
                                    const int ny2 = ys[j] + calc_dy(mir, rot, ny1 - ys[0], nx1 - xs[0]);
                                    const int nx2 = xs[j] + calc_dx(mir, rot, ny1 - ys[0], nx1 - xs[0]);
                                    if(!in_range(ny1, nx1) || idx[ny1][nx1] == -1) continue;
                                    if(!in_range(ny2, nx2) || idx[ny2][nx2] == -1) continue;
                                    const int id1 = idx[ny1][nx1], id2 = idx[ny2][nx2];
                                    if((used1 | used2) & (1LL << id1) || (used1 | used2) & (1LL << id2) || id1 == id2) continue;
                                    if(vis.count(used1 | (1LL << id1))) continue;
                                    vis.insert(used1 | (1LL << id1));
                                    st.emplace(used1 | (1LL << id1), used2 | (1LL << id2));
                                }
                            }
                        }
                    }
                }
            }
            return false;
        };

        cout << (solve() ? "YES" : "NO") << endl;
    }
}
