#include <bits/stdc++.h>
using namespace std;

int main() {
    int w, h; cin >> w >> h;
    vector<int> a(w), b(h);
    for(auto& x : a) cin >> x;
    for(auto& x : b) cin >> x;

    for(auto x : a) {
        sort(begin(b), end(b), greater<>{});
        if(x == 0) continue;
        if(x > (int)b.size() || *min_element(begin(b), begin(b) + x) == 0) {
            cout << 0 << endl;
            return 0;
        }
        for(int j = 0; j < x; ++j) {
            b[j] -= 1;
        }
    }

    cout << (*max_element(begin(b), end(b)) == 0) << endl;
}
