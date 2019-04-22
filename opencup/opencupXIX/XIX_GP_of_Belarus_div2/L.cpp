#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int inv = 0, ok = 0;
    for(int i = 0; i + 1 < n; ++i) {
        if(a[i] > a[i + 1]) inv += 1;
        else                ok += 1;
    }

    if(inv == 0) {
        cout << "Bob" << endl;
    } else {
        cout << (n & 1 ? "Alice" : "Bob") << endl;
    }
}
