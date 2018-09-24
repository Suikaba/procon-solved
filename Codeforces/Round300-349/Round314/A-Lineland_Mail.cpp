#include <bits/stdc++.h>
using namespace std;

constexpr int inf = std::numeric_limits<int>::max();

int main() {
    int n; cin >> n;
    vector<int> x(n);
    for(int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    for(int i = 0; i < n; ++i) {
        int mini = min(i != 0 ? x[i] - x[i - 1] : inf, i != n - 1 ? x[i + 1] - x[i] : inf);
        int maxi = max(x[i] - x[0], x.back() - x[i]);
        cout << mini << ' ' << maxi << endl;
    }
}
