#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> p(n);
    for(int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    int cnt = 0;
    bool two = false;
    for(int i = 0; i < n; ++i) {
        if(p[i] == i) {
            cnt += 1;
        } else if(p[p[i]] == i) {
            two = true;
        }
    }
    if(two) {
        cnt += 2;
    } else if(cnt != n) {
        cnt += 1;
    }

    cout << cnt << endl;
}
