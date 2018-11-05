#include <bits/stdc++.h>
using namespace std;

int main() {
    auto f = [] (int n) {
        int res = 0;
        while(n > 0) {
            res += (n % 10) * (n % 10);
            n /= 10;
        }
        return res;
    };
    vector<int> dp(10000, -1);
    function<int(int)> solve = [&] (int x) {
        if(dp[x] != -1) return dp[x];
        if(x == 1) return dp[x] = 1;
        dp[x] = 0;
        return dp[x] = solve(f(x));
    };

    int n;
    while(cin >> n) {
        n = f(f(n));
        if(solve(n) == 1) {
            cout << "HAPPY" << endl;
        } else {
            cout << "UNHAPPY" << endl;
        }
    }
}
