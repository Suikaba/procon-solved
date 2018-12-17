#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(begin(a), end(a));
    swap(a[0], a.back());
    for(int i = 0; i < n; ++i) {
        cout << a[i] << " \n"[i + 1 == n];
    }
}
