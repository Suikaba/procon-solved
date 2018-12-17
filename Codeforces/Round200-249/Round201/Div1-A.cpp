#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    int g = 0;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        g = __gcd(a[i], g);
    }
    const int num = *max_element(begin(a), end(a)) / g;
    if((num - n) & 1) {
        cout << "Alice" << endl;
    } else {
        cout << "Bob" << endl;
    }
}
