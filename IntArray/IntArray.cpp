#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <iostream>
#include <algorithm>

struct IntArray {

	explicit IntArray(size_t n);
	IntArray(const IntArray& a);
	IntArray& operator=(const IntArray& a);
	~IntArray();
	
	void swap(IntArray& a);

	size_t size() const;

	int get(size_t i) const;
	int& get(size_t i);

	void resize(size_t nsize);

private:
	size_t size_;
	int* data_;
};



IntArray::IntArray(size_t n) : size_(n), data_(new int[size_])
{
	for (size_t i = 0; i != size_; i++)
		data_[i] = 0;
}

IntArray::IntArray(const IntArray& a) : size_(a.size_), data_(new int[size_])
{
	for (size_t i = 0; i != size_; i++)
		data_[i] = a.data_[i];
}

IntArray& IntArray::operator=(const IntArray& a)
{
	if (this != &a)
		IntArray(a).swap(*this);
	return *this;
}

IntArray::~IntArray() {
	delete[] data_;
}

size_t IntArray::size() const
{
	return size_;
}

int IntArray::get(size_t i) const
{
	return data_[i];
}

int& IntArray::get(size_t i)
{
	return data_[i];
}

void IntArray::resize(size_t nsize)
{
	if (size_ == nsize)
		return;
	IntArray t(nsize);
	size_t n = nsize > size_ ? size_ : nsize;
	for (size_t i = 0; i != n; i++)
		t.data_[i] = data_[i];
	swap(t);
}

void IntArray::swap(IntArray& a)
{
	std::swap(size_, a.size_);
	std::swap(data_, a.data_);
}

int main() {
	IntArray a(5);
	for (size_t i = 0; i != a.size(); i++)
		a.get(i) = a.size() - i;
	std::cout << "a.get(0) = " << a.get(0) << std::endl;
	IntArray const b(a);
	std::cout << "b.get(0) = " << b.get(0) << std::endl;
	a.resize(2);
	std::cout << "a.size() = " << a.size() << std::endl;
	std::cout << "a.get(2) = " << a.get(1) << std::endl;

	IntArray const& c = a;
	std::cout << "c.get(2) = " << c.get(1) << std::endl;
	return 0;
}


