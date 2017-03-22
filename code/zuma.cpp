/*
 * 描述
 * 祖玛是一款曾经风靡全球的游戏，其玩法是：在一条轨道上初始排列着若干个彩色珠子
 * 其中任意三个相邻的珠子不会完全同色。此后，你可以发射珠子到轨道上并加入原有序
 * 列中。一旦有三个或更多同色的珠子变成相邻，它们就会立即消失。这类消除现象可能
 * 会连锁式发生，其间你将暂时不能发射珠子。
 *
 * 开发商最近准备为玩家写一个游戏过程的回放工具。他们已经在游戏内完成了过程记录
 * 的功能，而回放功能的实现则委托你来完成。
 *
 * 游戏过程的记录中，首先是轨道上初始的珠子序列，然后是玩家接下来所做的一系列操
 * 作。你的任务是，在各次操作之后及时计算出新的珠子序列。
 *
 * 输入
 * 第一行是一个由大写字母'A'~'Z'组成的字符串，表示轨道上初始的珠子序列，不同的
 * 字母表示不同的颜色。
 *
 * 第二行是一个数字n，表示整个回放过程共有n次操作。
 *
 * 接下来的n行依次对应于各次操作。每次操作由一个数字k和一个大写字母Σ描述，以空
 * 格分隔。其中，Σ为新珠子的颜色。若插入前共有m颗珠子，则k ∈ [0, m]表示新珠子嵌
 * 入之后（尚未发生消除之前）在轨道上的位序。
 *
 * 输出
 * 输出共n行，依次给出各次操作（及可能随即发生的消除现象）之后轨道上的珠子序列
 *
 * 如果轨道上已没有珠子，则以“-”表示。
 *
 *
 * Example
 *
 * Input
 * ACCBA
 * 5
 * 1 B
 * 0 A
 * 2 B
 * 4 C
 * 0 A
 *
 * Output
 * ABCCBA
 * AABCCBA
 * AABBCCBA
 * -
 * A
 *
 */
#include <iostream>
#include <iterator>
#include <list>
using namespace std;

void vanish(list<char>& lst, list<char>::iterator pos) {
    // 检查 pos 位置的珠子是否要被消除
    if (pos == lst.end()) return;
    char value = *pos;

    // find furtherst pos on the left s.t. *pos == value
    auto left = pos;
    while (left != lst.begin() && *(--left) == value);
    if (*left != value) ++left;

    // find furtherst pos on the right s.t. *pos == value
    auto right = pos;
    while (right != lst.end() && *right == value) ++right;

    if (distance(left, right) < 3)
        return;
    else {
        pos = lst.erase(left, right);
        vanish(lst, pos);
    }
}

int main() {
    // build initial list
    list<char> lst;
    string input;
    getline(cin, input);
    for (char c : input) lst.push_back(c);

    // read data
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int inc;
        char c;
        cin >> inc >> c;

        auto pos = lst.begin();
        while (inc--) ++pos;

        pos = lst.insert(pos, c);
        vanish(lst, pos);

        // output state
        if (lst.empty())
            cout << '-' << endl;
        else {
            for (char x : lst) cout << x;
            cout << endl;
        }
    }
}
