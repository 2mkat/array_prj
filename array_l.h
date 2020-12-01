#pragma once

#include <iostream>

class Array{
private:
    int *array_;
    std::size_t len_;

public:

    Array(std::size_t size = 1, std::size_t key = 1, int range = 10);
    Array(const int*, std::size_t);

    Array(Array& );
    ~Array();

    Array& operator=(Array);
    int& operator[](std::size_t );
    bool Test() const;
    bool operator==(Array&) const;
    Array operator+(Array&);

    void Shell_sort();
    void Shaker_sort();
    void Hoar_sort(int , int );
    void Bit_sort(int ,int ,int );

    friend std::istream& operator>> (std::istream&, Array&);
    friend std::ostream& operator<< (std::ostream&, Array&);
};
