#include <bits/stdc++.h>
using namespace std;

int main() {
    string s1, s2, s3, s4;
    while(cin >> s1 >> s2 >> s3 >> s4, s1 != "0000" && s2 != "0000" && s3 != "0000" && s4 != "0000") {
        const string s = s1 + s2 + s3 + s4;
        int sum = 0;
        for(int i = 0; i < 16; ++i) {
            if(i % 2 == 0) {
                int t = (s[i] - '0') * 2;
                if(t >= 10) t -= 9;
                sum += t;
            } else {
                sum += (s[i] - '0');
            }
        }
        if(sum % 10 == 0) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}