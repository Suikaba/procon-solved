#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    set<string> s;
    for(int i = 0; i < n; ++i) {
        string t;
        cin >> t;
        sort(begin(t), end(t));
        t.erase(unique(begin(t), end(t)), end(t));
        s.insert(t);
    }
    cout << s.size() << endl;
}
