#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

long long merge_sort_and_count_inv(const vector<int>&);
long long merge_sort_and_count_inv(const vector<int>& numbers, vector<int>& tmp,
                                   int left, int right);
long long merge(vector<int>& tmp, int left_start, int right_start,
                int right_end);

int main() {
    int n = 100000;
    vector<int> numbers;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        numbers.push_back(x);
    }
    long long result = merge_sort_and_count_inv(numbers);
    cout << "There are " << result << " inversions" << endl;
}

long long merge_sort_and_count_inv(const vector<int>& numbers) {
    vector<int> tmp {numbers};
    return merge_sort_and_count_inv(numbers, tmp, 0, numbers.size() - 1);
}

long long merge_sort_and_count_inv(const vector<int>& numbers, vector<int>& tmp,
                                   int left, int right) {
    if (left < right) {
        int center = left +  (right - left) / 2;
        long long left_inv =
            merge_sort_and_count_inv(numbers, tmp, left, center);
        long long right_inv =
            merge_sort_and_count_inv(numbers, tmp, center + 1, right);
        long long merge_inv = merge(tmp, left, center + 1, right);
        return left_inv + right_inv + merge_inv;
    }
    return 0;
}

long long merge(vector<int>& tmp, int left_start, int right_start,
                int right_end) {
    int pos = 0;
    int invs = 0;
    int num_elements = right_end - left_start + 1;
    vector<int> merged(num_elements);

    int left_end = right_start - 1;
    while (left_start <= left_end && right_start <= right_end) {
        if (tmp[left_start] <= tmp[right_start]) {
            merged[pos++] = tmp[left_start++];
        } else {
            merged[pos++] = tmp[right_start++];
            invs += left_end - left_start + 1;
        }
    }

    while (left_start <= left_end) {
        merged[pos++] = tmp[left_start++];
    }

    while (right_start <= right_end) {
        merged[pos++] = tmp[right_start++];
    }

    // copy back to tmp
    while (--pos >= 0) {
        tmp[right_end--] = merged[pos];
    }

    return invs;
}
