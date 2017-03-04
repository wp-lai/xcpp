/*
 * Longest common subsequence problem
 */
#include <cassert>
#include <string>
#include <vector>
using std::vector;
using std::string;

class LCS {
public:
    LCS(string s1, string s2);
    int length() const { return table[n1][n2]; }
    string getLCS() const { return lcs; }

private:
    string s1;
    string s2;
    size_t n1;
    size_t n2;
    string lcs;                 // longest common sequence
    vector<vector<int>> table;  // path table

    void buildPath();
    string backtrace(size_t i, size_t j) const;
};

int main() {
    LCS a("program", "algorithm");
    assert(a.length() == 3);
    assert(a.getLCS() == "grm");

    LCS b("computer", "cute");
    assert(b.length() == 4);
    assert(b.getLCS() == "cute");
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

string LCS::backtrace(size_t i, size_t j) const {
    if (i == 0 || j == 0) return string();

    if (s1[i - 1] == s2[j - 1]) return backtrace(i - 1, j - 1) + s1[i - 1];

    if (table[i - 1][j] > table[i][j - 1])
        return backtrace(i - 1, j);
    else
        return backtrace(i, j - 1);
}
