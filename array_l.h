#pragma once

#include <iostream>

class Array{
private:
    int *array_;
    std::size_t len_;

public:

    Array(std::size_t , std::size_t, int);
    Array(const int*, std::size_t);
    explicit Array(std::size_t len = 0);

    Array(const Array& );
    ~Array();

    Array& operator=(const Array& );
    int& operator[](std::size_t );
    bool Test() const;
    bool operator==(const Array&) const;
    Array operator+(const Array&);
    size_t get_len() const;
    size_t get_bit() const;

    void Shell_sort();
    void Shaker_sort();
    void Hoar_sort(int , int );
    void Bit_sort(int ,int ,int );
    void Pyramidal_sort();

    friend std::istream& operator>> (std::istream&, Array&);
    friend std::ostream& operator<< (std::ostream&, Array&);
};
