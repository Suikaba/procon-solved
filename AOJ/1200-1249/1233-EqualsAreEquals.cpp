#include <bits/stdc++.h>
using namespace std;

// Equals are Equals
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1233

// 目標 -> 40min, 実際 -> 90min
// 反省
// getline の仕様を確認するのに手間取った．(Win だと \r が残ってたりして辛かった)
// 空白のスキップを書き忘れているところがあった．末尾のごみ処理は次にやつに投げずに自己完結すべきだった．
// 項をまとめる時，係数を含めて等号判定する（これは最後の時）のと，係数を含めずに（これは途中）判定する2つがあることを失念．
// ちょっと複雑なテストケースを作れば気づいていたはずなので，サンプルを作るのを怠った自分の責任．

struct term {
    int coff;
    vector<int> deg;

    term() : coff(1), deg(26, 0) {}

    bool operator<(const term& other) const {
        return deg < other.deg;
    }
    bool operator==(const term& other) const {
        return coff == other.coff && deg == other.deg;
    }
};

struct expression {
    void add_term(term new_term) {
        for(auto& t : terms) {
            if(t.deg == new_term.deg) {
                t.coff += new_term.coff;
                return;
            }
        }
        terms.push_back(move(new_term));
        sort(begin(terms), end(terms));
        clean_up();
    }

    void add_expr(expression e) {
        for(auto& t : e.terms) {
            add_term(t);
        }
        clean_up();
    }

    expression operator-() const {
        expression res;
        res.terms = terms;
        for(auto& t : res.terms) {
            t.coff = -t.coff;
        }
        return res;
    }

    bool operator==(expression const& other) const {
        return terms == other.terms;
    }

    void clean_up() {
        terms.erase(remove_if(begin(terms), end(terms),
                              [](const auto& t1) {
                                  return t1.coff == 0;
                              }),
                    end(terms));
    }

    void debug_print() const {
        cout << "sz: " << terms.size() << endl;
        for(auto& t : terms) {
            cout << "coff: " << t.coff << " deg: ";
            for(int i = 0; i < 26; ++i) {
                cout << t.deg[i] << ' ';
            }
            cout << endl;
        }
    }

    vector<term> terms;
};

term operator*(term a, term const& rhs) {
    a.coff *= rhs.coff;
    for(int i = 0; i < 26; ++i) {
        a.deg[i] += rhs.deg[i];
    }
    return a;
}

expression operator*(expression const& lhs, expression const& rhs) {
    expression res;
    for(auto const& t1 : lhs.terms) {
        for(auto const& t2 : rhs.terms) {
            res.add_term(t1 * t2);
        }
    }
    return res;
}


expression parse_expr(string const& s, int& p);
expression parse_term(string const& s, int& p);
expression parse_factor(string const& s, int& p);
void skip_sp(string const& s, int& p);
int number(string const& s, int& p);

expression parse_expr(string const& s, int& p) {
    auto e = parse_term(s, p);
    skip_sp(s, p);
    while(p < (int)s.size() && (s[p] == '+' || s[p] == '-')) {
        const char op = s[p++];
        skip_sp(s, p);
        auto t2 = parse_term(s, p);
        if(op == '-') {
            t2 = -t2;
        }
        e.add_expr(t2);
        skip_sp(s, p);
    }
    return e;
}

expression parse_term(string const& s, int& p) {
    auto e = parse_factor(s, p);
    skip_sp(s, p);
    while(p < (int)s.size() && s[p] != '+' && s[p] != '-' && s[p] != ')') {
        auto f = parse_factor(s, p);
        e = e * f;
    }
    return e;
}

expression parse_factor(string const& s, int& p) {
    expression res;
    skip_sp(s, p);

    if(s[p] == '(') {
        skip_sp(s, ++p);
        auto e = parse_expr(s, p);
        res = e;
        skip_sp(s, p);
        assert(s[p] == ')');
        skip_sp(s, ++p); // )
        if(p < (int)s.size() && s[p] == '^') {
            skip_sp(s, ++p);
            int d = number(s, p); // todo: only "^ (number)" ?
            for(int i = 0; i < d - 1; ++i) {
                res = res * e;
            }
        }
        skip_sp(s, p);
    } else if(isdigit(s[p])) {
        const int n = number(s, p);
        term t;
        t.coff = n;
        res.add_term(t);
        skip_sp(s, p);
    } else if(isalpha(s[p])) {
        const int idx = s[p++] - 'a';
        term t;
        t.deg[idx] = 1;
        skip_sp(s, p);
        if(p < (int)s.size() && s[p] == '^') {
            skip_sp(s, ++p);
            t.deg[idx] *= number(s, p);
            skip_sp(s, p);
        }
        res.add_term(t);
    } else {
        cout << "str: " << s << "  p: " << p << " s[p]: " << s[p] << endl;
        assert(false);
    }

    return res;
}

int number(string const& s, int& p) {
    assert(isdigit(s[p]));
    int res = 0;
    while(p < (int)s.size() && isdigit(s[p])) {
        res *= 10;
        res += s[p++] - '0';
    }
    return res;
}

void skip_sp(string const& s, int& p) {
    while(p < (int)s.size() && s[p] == ' ') {
        p++;
    }
}

expression parse(string const& s) {
    int p = 0;
    return parse_expr(s, p);
}


int main() {
    string s;
    while(getline(cin, s), s[0] != '.') {
        if(s.back() == '\r') s.pop_back();
        const auto target = parse(s);
        string t;
        while(getline(cin, t), t[0] != '.') {
            if(t.back() == '\r') t.pop_back();
            const auto ss = parse(t);
            if(target == ss) {
                cout << "yes" << endl;
            } else {
                cout << "no" << endl;
            }
        }
        cout << "." << endl;
    }
}
