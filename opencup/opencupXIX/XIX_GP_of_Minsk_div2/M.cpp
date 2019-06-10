#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int T; cin >> T;
    map<string, int> atk, def;
    for(int i = 0; i < T; ++i) {
        string s; cin >> s;
        int a, d; cin >> d >> a;
        atk[s] = a;
        def[s] = d;
    }

    int V, E; cin >> V;
    ll tot_def = 0, tot_atk = 0;
    for(int i = 0; i < V; ++i) {
        string s; int c; cin >> s >> c;
        tot_def += def[s] * c;
    }
    cin >> E;
    for(int i = 0; i < E; ++i) {
        string s; int c; cin >> s >> c;
        tot_atk += atk[s] * c;
    }

    if(tot_def > tot_atk) {
        cout << "Victory" << endl;
    } else if (tot_def < tot_atk) {
        cout << "Epic fail" << endl;
    } else {
        cout << "Draw" << endl;
    }
}