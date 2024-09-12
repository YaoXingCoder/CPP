/*************************************************************************
    > File Name: my_vector.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月09日 星期一 22时35分09秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 实现自定义 vector
    > Content:

 ************************************************************************/

#include <iostream>
#include <cstring>

template <typename T>
std::allocator<T> Vector<T>::_alloc;

template < typename T >
Vector<T>::Vector(std::size_t n) :_start(_alloc.allocate(n)), _finish(_start + n), _end_of_storage(_start + n) {}

template < typename T >
Vector<T>::~Vector() {
    if ( _finish != _start ) {
        _alloc.destroy(--_finish);
    }
    _alloc.deallocate(_start, capacity());
    _start = nullptr;
    _finish = nullptr;
    _end_of_storage = nullptr;
    std::cout << "~Vector()" << std::endl;
}

template < typename T >
int Vector<T>::size() {
    return _finish - _start; 
}

template < typename T>
int Vector<T>::capacity() {
    return _end_of_storage - _start;
}

template <typename T>
void Vector<T>::push_back(const T & ele) {
    if ( size() == capacity() ) { reallocate(); }
    _alloc.construct(_finish++, ele);
}

template <typename T>
void Vector<T>::pop_back() {
    if ( size() == 0 ) { return ; }
    _alloc.destroy(--_finish);
}

template < typename T>
void Vector<T>::reallocate() {
    /* 分配新空间, 赋值数据 */
    std::size_t newCapacity = (size() == 0) ? 1 : size() * 2;
    T * tmp = _alloc.allocate(newCapacity);
    std::memcpy(tmp, _start, size() * sizeof(T));

    /* 释放旧空间 */
    if ( _start ) {
        while ( _start != _finish ) { _alloc.destroy(--_finish); }
        _alloc.deallocate(_start, capacity());
    }

    /* 更新数据 */
    _start = tmp;
    _finish = _start + newCapacity / 2;
    _end_of_storage = _start + newCapacity;

    tmp = nullptr;
}

