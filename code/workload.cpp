/*
 * 有n份工作要分配给n个人来完成，每个人完成一份。
 * 第i个人完成第k份工作所用的时间为一个正整数t[i][k]，其中1 ≤ i, k ≤ n。
 * 试确定一个分配方案，使得完成这n份工作的时间总和最小。
 */
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class Workload {
public:
    Workload(int n);
    void arrange();
    void print_best_arrange() const {
        for (auto& e : best_arrange) {
            cout << "task #" << e.second + 1 << " is assigned to "
                 << e.first + 1 << endl;
        }
    }
    int get_best_cost() const { return best_cost; }

    friend istream& operator>>(istream& is, Workload& wl);

private:
    int dimension;
    vector<vector<int>> cost_matrix;
    vector<bool> visited;

    vector<pair<int, int>> best_arrange;
    vector<pair<int, int>> temp_arrange;
    int best_cost = -1;

    void assign(int i, int cost);
};

int main() {
    int n;
    cin >> n;
    Workload wl(n);
    cin >> wl;
    wl.arrange();
    cout << wl.get_best_cost() << endl;
    wl.print_best_arrange();
}

Workload::Workload(int n)
    : dimension{n},
      cost_matrix{vector<vector<int>>(n, vector<int>(n, 0))},
      visited{vector<bool>(n, false)} {}

istream& operator>>(istream& is, Workload& wl) {
    for (int i = 0; i < wl.dimension; ++i) {
        for (int j = 0; j < wl.dimension; ++j) {
            is >> wl.cost_matrix[i][j];
        }
    }
    return is;
}

void Workload::arrange() {
    best_cost = 0;
    for (int i = 0; i < dimension; ++i) {
        best_cost += cost_matrix[i][i];
    }

    assign(0, 0);
}

void Workload::assign(int i, int cost) {
    if (i >= dimension) {
        if (cost < best_cost) {
            best_arrange = temp_arrange;
            best_cost = cost;
        }
        return;
    }

    if (cost > best_cost) return;

    for (int j = 0; j < dimension; ++j) {
        if (!visited[j]) {
            visited[j] = true;
            temp_arrange.push_back(make_pair(i, j));
            assign(i + 1, cost + cost_matrix[i][j]);
            temp_arrange.pop_back();
            visited[j] = false;
        }
    }
}
