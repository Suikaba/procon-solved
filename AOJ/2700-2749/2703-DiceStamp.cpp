#include <bits/stdc++.h>
using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2703

// 反省点
// すぐわかる嘘で投げてしまった（投げる前に落ちるケースすぐわかるでしょ
// 嘘に気がついた後のリカバリーが雑（WA生やしてるんだから，直後にいきなり違うの書き始めるのは良くない．ひと呼吸おいてから
// 間に合うと踏んで投げたけど，val[x][y] の二次元配列作って書いたほうが速い，本番ならTLと相談

using pii = pair<int, int>;

enum {
    LEFT, RIGHT, FRONT, BACK, DOWN, UP
};

class dice {
public:
    dice(vector<int> score) : score(score) { assert(score.size() == 6); }

    void roll(char dir) {
        assert(dir == 'L' || dir == 'R' || dir == 'B' || dir == 'F');
        vector<int> nscore = score;
        if(dir == 'L') {
            nscore[LEFT] = score[UP];
            nscore[UP] = score[RIGHT];
            nscore[RIGHT] = score[DOWN];
            nscore[DOWN] = score[LEFT];
        } else if(dir == 'R') {
            nscore[RIGHT] = score[UP];
            nscore[UP] = score[LEFT];
            nscore[LEFT] = score[DOWN];
            nscore[DOWN] = score[RIGHT];
        } else if(dir == 'F') {
            nscore[FRONT] = score[UP];
            nscore[UP] = score[BACK];
            nscore[BACK] = score[DOWN];
            nscore[DOWN] = score[FRONT];
        } else {
            nscore[BACK] = score[UP];
            nscore[UP] = score[FRONT];
            nscore[FRONT] = score[DOWN];
            nscore[DOWN] = score[BACK];
        }
        score = move(nscore);
    }

    int get_value(int dir) const {
        return score[dir];
    }

private:
    vector<int> score;
};

int main() {
    const string dirs = "LRFB";
    constexpr int dx[4] = {-1, 1, 0, 0};
    constexpr int dy[4] = {0, 0, -1, 1};
    int n;
    while(cin >> n, n) {
        // (x, y -> value);
        using traj = map<pii, int>;
        vector<traj> trajs;
        for(int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            vector<int> score(6);
            for(int j = 0; j < 6; ++j) {
                cin >> score[j];
            }
            string rot;
            cin >> rot;
            dice d(score);
            traj t;
            t[make_pair(x, y)] = d.get_value(DOWN);
            for(char to : rot) {
                int dir = dirs.find(to);
                x += dx[dir], y += dy[dir];
                d.roll(to);
                t[make_pair(x, y)] = d.get_value(DOWN);
            }
            trajs.push_back(move(t));
        }

        vector<int> dp(1 << n);
        for(int S = 0; S < (1 << n); ++S) {
            set<pii> used;
            for(int i = 0; i < n; ++i) {
                if(S & (1 << i)) {
                    for(auto& p : trajs[i]) {
                        used.insert(p.first);
                    }
                }
            }
            for(int i = 0; i < n; ++i) {
                if(S & (1 << i)) continue;
                map<pii, int> new_values;
                for(auto& p : trajs[i]) {
                    if(used.count(p.first)) continue;
                    new_values[p.first] = p.second;
                }
                int value = 0;
                for(auto& p : new_values) {
                    value += p.second;
                }
                dp[S | (1 << i)] = max(dp[S | (1 << i)], dp[S] + value);
            }
        }

        cout << dp.back() << endl;
    }
}
