#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using pdd = pair<double, double>;
constexpr double eps = 1e-12;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n;
    while(cin >> n) {
        map<pii, int> car;
        vector<double> ts;
        for(int i = 0; i < n; ++i) {
            int t, v; cin >> t >> v;
            car[make_pair(t, v)] += 1;
            ts.push_back(t);
        }

        {
            auto cs = car;
            deque<pii> que;
            for(auto const [p, _] : cs) {
                const auto [ti, vi] = p;
                if(!que.empty() && ti - que.front().first >= 100) {
                    que.pop_front();
                }
                for(auto const [tj, vj] : que) {
                    if(vi != vj) {
                        const double t = (double)(vi * ti - vj * tj) / (vi - vj);
                        if(t >= ti && vi * (t - ti) <= 100) {
                            ts.push_back((double)(vi * ti - vj * tj) / (vi - vj));
                        }
                    }
                }
                que.emplace_back(ti, vi);
            }
            sort(begin(ts), end(ts));
            vector<double> tts;
            for(auto t : ts) {
                if(tts.empty() || abs(tts.back() - t) > eps) {
                    tts.push_back(t);
                }
            }
            ts = move(tts);
        }

        int ans = 1;
        auto it = car.begin();
        double cur_t = 0;
        vector<tuple<double, double, int>> cur; // (pos, v, cnt)
        for(auto t : ts) {
            const double lapse = t - cur_t;
            {
                for(auto& [p, v, cnt] : cur) {
                    p += v * lapse;
                }
                cur.erase(remove_if(begin(cur), end(cur), [] (auto const& c) { return get<0>(c) > 100 + eps; }), end(cur));
            }
            while(it != end(car) && t >= it->first.first) {
                if(it->first.second * (t - it->first.first) <= 100 + eps) {
                    cur.emplace_back(it->first.second * (t - it->first.first), it->first.second, it->second);
                }
                ++it;
            }
            sort(begin(cur), end(cur));
            int cnt = 0;
            double prev_p = -1;
            for(auto const& [p, _, c] : cur) {
                if(p - prev_p < eps) { // same pos
                    cnt += c;
                } else {
                    cnt = c;
                }
                prev_p = p;
                ans = max(ans, cnt);
            }
            cur_t = t;
        }

        cout << ans << endl;
    }
}
