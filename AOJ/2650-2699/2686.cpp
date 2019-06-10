#include <bits/stdc++.h>
using namespace std;

int grundy(vector<int> const& s, int a) {
    const int n = s.size();
    int x = 0;
    for(int i = 0; i < n; ++i) {
        x ^= s[i] % (a + 1);
    }
    return x;
}

int main() {
    int n, a, b; cin >> n >> a >> b;
    vector<int> s(n);
    for(int i = 0; i < n; ++i) {
        cin >> s[i];
    }

    const int max_v = *max_element(begin(s), end(s));
    bool ans = false;
    if(a == b) {
        ans = grundy(s, a) != 0;
    } else if(a > b) {
        ans = max_v > b || grundy(s, b) != 0;
    } else { // a < b
        int cnt = 0;
        for(int i = 0; i < n; ++i) {
            cnt += s[i] > a;
        }
        // cnt >= 2 => lose
        if(cnt == 0) {
            ans = grundy(s, a) != 0;
        } else if(cnt == 1) {
            const int m = max_v % (a + 1);
            const int g = grundy(s, a) ^ m;
            if(g <= a) {
                const int take = (m - g + a + 1) % (a + 1);
                ans = take != 0 && max_v - take <= a;
            }
        }
    }

    cout << (ans ? "Hanako" : "Jiro") << endl;
}
