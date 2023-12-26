#ifndef _MY_VECTOR_
#define _MY_VECTOR_

#include <iostream>

template <class T>
T square(T a);

template <class T>
class MyVector {
public:
    int getSize();
    void print();
    void push(T a);
    MyVector<T> operator*(const MyVector<T> &mv);
private:
    T arr[1000];
    int size = 0;
};

template <class T>
T square(T a) {
    return a * a;
}

template <class T>
int MyVector<T>::getSize() {
    return size;
}

template <class T>
void MyVector<T>::print() {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << std::endl;
    }
}

template <class T>
void MyVector<T>::push(T a) {
    arr[size++] = a;
}

template <class T>
MyVector<T> MyVector<T>::operator*(const MyVector<T> &mv) {
    MyVector<T> res;
    for (int i = 0; i < size; ++i) {
        res.arr[i] = arr[i] * mv.arr[i];
    }
    res.size = size;
    return res;
}

#endif
