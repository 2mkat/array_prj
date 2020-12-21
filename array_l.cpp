#include "array_l.h"

#include <iostream>
#include <ctime>
#include <algorithm>
#include <cmath>

Array::Array(std::size_t size, std::size_t key, int range){

    srand(time(NULL));

    len_ = size;
    array_ = new int[len_];

    if(key == 1){
        for(int i = 0; i < len_; ++i){
            array_[i] = rand() % range + 1;
        }
    }
    if(key == 2){
        for(int i = 0; i < len_; ++i){
            array_[i] = rand() % range + 1;
        }
        std::sort(array_, array_ + len_);
    }
    if(key == 3){
        for(int i = 0; i < len_; ++i){
            array_[i] = rand() % range + 1;
        }
        std::sort(array_, array_ + len_, [](int i, int j){return i > j;});
    }
}
Array::Array(const int *array, std::size_t size_array){

    array_ = new int[size_array];
    std::copy(array, array + size_array, array_);

    len_ = size_array;
}
Array::Array(size_t len){
    len_ = len;
    array_ = new int[len_];
    std::fill(array_, array_ + len_, 0);
}

Array::Array(const Array &c1){
    len_ = c1.len_;
    array_ = new int[c1.len_];

    std::copy(c1.array_, c1.array_ + len_, array_);
}
Array::~Array() {
    delete[] array_;
}
Array& Array::operator= (const Array& c1){
    if(this != &c1) {
        delete[] array_;

        len_ = c1.len_;
        array_ = new int[len_];

        for (int i = 0; i < len_; ++i) {
            array_[i] = c1.array_[i];
        }
    }
    return *this;
}
int& Array::operator[] (std::size_t index){
    if(index < 0 || index >= len_){
        std::cout << "incorrect index" << '\n';
        return array_[0];
    }
    else {
        return array_[index];
    }
}
bool Array::Test() const{
    for (int i = 0; i < len_ - 1; ++i){
        if (array_[i] > array_[i + 1]){
            return false;
        }
    }
    return true;
}
bool Array::operator== (const Array& c1) const{
    if(len_ != c1.len_){
        return false;
    }
    int temp = 0;
    int length = c1.len_;

    for (int i = 0; i < len_; ++i) {
        for (int k = 0; k < length; ++k) {
            if (array_[i] == c1.array_[k]) {
                temp++;
                //std::swap(c1.array_[k], c1.array_[length - 1]);
                length--;
            }
        }
    }
    return (temp == len_);
}
Array Array::operator+(const Array& c1){

    if(!Test() || !c1.Test()){
        return Array();
    }

    Array res(len_ + c1.len_);
    res.array_ = new int[res.len_];

    int left_point = 0,
        right_point = 0,
        temp = 0;

    while(left_point < len_ && right_point < c1.len_){
        res.array_[temp++] = (array_[left_point] < c1.array_[right_point]) ? array_[left_point++] : c1.array_[right_point++];
    }
    if(len_ < c1.len_){
        std::copy(c1.array_ + right_point, c1.array_ + c1.len_,res.array_ + temp);
    }
    else {
        std::copy(array_ + left_point, array_ + len_, res.array_ + temp);
    }

    std::cout << res;

    return res;
}
size_t Array::get_len() const{
    return (len_);
}
size_t Array::get_bit() const {
    int max_el = *std::max_element(array_, array_ + len_);
    return trunc(log(max_el) / log(2));
}

