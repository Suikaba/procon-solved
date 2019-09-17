#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while(cin >> n) {
        // mirror, dir
        vector<vector<vector<string>>> v(2, vector<vector<string>>(4, vector<string>(n, string(n, ' '))));
        for(auto& x : v[0][0]) cin >> x;
        cin.ignore();
        vector<char> cs;
        {
            string line; getline(cin, line);
            for(int i = 0; i < (int)line.size(); i += 2) {
                if(line[i] == '/') {
                    cs.push_back('|');
                    cs.push_back('<');
                    cs.push_back('<');
                    cs.push_back('<');
                } else if(line[i] == '\\') {
                    cs.push_back('|');
                    cs.push_back('<');
                } else if(line[i] == '-') {
                    cs.push_back('|');
                    cs.push_back('<');
                    cs.push_back('<');
                } else if(line[i] == '>') {
                    cs.push_back('<');
                    cs.push_back('<');
                    cs.push_back('<');
                } else {
                    cs.push_back(line[i]);
                }
            }
        }
        auto rotate = [] (char c, char com) {
            if(com == '|') {
                switch(c) {
                case '<': return '>';
                case '>': return '<';
                case '/': return '\\';
                case '\\': return '/';
                default: return c;
                }
            } else { // <
                switch(c) {
                case '/': return '\\';
                case '\\': return '/';
                case 'v': return '>';
                case '>': return '^';
                case '^': return '<';
                case '<': return 'v';
                case '|': return '-';
                case '-': return '|';
                default: return c;
                }
            }
        };

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                v[1][0][i][j] = rotate(v[0][0][i][n - j - 1], '|');
            }
        }
        for(int i = 0; i < 2; ++i) {
            for(int j = 1; j < 4; ++j) {
                for(int k = 0; k < n; ++k) {
                    for(int l = 0; l < n; ++l) {
                        v[i][j][k][l] = rotate(v[i][j - 1][l][n - k - 1], '<');
                    }
                }
            }
        }

        vector<vector<int>> idx(2, {0, 1, 2, 3});
        for(auto c : cs) {
            if(c == '|') {
                swap(idx[0], idx[1]);
                swap(v[0], v[1]);
            } else {
                for(auto& i : idx[0]) i = (i + 1) % 4;
                for(auto& i : idx[1]) i = (i + 3) % 4;
            }
        }

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                cout << v[0][idx[0][0]][i][j];
            }
            cout << '\n';
        }
    }
}
