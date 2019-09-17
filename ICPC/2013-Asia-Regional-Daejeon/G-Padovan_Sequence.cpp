#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    vector<ll> v = {1, 1, 1, 2, 2};
    for(int i = v.size(); i < 101; ++i) {
        v.push_back(v.back() + v[v.size() - 5]);
    }
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        cout << v[n - 1] << endl;
    }
}