void Array::Shell_sort(){
    int* h=nullptr,
            amount_step = trunc(log(len_) / log(2)),
            i = 0,
            step = 0,
            j = 0,
            temp = 0,
            k = 0;

    h = new int[amount_step];
    h[0] = len_ / 2;

    for (int i = 1; i < amount_step; i++){
        h[i] = h[i - 1] / 2;
    }

    while (i < amount_step){
        step = h[i];

        for(int b = 0; b < step; ++b){
            j = b + step;
            while (j < len_){
                temp = array_[j];
                k = j - step;

                while (k >= 0 && array_[k] > temp){
                    array_[k + step] = array_[k];
                    k -= step;
                }

                array_[k + step] = temp;
                j += step;
            }
        }
        i++;
    }

    delete[]h;
}
void Array::Shaker_sort(){

   int left_point = 0,
           right_point = int(len_) - 1,
           temp1 = 0,
           temp2 = 0,
           idx = 0;

    while (left_point < right_point){
        idx = left_point;
        temp1 = left_point;
        // проход слева-направо
        while(idx < right_point){
            if (array_[idx] > array_[idx + 1]){
                std::swap(array_[idx],array_[idx + 1]);
                temp1 = idx;
            }
            idx++;
        }

        right_point = temp1;  //запоминаем место текущего обмена
        // проход справа-налево
        temp2 = right_point;
        while(idx > left_point){
            if (array_[idx] < array_[idx - 1]){
                std::swap(array_[idx],array_[idx - 1]);
                temp2 = idx;
            }
            idx--;
        }

        left_point = temp2;     //запоминаем место текущего обмена
    }
}
void Array::Hoar_sort(int left_p, int right_p){
    if (left_p >= right_p){
        return;
    }

    int i = left_p,
        j = right_p,
        middle = array_[(i + j) / 2];    // среднее по индексу

    while (i <= j){
        while (array_[i] < middle){
            i++;
        }

        while (array_[j] > middle){
            j--;
        }

        if (i <= j){
            std::swap(array_[i], array_[j]);
            i++;
            j--;
        }
    }
    this->Hoar_sort(left_p, j);
    this->Hoar_sort(i, right_p);
}
void Array::Bit_sort(int left_point, int right_point, int k){
    if (left_point >= right_point || k < 0){
        return;
    }

    int i = left_point,
        j = right_point;

    while (i <= j){
        while (i <= j && (bool(array_[i] & (1<<k))) == 0){
            i++;
        }

        while (i <= j && (bool(array_[j] & (1<<k))) == 1){
            j--;
        }

        if (i < j){
            std::swap(array_[i], array_[j]);
            i++;
            j--;
        }
    }

    std::cout << k << '\n' << *this << '\n';

    this->Bit_sort(left_point, j, k - 1);
    this->Bit_sort(i, right_point, k - 1);
}

void Array::Pyramidal_sort(){
    int size = this->len_;
    //Heapify(*this, size);
    for(int i = size - 1; i >= 0; --i){
        Sift(*this, i + 1);
        std::swap(array_[0], array_[i]);
    }
}

Array Array::Sift(Array &a, int size){
    int mid = (size - 1) / 2;
    bool conditinal1;
    bool conditinal2;
    for(mid; mid >= 0; --mid){
        int i = mid;
        do{
            int currRoot = i;
            int l = 2*i + 1;
            int r = 2*i + 2;
            if(l < size && a[l] > a[i]) {
                i = l;
            }
            if(r < size && a[r] > a[i]) {
                i = r;
            }

            if(i != currRoot) {
                std::swap(a[currRoot], a[i]);
            }
            conditinal1 = (a[i] < a[2 * i + 1] && 2 * i + 1 < size);
            conditinal2 = (a[i] < a[2 * i + 2] && 2 * i + 2 < size);
        } while(conditinal1 || conditinal2);
    }
    return a;
}

std::istream& operator>>(std::istream& in, Array& c1){
    in >> c1.len_;
    delete [] c1.array_;

    c1.array_ = new int[c1.len_];
    for(int i = 0; i < c1.len_; ++i){
        in >> c1.array_[i];
    }
    return in;
}
std::ostream& operator<<(std::ostream& out, Array& c1) {
    for(int i = 0; i < c1.len_; ++i){
        out << c1.array_[i] << " ";
    }
    return out;
}
