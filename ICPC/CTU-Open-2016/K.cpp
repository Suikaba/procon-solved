#include <bits/stdc++.h>
using namespace std;

int main() {
    map<string, char> m = {
        {"", ' '},
        {".-", 'A'},
        {"-...", 'B'},
        {"-.-.", 'C'},
        {"-..", 'D'},
        {".", 'E'},
        {"..-.", 'F'},
        {"--.", 'G'},
        {"....", 'H'},
        {"..", 'I'},
        {".---", 'J'},
        {"-.-", 'K'},
        {".-..", 'L'},
        {"--", 'M'},
        {"-.", 'N'},
        {"---", 'O'},
        {".--.", 'P'},
        {"--.-", 'Q'},
        {".-.", 'R'},
        {"...", 'S'},
        {"-", 'T'},
        {"..-", 'U'},
        {"...-", 'V'},
        {".--", 'W'},
        {"-..-", 'X'},
        {"-.--", 'Y'},
        {"--..", 'Z'}
    };
    string s;
    while(cin >> s) {
        string cur, ans;
        for(auto c : s) {
            if(c == '/') {
                ans += m[cur];
                cur = "";
            } else {
                cur += c;
            }
        }
        ans += m[cur];
        cout << ans << endl;
    }
}