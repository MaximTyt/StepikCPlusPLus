// В предыдущей версии предполагается, что для типа T определены оператор присваивания и конструктор по умолчанию. 
// При создании шаблонных классов контейнеров (вроде Array и не только) разумно стараться минимизировать требования к типам шаблонных параметров. 
// Поэтому усложним задачу, реализуйте класс Array не полагаясь на то, что для типа T определен оператор присваивания и конструктор по умолчанию. 
// Конструктор копирования у типа T есть.
#include <iostream>
#include <cstddef>

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

    explicit Array(size_t size, const T& value = T()) : size_(size), data_((T*)new char[size_ * sizeof(T)]) {
        for (size_t i = 0; i != size_; i++)
            new (data_ + i) T(value);
    }

    Array(){
        size_ = 0;
        data_ = 0;
    }

    Array(const Array& other) : size_(other.size_), data_((T*)new char[size_ * sizeof(T)]) {
        for (size_t i = 0; i != size_; i++)
            new (data_ + i) T(other[i]);
    }

    ~Array() 
    { 
        for (size_t i = 0; i != size_; i++)
            data_[i].~T();
        delete [] (char*)data_;
        
    }


    Array& operator=(const Array& other)
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

    T& operator[](size_t i) { return *(data_ + i); }

    const T& operator[](size_t i) const { return *(data_ + i); }

};

// Шаблонный класс Array может хранить объекты любого типа, для которого определён конструктор копирования, в том числе и другой Array, 
// например, Array< Array<int> >. Глубина вложенности может быть произвольной. Напишите шаблонную функцию (или несколько) flatten, которая 
// принимает на вход такой "многомерный" Array неизвестной заранее глубины вложенности и выводит в поток out через пробел все элементы, 
// хранящиеся на самом нижнем уровне. Примеры работы функции flatten:

//  Array<int> ints(2, 0);
//  ints[0] = 10;
//  ints[1] = 20;
//  flatten(ints, std::cout); // выводит на экран строку "10 20"
//  Array< Array<int> > array_of_ints(2, ints);
//  flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20"
//  Array<double> doubles(10, 0.0);
//  flatten(doubles, std::cout); // работать должно не только для типа int

template <typename T>
std::ostream& operator<<(std::ostream& os, Array<T> const& t) {
    for (int i = 0; i != t.size(); i++)
        os << t[i] << ' ';
    return os;
}

template <typename T>
void flatten(const Array<T>& array, std::ostream& out)
{    
    out << array;
}

int main()
{
   /* Array<int> a(10, 5);
    std::cout << "Size a == " << a.size() << std::endl;
    for (size_t i = 0; i != a.size(); i++)
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
        std::cout << "b1[" << i << "] == " << b1[i] << std::endl;*/
    Array<int> ints(2, 0);
    ints[0] = 10;
    ints[1] = 20;
    Array< Array<int> > array_of_ints(2, ints);
    flatten(array_of_ints, std::cout);
    return 0;
}
