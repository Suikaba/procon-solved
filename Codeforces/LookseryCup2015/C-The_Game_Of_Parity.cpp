#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> cnt(2);
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        cnt[a & 1] += 1;
    }
    if(k == n) {
        cout << (cnt[1] & 1 ? "Stannis" : "Daenerys") << endl;
    } else {
        if((n - k) & 1) {
            cout << (cnt[1] <= (n - k) / 2 || (cnt[0] <= (n - k) / 2 && k % 2 == 0) ? "Daenerys" : "Stannis") << endl;
        } else {
            cout << (cnt[0] <= (n - k) / 2 && (k & 1) ? "Stannis" : "Daenerys") << endl;
        }
    }
}
