/*
 * Longest common subsequence problem
 */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::set;
using std::for_each;

class LCS {
public:
    LCS(string s1, string s2);
    int length() const { return table[n1][n2]; }
    const set<string>& getLcs() const { return lcs; }

private:
    string s1;
    string s2;
    size_t n1;
    size_t n2;
    set<string> lcs;            // longest common sequence
    vector<vector<int>> table;  // path table

    void buildPath();
    set<string> backtrace(size_t i, size_t j);  // return all lcs
};

int main(int argc, char* argv[]) {
    assert(argc == 3);
    cout << "string one : " << argv[1] << endl;
    cout << "string two : " << argv[2] << endl;

    LCS x(argv[1], argv[2]);
    cout << "length of lcs: " << x.length() << endl;
    set<string> ss = x.getLcs();
    cout << "all lcs: ";
    for (auto& e : ss) cout << e << " ";
    cout << endl;
}

LCS::LCS(string s1, string s2)
    : s1{s1},
      s2{s2},
      n1{s1.size()},
      n2{s2.size()},
      table{vector<vector<int>>(n1 + 1, vector<int>(n2 + 1, 0))} {
    buildPath();
    lcs = backtrace(n1, n2);
}

void LCS::buildPath() {
    for (size_t i = 1; i < n1 + 1; ++i) {
        for (size_t j = 1; j < n2 + 1; ++j) {
            if (s1[i - 1] == s2[j - 1])
                table[i][j] = table[i - 1][j - 1] + 1;
            else
                table[i][j] = (table[i - 1][j] > table[i][j - 1])
                                  ? table[i - 1][j]
                                  : table[i][j - 1];
        }
    }
}

set<string> LCS::backtrace(size_t i, size_t j) {
    if (i == 0 || j == 0) return set<string>({""});
    set<string> res;

    if (s1[i - 1] == s2[j - 1]) {
        set<string> old = backtrace(i - 1, j - 1);
        for (auto e : old) res.insert(e + s1[i - 1]);
        return res;
    }

    if (table[i - 1][j] >= table[i][j - 1]) {
        set<string> temp = backtrace(i - 1, j);
        res.insert(temp.begin(), temp.end());
    }
    if (table[i][j - 1] >= table[i - 1][j]) {
        set<string> temp = backtrace(i, j - 1);
        res.insert(temp.begin(), temp.end());
    }
    return res;
}
