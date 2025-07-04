﻿// Определен следующий класс (он также приведен в комментарии в шаблоне кода):

//struct Cls {
//    Cls(char c, double d, int i);
//private:
//    char c;
//    double d;
//    int i;
//};
//Как видно, все поля этого класса закрытые, ваша задача реализовать несколько функций, которые дают полный доступ к этим полям(см.шаблон кода), 
// несмотря на то, что они закрытые.

//Внимание: предполагаемое решение этого задания существенно опирается на Undefined Behaviour и является исключительно учебным, но полезно для лучшего понимания 
// того, как работают модификаторы доступа.Решение было проверено на различных компиляторах(g++ / clang++ / icc / msvc), но мы настоятельно не рекомендуем 
// использовать подобные трюки в боевом коде.

#include <iostream>

//Класс Cls определен точно таким образом:

struct Cls {
    Cls(char c, double d, int i);
private:
    char c;
    double d;
    int i;
};

struct _Cls {
    _Cls(char c, double d, int i);
    char c;
    double d;
    int i;
};

Cls::Cls(char c, double d, int i) : c(c), d(d), i(i)
{}

_Cls::_Cls(char c, double d, int i) : c(c), d(d), i(i)
{}

 // Эта функция должна предоставить доступ к полю c объекта cls.
 // Обратите внимание, что возвращается ссылка на char, т. е.
 // доступ предоставляется на чтение и запись.
char &get_c(Cls& cls) {
    _Cls * _cls = (_Cls*)((void*)& cls);
    return _cls->c;
}

// Эта функция должна предоставить доступ к полю d объекта cls.
// Обратите внимание, что возвращается ссылка на double, т. е.
// доступ предоставляется на чтение и запись.
double &get_d(Cls& cls) {
    _Cls* _cls = (_Cls*)((void*)&cls);
    return _cls->d;
}

// Эта функция должна предоставить доступ к полю i объекта cls.
// Обратите внимание, что возвращается ссылка на int, т. е.
// доступ предоставляется на чтение и запись.
int &get_i(Cls& cls) {
    _Cls* _cls = (_Cls*)((void*)&cls);
    return _cls->i;
}

int main()
{
    Cls cls('#', 5.1, 7);
    std::cout << "c = " << get_c(cls) << std::endl;
    std::cout << "d = " << get_d(cls) << std::endl;
    std::cout << "i = " << get_i(cls) << std::endl;
    return 0;
}