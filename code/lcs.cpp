/*
 * compute the length of longest common substring
 */
#include <cassert>
#include <string>
#include <vector>
using std::vector;
using std::string;

int lcs(string str1, string str2) {
    int n = str1.size();
    int m = str2.size();
    if (n == 0 || m == 0) return 0;

    vector<vector<int>> path(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            if (str1[i - 1] == str2[j - 1])
                path[i][j] = path[i - 1][j - 1] + 1;
            else
                path[i][j] = (path[i - 1][j] > path[i][j - 1]) ? path[i - 1][j]
                                                               : path[i][j - 1];
        }
    }
    return path[n][m];
}

int main() {
    assert(lcs("program", "algorithm") == 3);
    assert(lcs("computer", "cute") == 4);
}

