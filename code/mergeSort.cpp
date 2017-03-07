#include <iostream>
using namespace std;

template <typename T>
void merge(T* arr, int mid, int lo, int hi) {
    T* A = arr + lo;
    int lc = hi - mid;
    T* C = arr + mid;

    int lb = mid - lo;
    T* B = new T[lb];
    for (int i = 0; i < lb; ++i) B[i] = A[i];

    for (int i = 0, j = 0, k = 0; i < lb;) {
        if (j < lc && C[j] < B[i]) {
            A[k++] = C[j++];
        } else {
            A[k++] = B[i++];
        }
    }

    delete[] B;
}

template <typename T>
void mergeSort(T* arr, int lo, int hi) {
    if (hi - lo < 2) return;

    int mid = (lo + hi) / 2;
    mergeSort(arr, lo, mid);
    mergeSort(arr, mid, hi);
    merge(arr, mid, lo, hi);
}

template <typename T>
void printArr(T* arr, int n) {
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[8] = {9, 8, 6, 12, 8, 7, 5, 3};
    cout << "before sort: ";
    printArr(arr, 8);
    cout << "after  sort: ";
    mergeSort(arr, 0, 8);
    printArr(arr, 8);
}
