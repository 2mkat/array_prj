#include <iostream>
#include "array_l.h"
#include "array_l.cpp"

int main() {

    int *arr = new int[9] {2,3,1,5,4,6,9,8,7};

    Array c1(arr, 9);
    c1.Bit_sort(2,6,2);
    Array c2(4,2,10);
    cout << c1 << '\n';
   // c1 + c2;

    return 0;
}
