#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll to_int(string s) {
    const int n = s.size();
    ll res = 0;
    for(int i = 0; i < n; ++i) {
        if(s[i] == ',') continue;
        res *= 10;
        res += s[i] - '0';
    }
    return res;
}

string str_of_int(ll n) {
    auto s = to_string(abs(n));
    reverse(begin(s), end(s));
    string res;
    for(int i = 0; i < (int)s.size(); ++i) {
        if(i % 3 == 0 && i != 0) {
            res += ',';
        }
        res += s[i];
    }
    reverse(begin(res), end(res));
    if(n < 0) res = "-" + res;
    if(n > 0) res = "+" + res;
    return res;
}

const string mstr[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September",
"October", "November", "December"};

void print2(ll m, ll c) {
    cout << str_of_int(m) << " from " << c << " " << (c > 1 ? "invoices." : "invoice.") << endl;
}

int main() {
    int n; cin >> n;
    map<int, ll> month, cnt;
    ll year = 0;
    for(int i = 0; i < n; ++i) {
        int dd, mm, yy; scanf("%d.%d.%d", &dd, &mm, &yy); // yy not used
        string in_out; cin >> in_out;
        {
            string s;
            while(cin >> s, s.back() != '.');
        }
        string ms; cin >> ms;
        const ll money = to_int(ms);
        if(in_out == "income") {
            month[mm] += money;
            year += money;
        } else {
            month[mm] -= money;
            year -= money;
        }
        cnt[mm] += 1;
    }

    for(auto const& p : month) {
        cout << "Month: " << mstr[p.first] << endl;
        const int c = cnt[p.first];
        print2(p.second, c);
        cout << endl;
    }
    cout << "Year" << endl;
    print2(year, n);
}