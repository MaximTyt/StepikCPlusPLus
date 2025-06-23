// 1) В этой задаче вам требуется реализовать конструктор, который принимает на вход C-style строку, вычисляет ее размер 
// (без учета завершающего 0 символа) и сохраняет его в поле size, кроме того, конструктор должен аллоцировать память достаточную для хранения копии 
// переданной строки (вместе с завершающим 0 символом), копирует переданную строку в выделенную память и сохраняет указатель на начало этой области памяти 
// в поле str. Т.е. в результате работы конструктора в поле str должен оказаться указатель на C-строку c копией исходной строки, а в поле size — длина строки 
// без учета завершающего нулевого символа.
// 2) Конструкторов у структуры может быть несколько. Для строки может оказаться полезным заполняющий конструктор (например, чтобы создать строку пробелов). 
// Заполняющий конструктор принимает число и символ, и создает строку с заданным количеством повторений переданного символа. Условия налагаемые на реализацию 
// конструктора те же самые (в поле size размер без учета завершающего 0 символа, в поле str C-style строка, т.е. с завершающим 0 символом). Кроме конструктора 
// в этой задаче вам нужно также реализовать и деструктор, который освободит выделенную память.
// 3) реализовать метод append. 
// При выполнении задания будьте аккуратны при работе с памятью — при вызове метода не должно возникать утечек памяти.Кроме того, не забудьте, 
// что size хранит размер без учета завершающего 0 символа.
// 4) Добавьте в класс String реализацию конструктора копирования. 
// 5) Завершите класс String, добавив к нему оператор присваивания. Будьте аккуратны при работе с памятью.
// Инвариант класса остается тем же (в size хранится размер строки без завершающего 0 символа, str указывает на C-style строку, т. е. с 
// завершающим нулевым символом).
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <iostream>
#include <algorithm>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

struct String {

	/* Реализуйте этот конструктор */
	String(const char* str);
	/* Реализуйте этот конструктор */
	String(size_t n, char c);
	/* и деструктор */
	~String();

	/* Реализуйте конструктор копирования */
	String(const String& other);
	/* Реализуйте оператор присваивания */
	String & operator=(const String& other);
	String operator[](size_t i) const;

	/* Реализуйте этот метод. */
	void append(String& other);
	void swap(String& other);

	char & at(size_t idx);
	char   at(size_t idx) const;

	size_t size;
	char* str;	
};

String::String(const char* str = "") : size(strlen(str)), str(strcpy(new char[size + 1], str))
{}

String::String(size_t n, char c) {
	size = n;
	str = new char[size + 1];
	for (size_t i = 0; i != n; i++)
		str[i] = c;
	str[size] = '\0';
}



String::String(const String& other) : size(other.size), str(strcpy(new char[size + 1], other.str))
{}

String& String::operator=(const String & other)
{
	if (this != &other)
		String(other).swap(*this);	
	return *this;
}

// В этой задаче вам требуется реализовать оператор [] для уже известного вам класса String. Однако на этот раз оператор должен реализовывать нестандартное 
// поведение: оператор нужно реализовать таким образом, чтобы для объекта str класса String можно было писать str[i][j] и это выражение возвращало подстроку 
// начинающуюся в позиции i (считая с 0) и заканчивающуюся в позиции j (не включая).

String String::operator[](size_t i) const
{
	String s;
	if (i < size) {
		delete[] s.str;
		s.str = strcpy(new char[size - i + 1], str + i);
		s.size = i;
	}
	else {
		s.size = i - size;
		if (i) {
			delete[] s.str;
			s.str = strncpy(new char[s.size + 1], str, s.size);
		}
		s.str[s.size] = '\0';
	}
	return s;
}

	/*if (i < size) {
		String s(str + i);
		s.size = i;
		return s;
	}
	else {
		String s;
		s.size = i - size;
		if (i) {
			delete[] s.str;
			s.str = strncpy(new char[s.size + 1], str, s.size);
		}
		s.str[s.size] = '\0';
		return s;
	}*/



String::~String() {
	delete[] str;
}

void String::append(String& other) {
	size += other.size;
	char* t_str = new char[size + 1];
	strcpy(t_str, str);
	strcat(t_str, other.str);
	this->~String();
	str = t_str;
}

void String::swap(String& other)
{
	std::swap(size, other.size);
	std::swap(str, other.str);
}

char& String::at(size_t idx)
{
	return str[idx];
}

char String::at(size_t idx) const
{
	return str[idx];
}

int main() {
	
	/*size_t n;
	char c;
	std::cout << "Count = ";
	std::cin >> n;
	std::cout << "Simbol = ";
	std::cin >> c;
	String str0(n, c);
	std::cout << "Size of string without 0 = " << str0.size << std::endl;
	std::cout << "The string = " << str0.str << std::endl;
	String str1("Hello_");
	std::cout << "Size of string without 0 = " << str1.size << std::endl;
	std::cout << "The string = " << str1.str << std::endl;
	str1.append(str0);
	std::cout << "Size of string without 0 = " << str1.size << std::endl;
	std::cout << "The string = " << str1.str << std::endl;
	str1.append(str1);
	std::cout << "Size of string without 0 = " << str1.size << std::endl;
	std::cout << "The string = " << str1.str << std::endl;*/

	/*String str("Hello, world!");
	std::cout << "Size of string without 0 = " << str.size << std::endl;
	std::cout << "The string = " << str.str << std::endl;
	String str1(str);
	std::cout << "Size of string without 0 = " << str1.size << std::endl;
	std::cout << "The string = " << str1.str << std::endl;
	String str2;
	str2 = str1;
	std::cout << "Size of string without 0 = " << str2.size << std::endl;
	std::cout << "The string = " << str2.str << std::endl;*/


	/*String greet("Hello");
	char ch1 = greet.at(0);

	String const const_greet("Hello, Const!");
	char const& ch2 = const_greet.at(0);*/

	String const hello("hello");
	/*std::cout << "Size of string without 0 = " << hello.size << std::endl;
	std::cout << "strlen == " << strlen(hello.str) << std::endl;
	std::cout << "The string = " << hello.str << std::endl;*/



	String const hell = hello[0][4];
	std::cout << "Size of string without 0 = " << hell.size << std::endl;
	std::cout << "strlen == " << strlen(hell.str) << std::endl;
	std::cout << "The string = " << hell.str << std::endl;


	String const hell1 = hello[1][4];
	
	std::cout << "Size of string without 0 = " << hell1.size << std::endl;
	std::cout << "strlen == " << strlen(hell1.str) << std::endl;
	std::cout << "The string = " << hell1.str << std::endl;	

	String const hell2 = hell[0][1];
	std::cout << "Size of string without 0 = " << hell2.size << std::endl;
	std::cout << "strlen == " << strlen(hell2.str) << std::endl;
	std::cout << "The string = " << hell2.str << std::endl;
	
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}
