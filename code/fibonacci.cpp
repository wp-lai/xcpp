#include <cassert>
#include <iostream>

unsigned fib(unsigned n) {
    if (n < 2) return n;

    int i = 0, j = 1;  // fib(0) = 0, fib(1) = 1
    while (--n > 0) {
        j = i + j;
        i = j - i;
    }
    return j;
}

int main() {
    assert(fib(46) == 1836311903);
    assert(fib(10) == 55);
}
