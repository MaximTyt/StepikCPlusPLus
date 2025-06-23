#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
struct String {

	/* Реализуйте этот конструктор */
	String(const char* str = "") {
		this->size = strlen(str);
		this->str = new char[size + 1];
		strcpy(this->str, str);
	}

	size_t size;
	char* str;
};

int main() {
	/*String str("Hello!");
	std::cout << "Размер строки без 0 = " << str.size << std::endl;
	std::cout << "Сама строка = " << str.str << std::endl;*/
	int n = 5;
	int* mas = NULL;
	mas = (int*)malloc(n);
	std::cout << _msize(mas) << std::endl;
	mas = (int*)realloc(mas, n * sizeof(int));
	std::cout << _msize(mas) << std::endl;
	free(mas);
	return 0;
}