
#include <iostream>

#pragma once

using namespace std;

class Array{
private:
    int *array_;
    int len_;

public:

    Array(int size = 1, int key = 1, int range = 10);
    Array(const int*, int);

    Array(Array& );
    ~Array();

    Array& operator=(Array);
    int& operator[](int);
    bool Test() const;
    bool operator==(Array&) const;
    Array operator+(Array&);

    void Shell_sort();
    void Shaker_sort();
    void Hoar_sort(int , int );
    void Bit_sort(int ,int ,int );

    friend istream& operator>> (istream&, Array&);
    friend ostream& operator<< (ostream&, Array&);
};