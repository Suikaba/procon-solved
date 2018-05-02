#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1234

// 反省点
// 一部誤読があった
// 不必要な変数を保持していた（今のコードには無いが

using pii = pair<int, int>;

struct team {
    int id;
    int goal, score, goal_diff;

    team() : id(-1), goal(0), score(0), goal_diff(0) {}

    bool operator<(const team& t) const {
        if(score != t.score) return score < t.score;
        if(goal_diff != t.goal_diff) return goal_diff < t.goal_diff;
        return goal < t.goal;
    }
    bool operator==(const team& t) const {
        return score == t.score && goal_diff == t.goal_diff && goal == t.goal;
    }
};

int main() {
    cout << fixed << setprecision(7);

    vector<double> possibility(9);
    vector<double> fact(9, 1);
    for(int i = 2; i <= 8; ++i) {
        fact[i] = fact[i - 1] * i;
    }
    for(int i = 0; i <= 8; ++i) {
        possibility[i] = fact[8] / fact[i] / fact[8 - i] * pow(0.25, i) * pow(0.75, 8 - i);
    }

    int T;
    cin >> T;
    while(T--) {
        int target = 0;
        vector<team> teams(4);
        vector<vector<int>> goal(4, vector<int>(4));
        for(int i = 0; i < 4; ++i) {
            teams[i].id = i;
        }

        auto calc_scores = [](team& t1, team& t2, int g1, int g2) {
            t1.goal += g1;
            t1.goal_diff += g1 - g2;
            t2.goal += g2;
            t2.goal_diff += g2 - g1;
            if(g1 > g2) {
                t1.score += 3;
            } else if(g2 > g1) {
                t2.score += 3;
            } else {
                t1.score += 1;
                t2.score += 1;
            }
        };

        vector<pii> not_yet;
        for(int i = 0; i < 5; ++i) {
            string s;
            cin >> s;
            if(s[0] == '*') {
                target = i - 1;
            }
            if(i == 0) continue;
            for(int j = 6 + i * 5; j <= 21; j += 5) {
                int a = i - 1, b = (j - 6) / 5;
                if(s[j] == '_') {
                    not_yet.emplace_back(a, b);
                    continue;
                }
                calc_scores(teams[a], teams[b], s[j] - '0', s[j + 2] - '0');
                goal[a][b] = s[j] - '0';
                goal[b][a] = s[j + 2] - '0';
            }
        }
        assert(not_yet.size() == 2);

        function<double(vector<team>, int, int)> order = [&](vector<team> teams, int rest, int prev_size) {
            const int n = teams.size();
            double res = 0;
            sort(rbegin(teams), rend(teams));
            for(int i = 0; i < n && rest > 0; ++i) {
                vector<team> concerned(1);
                concerned[0].id = teams[i].id;
                while(i + 1 < n && teams[i] == teams[i + 1]) {
                    team new_team;
                    new_team.id = teams[++i].id;
                    concerned.push_back(move(new_team));
                }
                const int m = concerned.size();

                if(m == prev_size) {
                    bool found = false;
                    for(auto& t : concerned) {
                        found |= t.id == target;
                    }

                    return found ? min((double)rest / m, 1.0) : 0.0;
                } else {
                    for(int ti = 0; ti < m; ++ti) {
                        for(int tj = ti + 1; tj < m; ++tj) {
                            const int i1 = concerned[ti].id, i2 = concerned[tj].id;
                            calc_scores(concerned[ti], concerned[tj], goal[i1][i2], goal[i2][i1]);
                        }
                    }
                    res += order(concerned, rest, m);
                }

                rest -= m;
            }

            return res;
        };

        double ans = 0;
        for(int i = 0; i <= 8; ++i) {
            for(int j = 0; j <= 8; ++j) {
                for(int k = 0; k <= 8; ++k) {
                    for(int l = 0; l <= 8; ++l) {
                        const int a = not_yet[0].first, b = not_yet[0].second;
                        const int c = not_yet[1].first, d = not_yet[1].second;
                        auto tmp_teams = teams;
                        calc_scores(tmp_teams[a], tmp_teams[b], i, j);
                        calc_scores(tmp_teams[c], tmp_teams[d], k, l);
                        goal[a][b] = i, goal[b][a] = j;
                        goal[c][d] = k, goal[d][c] = l;
                        ans += order(tmp_teams, 2, 4) * possibility[i] * possibility[j] * possibility[k] * possibility[l];
                    }
                }
            }
        }

        cout << ans << endl;
    }
}
