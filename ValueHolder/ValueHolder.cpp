// Шаблонные классы можно наследовать. Реализуйте шаблонную структуру ValueHolder с одним типовым параметром T, унаследованную от интерфейса ICloneable. 
// Интерфейс ICloneable содержит всего один виртуальный метод ICloneable* clone() const, который должен вернуть указатель на копию объекта, на котором 
// он был вызван (объект должен быть создан в куче). Шаблон ValueHolder, как говорит его название, хранит всего одно значение (назовите его data_) 
// типа T (для типа T определен конструктор копирования). Не делайте поле data_ закрытым (поэтому в данном случае мы явно пишем, что ValueHolder должна быть 
// структурой).
#include <iostream>

struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

template <typename T>
struct ValueHolder : ICloneable {

	ValueHolder(const T& data) : data_(data)
	{}
	ValueHolder* clone() const { return new ValueHolder(data_); }
	T data_;
};

// написать класс Any (интересно, что не шаблонный), который позволяет хранить значения любого типа! Например, вы сможете  создать массив объектов типа Any, 
// и сохранять в них int-ы, double-ы или даже объекты Array.

class Any
{
    ICloneable* data_;

public:

    Any() : data_(0)
    {}

    template <typename Type>
    Any(Type const& other) : data_(new ValueHolder<Type>(other))
    {}

    Any(Any const& other) : data_(other.data_ ? other.data_->clone() : 0)
    {}

    void swap(Any& a)
    {
        std::swap(data_, a.data_);
    }

    Any& operator=(Any const& other) {
        if (this != &other)
            Any(other).swap(*this);
        return *this;
    }

    template <class Type>
    Any& operator=(Type const& other) {
        this->~Any();
        data_ = new ValueHolder<Type>(other);
        return *this;
    }

    template <typename Type>
    Type* cast() {
        ValueHolder<Type>* tmp = dynamic_cast<ValueHolder<Type> *>(data_);
        return tmp ? &tmp->data_ : 0;
    }

    ~Any()
    {
        delete data_;
    }


};


int main()
{
	/*ValueHolder<int> a(1);

	ValueHolder<int> b(2);

	std::cout << a.clone()->data_ << std::endl;*/

    Any i(10);
    Any a(5.4);
    Any b(a);
    Any c;
    c = a;
    c = 7;

    int* iptr = i.cast<int>();
    std::cout << *iptr << std::endl;
    double* dptr = i.cast<double>();
    std::cout << (dptr ? true : false) << std::endl;
    return 0;
}