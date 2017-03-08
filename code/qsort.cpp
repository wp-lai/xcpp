#include <iostream>
#include <utility>
using namespace std;

template <typename T>
void qsort(T* arr, int lo, int hi) {
    if (hi - lo < 2) return;

    int atKey = lo + rand() % (hi - lo);
    int key = arr[atKey];
    swap(arr[lo], arr[atKey]);

    int i = lo + 1;
    for (int j = i; j < hi; ++j) {
        if (arr[j] < key) swap(arr[j], arr[i++]);
    }
    swap(arr[lo], arr[i - 1]);

    qsort(arr, lo, i - 1);
    qsort(arr, i, hi);
}

template <typename T>
void printArr(T* arr, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));
    int arr[5] = {rand() % 100, rand() % 100, rand() % 100, rand() % 100,
                  rand() % 100};
    cout << "before sort: ";
    printArr(arr, 5);

    qsort(arr, 0, 5);
    cout << "after  sort: ";
    printArr(arr, 5);
}
