#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

class StablePairsDiv1 {
public:
    vector <int> findMaxStablePairs(int n, int c, int k) {
        vector<vector<vector<int>>> dp(k + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, -1)));
        vector<vector<vector<pii>>> prev(k + 1, vector<vector<pii>>(n + 1, vector<pii>(n + 1, make_pair(-1, -1))));
        for(int x = 1; x <= n; ++x) {
            for(int y = x + 1; y <= n; ++y) {
                dp[1][x][y] = x + y;
            }
        }
        for(int i = 2; i <= k; ++i) {
            for(int pre_x = 1; pre_x <= n; ++pre_x) {
                for(int pre_y = pre_x + 1; pre_y <= n; ++pre_y) {
                    if(dp[i - 1][pre_x][pre_y] == -1) continue;
                    const int sum = pre_x + pre_y;
                    for(int nx = pre_y + 1; nx <= n; ++nx) {
                        const int ny = c + sum - nx;
                        if(ny <= 0 || nx >= ny || ny > n) continue;
                        if(dp[i][nx][ny] < dp[i - 1][pre_x][pre_y] + sum + c) {
                            dp[i][nx][ny] = dp[i - 1][pre_x][pre_y] + sum + c;
                            prev[i][nx][ny] = make_pair(pre_x, pre_y);
                        }
                    }
                }
            }
        }

        vector<int> ans;
        int x = -1, y = -1, ma = -1;
        for(int i = 0; i <= n; ++i) {
            for(int j = 0; j <= n; ++j) {
                if(ma < dp[k][i][j]) {
                    x = i, y = j;
                    ma = dp[k][i][j];
                }
            }
        }
        //cerr << "ma: " << ma << ' ' << x << ' ' << y << endl;
        if(ma == -1) {
            return vector<int>();
        }

        //cerr << "ok" << endl;
        for(int i = k; i > 0; --i) {
            ans.push_back(y), ans.push_back(x);
            auto p = prev[i][x][y];
            x = p.first, y = p.second;
            //cerr << i << ' ' <<  x << ' ' << y << endl;
        }
        //cerr << "ok" << endl;
        reverse(begin(ans), end(ans));

        return ans;
    }
};


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
