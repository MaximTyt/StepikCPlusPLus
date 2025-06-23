// В качестве упражнения на частичную специализацию шаблонов классов вам предлагается реализовать простой шаблон SameType. 
// Этот шаблон не содержит никаких методов, а только одно статическое константное поле типа bool, с именем value. 
// Шаблон принимает два типовых параметра, и если два типовых параметра шаблона являются одним и тем же типом, то статическое поле value 
// должно хранить значение true, в противном случае значение false. Примеры:

//struct Dummy {};
//typedef int type;
//std::cout << SameType<int, int>::value << std::endl; // выведет 1, т. е. true
//std::cout << SameType<int, type>::value << std::endl; // 1, type == int
//std::cout << SameType<int, int&>::value << std::endl; // 0, int и ссылка на int - различные типы
//std::cout << SameType<Dummy, Dummy>::value << std::endl; // 1
//std::cout << SameType<int, const int>::value << std::endl; // 0, const - часть типа
#include <iostream>

//template <typename T>
//struct SameType
//{
//    static const bool value = true;
//};

template <typename T, typename U>
struct SameType
{
    static const bool value = false;
};

template <typename T>
struct SameType<T, T>
{
    static const bool value = true;
};


template <typename T, size_t N>
size_t array_size(T (&)[N]) {
    return N;
}

int main()
{
    struct Dummy { };
    typedef int type;
    std::cout << SameType<int, int>::value << std::endl; // выведет 1, т. е. true
    std::cout << SameType<int, type>::value << std::endl; // 1, type == int
    std::cout << SameType<int, int&>::value << std::endl; // 0, int и ссылка на int - различные типы
    std::cout << SameType<Dummy, Dummy>::value << std::endl; // 1
    std::cout << SameType<int, const int>::value << std::endl; // 0, const - часть типа

    int ints[] = { 1, 2, 3, 4 };
    
    std::cout << array_size(ints) << std::endl;
    int* iptr = ints;
    //std::cout << array_size(iptr) << std::endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
