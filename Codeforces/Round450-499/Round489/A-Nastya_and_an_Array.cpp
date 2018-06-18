#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<int> a;
    for(int i = 0; i < n; ++i) {
        int b; cin >> b;
        if(b == 0) continue;
        a.insert(b);
    }
    cout << a.size() << endl;
}
