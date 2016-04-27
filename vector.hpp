//
//  vector.hpp
//  lab3
//
//  Created by Дима Басан on 25.04.16.
//  Copyright © 2016 Дима Басан. All rights reserved.
//

#ifndef vector_hpp
#define vector_hpp

template <typename T>
class Vector {
    T* arr;
    int capacity;
    int Size;
    bool resize();
public:
    class iterator {
    protected:
        T* value;
    public:
        iterator() : value() {};
        iterator(T* val) : value(val) {};
        bool operator++(int key);
        bool operator--();
        bool operator<(const iterator &another);
        bool operator<=(const iterator &another);
        bool operator==(const iterator &another);
        bool operator!=(const iterator &another);
        bool operator=(const iterator &another);
        T    operator*();
    };
    Vector();
    Vector(const Vector<T> &Q);
    T& operator[](const int &index);
    void push_back(const T &value);
    void clear();
    T back();
    T front();
    iterator begin();
    iterator end();
    int size();
    bool empty();
    void erase(int);
    ~Vector();
};

template <typename T>
Vector<T>::Vector() : Size(0), capacity(0) { }

template <typename T>
Vector<T>::~Vector() {
    delete[] arr;
}

template <typename T>
void Vector<T>::clear() {
    Size <= 1 ? delete arr : delete[] arr;
    capacity = Size = 0;
}

template <typename T>
T Vector<T>::back() {
    return arr[Size - 1];
    
}

template <typename T>
T Vector<T>::front() {
    return arr[0];
}

template <typename T>
int Vector<T>::size() {
    return Size;
}

template <typename T>
Vector<T>::Vector(const Vector<T> &Q) {
    this->Size = Q.Size;
    this->capacity = Q.capacity;
    arr = new T[capacity];
    for (int i = 0; i != Size; i++) {
        arr[i] = Q.arr[i];
    }
}

template <typename T>
void Vector<T>::push_back(const T &value) {
    if ( empty() ) {
        arr = new T(value);
        capacity = Size = 1;
    } else {
        if (  Size == capacity  ) {
            resize();
        }
        arr[Size] = value;
        Size++;
    }
}

template <typename T>
T& Vector<T>::operator[](const int &index) {
    return arr[index];
}

template <typename T>
bool Vector<T>::resize() {
    T* NewArea = new T[capacity * 2];
    for (int i = 0; i != this->Size; i++) {
        NewArea[i] = this->operator[](i);
    }
    Size == 1 ? delete arr : delete[] arr;
    arr = NewArea;
    capacity *= 2;
    return true;
}

template <typename T>
bool Vector<T>::empty() {
    return ( Size == 0 );
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
    return arr;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
    return (arr + Size);
}

template <typename T>
bool Vector<T>::iterator::operator--() {
    value--;
    return true;
}

template <typename T>
bool Vector<T>::iterator::operator++(int key) {
    (value) = ++value;
    return value;
}

template <typename T>
bool Vector<T>::iterator::operator==(const iterator &another) {
    return (value == another.value);
}

template <typename T>
bool Vector<T>::iterator::operator=(const iterator &another) {
    value = another.value;
    return true;
}

template <typename T>
bool Vector<T>::iterator::operator<(const iterator &another) {
    return (value < another.value);
}

template <typename T>
bool Vector<T>::iterator::operator<=(const iterator &another) {
    return (value <= another.value);
}

template <typename T>
bool Vector<T>::iterator::operator!=(const iterator &another) {
    return (value != another.value);
}

template <typename T>
T Vector<T>::iterator::operator*() {
    return (*value);
}

template <typename T>
void Vector<T>::erase(int position) {
    for (int i = position; i < Size; ++i)
        arr[i] = arr[i + 1];
    arr[Size] = 0;
    Size--;
}

#endif /* vector_hpp */
