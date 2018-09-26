// http://codeforces.com/contest/584/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool is_prime(int n) {
    if(n == 0 || n == 1) return false;
    for(int i = 2; i * i <= n; ++i) {
        if(n % i == 0) return false;
    }
    return true;
}

vector<int> sol2(int n) {
    for(int i = 2; i <= n; ++i) {
        int j = n - i;
        if(j == 0) {
            if(is_prime(i)) return {i};
        } else {
            if(is_prime(i) && is_prime(j)) return {i, j};
        }
    }
    return vector<int>();
}

int main() {
    int n; cin >> n;
    if(is_prime(n)) {
        cout << 1 << endl;
        cout << n << endl;
        return 0;
    }
    vector<int> ans;
    for(int i = n - 2; i >= 2; --i) {
        if(!is_prime(i)) continue;
        auto tmp = sol2(n - i);
        if(!tmp.empty()) {
            ans.push_back(i);
            for(auto x : tmp) ans.push_back(x);
            break;
        }
    }
    cout << ans.size() << endl;
    sort(begin(ans), end(ans));
    for(int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
    }
}
