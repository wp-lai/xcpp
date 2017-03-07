/*
 * LightHouse Problem
 * Reference link:
 *  + https://dsa.cs.tsinghua.edu.cn/oj/problem.shtml?id=1144
 *  + http://www.szeju.com/index.php/other/10174237.html
 */
#include <iostream>
using namespace std;

struct Point {
    long x;
    long y;
};

template <typename T, class Compare>
long merge(T* arr, int mid, int lo, int hi, Compare cmp) {
    long inv = 0;

    T* A = arr + lo;
    int lc = hi - mid;
    T* C = arr + mid;

    int lb = mid - lo;
    T* B = new T[lb];
    for (int i = 0; i < lb; ++i) B[i] = A[i];

    for (int i = 0, j = 0, k = 0; i < lb;) {
        if (j < lc && cmp(C[j], B[i])) {
            inv += lb - i;
            A[k++] = C[j++];
        } else {
            A[k++] = B[i++];
        }
    }

    delete[] B;
    return inv;
}

template <typename T, class Compare>
long mergeSort(T* arr, int lo, int hi, Compare cmp) {
    // returen inversion number
    if (hi - lo < 2) return 0;

    long mid = (lo + hi) / 2;
    long l = mergeSort(arr, lo, mid, cmp);
    long r = mergeSort(arr, mid, hi, cmp);
    long m = merge(arr, mid, lo, hi, cmp);
    return l + r + m;
}

int main() {
    // read data length
    int n;
    cin >> n;

    // read data
    Point* arr = new Point[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].x >> arr[i].y;
    }

    // sort by x
    mergeSort(arr, 0, n,
              [](const Point& a, const Point& b) { return a.x < b.x; });

    // sort by y, and print #LightHouse = #Points - #Inversions
    long inv = mergeSort(
        arr, 0, n, [](const Point& a, const Point& b) { return a.y < b.y; });
    cout << n * (n - 1) / 2 - inv << endl;

    delete[] arr;
}
