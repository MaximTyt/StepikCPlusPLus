// Реализуйте шаблонную версию класса Array. Список всех операций, которые должен поддерживать класс Array, приведен в шаблоне кода.
#include <iostream>
#include <cstddef>
#include <algorithm>

template <typename T>
class Array
{
    size_t size_;
    T* data_;
    // Список операций:
    //
    // explicit Array(size_t size = 0, const T& value = T())
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.
    //
    // Array(const Array &)
    //   конструктор копирования, который создает
    //   копию параметра. Считайте, что для типа
    //   T определен оператор присваивания.
    //
    // ~Array()
    //   деструктор, если он вам необходим.
    //
    // Array& operator=(...)
    //   оператор присваивания.
    //
    // size_t size() const
    //   возвращает размер массива (количество
    //                              элементов).
    //
    // T& operator[](size_t)
    // const T& operator[](size_t) const
    //   две версии оператора доступа по индексу.
    
public:

    explicit Array(size_t size = 0, const T& value = T()) : size_(size), data_(new T[size]) {
        for (size_t i = 0; i != size_; i++)
            data_[i] = value;
    }

    Array(const Array& other) : size_(other.size_), data_(new T[size_]) {
        for (size_t i = 0; i != size_; i++)
            data_[i] = other.data_[i];
    }

    ~Array() { delete[] data_; }


    Array & operator=(const Array& other)
    {
        if (this != &other)
            Array(other).swap(*this);
        return *this;
    }

    void swap(Array& other)
    {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    size_t size() const { return size_; }

    T& operator[](size_t i){ return data_[i]; }

    const T& operator[](size_t i) const { return data_[i]; }

};
int main()
{
    Array<int> a(10, 5);
    std::cout << "Size a == " << a.size() << std::endl;
    for(size_t i = 0; i != a.size(); i++)
        std::cout << "a[" << i << "] == " << a[i] << std::endl;

    Array<int> a1;
    a1 = a;
    std::cout << "Size a1 == " << a1.size() << std::endl;
    for (size_t i = 0; i != a1.size(); i++)
        std::cout << "a1[" << i << "] == " << a1[i] << std::endl;

    Array<double> b(5, 5.4);
    std::cout << "Size b == " << b.size() << std::endl;
    for (size_t i = 0; i != b.size(); i++)
        std::cout << "b[" << i << "] == " << b[i] << std::endl;

    Array<double> b1(b);
    std::cout << "Size b1 == " << b1.size() << std::endl;
    for (size_t i = 0; i != b1.size(); i++)
        std::cout << "b1[" << i << "] == " << b1[i] << std::endl;

}

