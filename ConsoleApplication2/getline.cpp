//В этой задаче вам нужно реализовать функцию resize.Функция resize принимает на вход три аргумента : указатель на область памяти, выделенную с помощью 
// оператора new[], размер области(size) и новый размер(new_size).Функция должна выделить память размера new_size, скопировать в нее данные из переданной 
// области памяти, освободить старую область памяти и вернуть выделенную область памяти нового размера со скопированными данными.

//Обратите внимание, что память, возвращенная из функции, будет освобождена с помощью оператора delete[].Несмотря на то, что входной тип данных — это const char*, 
// не стоит рассчитывать, что там хранится C - style строка.При выполнении задания также учтите, что new_size может быть меньше size.

#include <iostream>

char* resize(char* str, unsigned size, unsigned new_size)
{
    char* news = new char[new_size];
    size = size >= new_size ? new_size : size;
    for (int i = 0; i < size; i++)
        news[i] = str[i];
    delete[] str;
    return news;
}


//Реализуйте функцию getline, которая считывает поток ввода посимвольно, пока не достигнет конца потока или не встретит символ переноса строки ('\n'), 
// и возвращает C-style строку с прочитанными символами.

//Обратите внимание, что так как размер ввода заранее неизвестен, то вам нужно будет перевыделять память в процессе чтения, если в потоке ввода оказалось 
// больше символов, чем вы ожидали.

//Память, возвращенная из функции будет освобождена оператором delete[].Символ переноса строки('\n') добавлять в строку не нужно, но не забудьте, 
// что в конце C - style строки должен быть завершающий нулевой символ.

char* getline()
{
    char c = '\0';
    char* str = new char[1];
    int i = 0;
    for (; std::cin.get(c) && c != '\n'; i++) {
        str = resize(str, i, i + 1);
        str[i] = c;
    }
    str[i] = '\0';
    return str;
}

struct Number {};

struct BigInt : Number
{
    BigInt(int x): _x(x)
    {}
    int _x;
};

struct String
{
    explicit String(char const* s);
};

int main()
{
    //std::cout << getline() << std::endl;

    int a = 3.5;

    double b = 7;

    std::cout << a <<' ' << b << std::endl;

    BigInt c = 100500;

    //String d = static_cast<String>("Stepik");

    Number* e = &c;


    BigInt* f = static_cast<BigInt*>(e);

    void* g = f;

    BigInt* h = static_cast<BigInt*>(g);
    return 0;
}