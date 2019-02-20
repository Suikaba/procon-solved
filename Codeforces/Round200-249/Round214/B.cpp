#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    vector<int> sum(k);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        sum[i % k] += a[i];
    }

    cout << (min_element(begin(sum), end(sum)) - begin(sum)) + 1 << endl;
}
