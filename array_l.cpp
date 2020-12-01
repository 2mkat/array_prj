#include "array_l.h"

#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>


Array::Array(int size, int key, int range){

    srand(time(nullptr));

    len_ = size;
    array_ = new int[len_];

    if(key == 1){
        for(int i = 0; i < len_; ++i){
            array_[i] = rand() % (range + range) - range;
        }
    }
    else if(key == 2){
        for(int i = 0; i < len_; ++i){
            array_[i] = rand() % (range + range) - range;
        }
        std::sort(array_, array_ + len_);
    }
    else{
        for(int i = 0; i < len_; ++i){
            array_[i] = rand() % (range + range) - range;
        }
        std::sort(array_, array_ + len_, [](int i, int j){return i > j;});
    }
}
Array::Array(const int *array, int size_array){

    array_ = new int[size_array];
    std::copy(array, array + size_array, array_);

    len_ = size_array;
}

Array::Array(Array &c1){
    len_ = c1.len_;
    array_ = new int[c1.len_];

    std::copy(c1.array_, c1.array_ + len_, array_);
}
Array::~Array() {
    delete[] array_;
    array_ = nullptr;

}
Array& Array::operator= (Array c1){
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
int& Array::operator[] (int index){
    if(index < 0 || index >= len_){
        cout << "incorrect index" << '\n';
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
bool Array::operator== (Array& c1) const{
    if(len_ != c1.len_){
        return false;
    }

    int temp = 0;
    int length = c1.len_;

    for(int i = 0; i < len_; ++i){
        for(int k = 0; k < length; ++k){
            if(array_[i] == c1.array_[k]){
                temp++;
                swap(c1.array_[k], c1.array_[length - 1]);
                length--;
            }
        }
    }
    return (temp == len_) ? true : false;
}
Array Array::operator+(Array& c1){

    if(!Test() || !c1.Test()){
        Array res;
        return res;
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

    cout << res;

    return res;
}

void Array::Shell_sort(){

    std::vector<int> step = {(len_)/2};
    for(int i = 1; step.at(i-1) != 1; ++i){
        step.push_back(step.at(i - 1)/2);
    }

    int j = 0,
        temp = 0,
        k = 0,
        s = 0,
        b = 0;
    for(auto i : step){
        s = i;      //s = step
        b = 0;
        while(b < s){
            j = b + s;
            while (j < len_){
                temp = array_[j];
                k = j - s; // position the first element
                while (array_[k] > temp && k >= 0){
                    std::swap(array_[k], array_[k + s]);
                    k -= s;
                }

                /*while (array_[k] > temp && k >= 0){  // по убыванию
                    std::swap(array_[k], array_[k + s]);
                    k -= s;
                }*/

                array_[k + s] = temp;
                j += s;
            }
            b++;
        }
    }
}
void Array::Shaker_sort(){
    int l = 0,
        r = len_ - 1,
        r1 = 0,
        l1 = 0,
        i = 0;

    while (l<r){
        i = l;
        r1 = l;

        while (i<r){
            if (array_[i]>array_[i+1]){
                swap(array_[i], array_[i + 1]);
                r1 = i;
            }
            i++;
        }
        r = r1;

        while (l<i){
            if (array_[i]<array_[i-1]){
                swap(array_[i - 1], array_[i]);
                l1 = i;
            }
            i--;
        }
        l = l1;
    }
}
void Array::Hoar_sort(int left_p, int right_p){
    if (left_p >= right_p){
        return;
    }

    int i = left_p,
        j = right_p,
        x = array_[(left_p + right_p) / 2];

    while (i<=j){
        while (array_[i]<x){
            i++;
        }

        while (array_[j]>x){
            j--;
        }

        if (i<=j){
            swap(array_[i], array_[j]);
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

    while (i<=j){
        while (i<=j && (bool(array_[i] & (1<<k)))==0){
            i++;
        }

        while (i<=j && (bool(array_[j] & (1<<k)))==1){
            j--;
        }

        if (i<j){
            swap(array_[i], array_[j]);
            i++;
            j--;
        }
    }

    //выполнение той же процедуру для двух других фрагментов
    this->Bit_sort(left_point, j, k - 1);
    this->Bit_sort(i, right_point, k - 1);
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