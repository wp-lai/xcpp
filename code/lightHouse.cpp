/*
 * LightHouse Problem
 * Reference link:
 *  + https://dsa.cs.tsinghua.edu.cn/oj/problem.shtml?id=1144
 *  + http://www.szeju.com/index.php/other/10174237.html
 */
#include <iostream>
#include <utility>
#include <ctime>
using namespace std;

struct Point {
    long x;
    long y;
};

void qsort(Point* arr, int lo, int hi) {
    srand(time(0));

    if (hi - lo < 2) return;

    int key = lo + rand() % (hi - lo);
    long xKey = arr[key].x;
    swap(arr[lo], arr[key]);

    int i = lo + 1;
    for (int j = lo + 1; j < hi; ++j) {
        if (arr[j].x < xKey) {
            swap(arr[i++], arr[j]);
        }
    }
    swap(arr[--i], arr[lo]);
    qsort(arr, lo, i);
    qsort(arr, i + 1, hi);
}

template <typename T, class Compare>
long invBetween(T* arr, int mid, int lo, int hi, Compare cmp) {
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
long invInside(T* arr, int lo, int hi, Compare cmp) {
    // returen inversion number
    if (hi - lo < 2) return 0;

    int mid = (lo + hi) / 2;
    long l = invInside(arr, lo, mid, cmp);
    long r = invInside(arr, mid, hi, cmp);
    long m = invBetween(arr, mid, lo, hi, cmp);
    return l + r + m;
}

class cmpX {
public:
    bool operator()(const Point& a, const Point& b) { return a.x < b.x; }
};

class cmpY {
public:
    bool operator()(const Point& a, const Point& b) { return a.y < b.y; }
};

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
    qsort(arr, 0, n);

    // sort by y, and print #LightHouse = #Points - #Inversions
    long inv = invInside(arr, 0, n, cmpY());
    cout << n * (n - 1) / 2 - inv << endl;

    delete[] arr;
}
