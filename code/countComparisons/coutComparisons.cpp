/*
 * Compute the total number of comparisons used to sort the given input file by
 * QuickSort, always use the first element of the array as the pivot element
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::swap;

int count_comps(vector<int>&);
int count_comps(vector<int>&, int start, int end);
int partition(vector<int>&, int left_pos, int right_pos, int pivot_pos);

int main() {
    // read data
    ifstream ifs("QuickSort.txt");
    vector<int> vec;
    int element;
    while (ifs >> element) vec.push_back(element);

    int n_comps = count_comps(vec);
    cout << "There are " << n_comps << " comparisons used by QuickSort" << endl;
}

int count_comps(vector<int>& vec) { return count_comps(vec, 0, vec.size() - 1); }

int count_comps(vector<int>& vec, int l, int r) {
    // base case
    if (l >= r) return 0;

    int mid = partition(vec, l, r, l); // always use the first element as pivot
    int l_comps = count_comps(vec, l, mid - 1);
    int r_comps = count_comps(vec, mid + 1, r);
    return l_comps + r_comps + (r - l);
}

int partition(vector<int>& vec, int left_pos, int right_pos, int pivot_pos) {
    int pivot = vec[pivot_pos];
    if (pivot_pos != left_pos) swap(vec[left_pos], vec[pivot_pos]);
    int i = left_pos + 1;
    for (int j = i; j <= right_pos; j++) {
        if (vec[j] < pivot) {
            swap(vec[j], vec[i]);
            i++;
        }
    }
    swap(vec[left_pos], vec[i - 1]);
    return i - 1;
}
