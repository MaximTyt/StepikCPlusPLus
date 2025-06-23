// В этом задании вам предлагается разработать иерархию классов Expression для представления арифметических выражений. Конкретнее, вам нужно определить три класса: 
// Expression — базовый класс иерархии, Number — для представления чисел и BinaryOperation — класс описывающий бинарную операцию (+, -, * или /).

//Класс Number должен хранить значение типа double.

//Класс BinaryOperation должен хранить указатель на левый и правый операнды, которые сами являются арифметическими выражениями, а также тип операции(+, -, *или / ), 
// которую нужно над ними произвести.

//Во всех классах должен быть метод evaluate, который возвращает значение типа double — значение соответствующего арифметического выражения, например, значение 
// экземпляра типа Number — это число, которое он хранит, а если у вас есть объект BinaryOperation с операцией + , то нужно вычислить значения левого и правого 
// операнда и вернуть их сумму.

//В данном задании вам нужно расставить ключевое слово virtual там, где это необходимо, определить метод evaluate там, где его не хватает, а также реализовать 
// деструкторы, там где они нужны.

//При выполнении этого задания учтите, что при уничтожении объекта BinaryOperation он отвечает за уничтожение левого и правого операндов(гарантируется, 
// что они выделены в динамической памяти).

#include <iostream>
#include <algorithm>

struct Expression
{
    virtual double evaluate() const = 0;
    virtual ~Expression() {}
};

struct Number : Expression
{
    Number(double value)
        : value(value)
    {}
    double evaluate() const;



private:
    double value;
};

struct BinaryOperation : Expression
{
    /*
      Здесь op это один из 4 символов: '+', '-', '*' или '/', соответствующих операциям,
      которые вам нужно реализовать.
     */
    BinaryOperation(Expression const* left, char op, Expression const* right)
        : left(left), op(op), right(right)
    { }

    double evaluate() const;
    ~BinaryOperation() {
        delete left;
        delete right;        
    }

private:
    Expression const* left;
    Expression const* right;
    char op;
};

double Number::evaluate() const { return value; }

double BinaryOperation::evaluate() const
{
    if (op == '+')
        return left->evaluate() + right->evaluate();
    if (op == '-')
        return left->evaluate() - right->evaluate();
    if (op == '*')
        return left->evaluate() * right->evaluate();
    if (op == '/')
        if (right->evaluate() == 0)
            return 0;
        else
            return left->evaluate() / right->evaluate();
    return 0;
}

// Вам требуется реализовать функцию, которая принимает на вход два указателя на базовый класс Expression, и возвращает true, если оба указателя указывают 
// на самом деле на объекты одного и того же класса, и false в противном случае (т.е. если оба указателя указывают на BinaryOperation, то возвращается true, 
// а если один из них указывает на Number, а второй на BinaryOperation, то false).

bool _check_equals(Expression const* left, Expression const* right)
{   
    
    std::cout << *(void**)left << std::endl;
    std::cout << *(void**)right << std::endl;
        
    return *(void**)left == *(void**)right;
}

bool check_equals(Expression const* left, Expression const* right)
{
    return typeid(*left) == typeid(*right);
}


struct ScopedPtr
{    
    explicit ScopedPtr(Expression* ptr = 0);
    ~ScopedPtr();
    Expression* get() const;
    Expression* release();
    void reset(Expression* ptr = 0);
    Expression& operator*() const;
    Expression* operator->() const;        

private:
    // запрещаем копирование ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression* ptr_;
};


//Реализуйте ScopedPtr, который будет работать с указателями на базовый класс Expression.В этом задании вам требуется реализовать методы get, release и reset, 
// операторы* и->так, как это было описано в предыдущем степе.А также реализуйте конструктор ScopedPtr от указателя на Expression.


ScopedPtr::ScopedPtr(Expression* ptr) : ptr_(ptr)
{}

ScopedPtr::~ScopedPtr()
{
    delete ptr_;
}

Expression* ScopedPtr::get() const
{
    return ptr_;
}

Expression* ScopedPtr::release()
{
    Expression* ptr = ptr_;
    ptr_ = 0;
    return ptr;
}

void ScopedPtr::reset(Expression* ptr)
{
    delete ptr_;
    ptr_ = ptr;
}

Expression& ScopedPtr::operator*() const
{
    return *ptr_;
}

Expression* ScopedPtr::operator->() const
{
    return ptr_;
}

// Реализуйте класс SharedPtr как описано ранее. Задание немного сложнее, чем кажется на первый взгляд. 
// Уделите особое внимание "граничным случаям" — нулевой указатель, присваивание самому себе, вызов reset на нулевом SharedPtr и прочее.


struct SharedPtr
{    
    explicit SharedPtr(Expression* ptr = 0);
    ~SharedPtr();
    SharedPtr(const SharedPtr&);
    SharedPtr& operator=(const SharedPtr&);
    Expression* get() const;
    void reset(Expression* ptr = 0);
    Expression& operator*() const;
    Expression* operator->() const;

private:
    Expression* ptr_;
    size_t* c_;
};

SharedPtr::SharedPtr(Expression* ptr) : ptr_(ptr), c_(ptr_ ? new size_t(1) : 0)
{}

SharedPtr::~SharedPtr()
{
    if (c_ && (-- * c_ == 0)) {
        delete ptr_;
        delete c_;        
    }
}

SharedPtr::SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), c_(other.c_)
{
    if (c_)
        ++*c_;
}

SharedPtr& SharedPtr::operator=(const SharedPtr& other)
{
    if (ptr_ != other.ptr_)
    {
        if (ptr_)
            this->~SharedPtr();

        ptr_ = other.ptr_;
        c_ = other.c_;        

        if (other.ptr_)
            ++*other.c_;        
    }
    return *this;
}

Expression* SharedPtr::get() const { return ptr_; }

void SharedPtr::reset(Expression* ptr)
{
    if(ptr != ptr_)
        this->~SharedPtr();
    ptr_ = ptr;
    c_ = ptr_ ? new size_t(1) : 0;
}

Expression& SharedPtr::operator*() const { return *ptr_; }

Expression* SharedPtr::operator->() const { return ptr_; }

template<class T>
bool isSameObject(T const* p, T const* q)
{
    return dynamic_cast<void const*>(p) == dynamic_cast<void const*>(q);
}



int main()
{
    Expression* sube = new BinaryOperation(new Number(1), '/', new Number(2));

    //std::cout << sube->evaluate() << std::endl;

    Expression* expr = new BinaryOperation(sube, '+', new Number(1.8));

    Expression* c = new Number(4);

    std::cout << expr->evaluate() << std::endl;


    Expression* c1 = static_cast<Number *>(c);
    Number* d = new Number(5);

    std::cout << "sube == expr => " << _check_equals(sube, expr) << std::endl;
    std::cout << "c1 == d => " << _check_equals(c1, d) << std::endl;
    std::cout << "sube == d => " << _check_equals(sube, d) << std::endl;

    std::cout << "sube == expr => "  << check_equals(sube, expr) << std::endl;
    std::cout << "c1 == d => "  << check_equals(c1, d) << std::endl;
    std::cout << "sube == d => "  << check_equals(sube, d) << std::endl;

    std::cout << "(isSameObject) sube == expr => "  << isSameObject(sube, expr) << std::endl;
    std::cout << "(isSameObject) c1 == c => "  << isSameObject(c1, c) << std::endl;
    std::cout << "(isSameObject) sube == c => "  << isSameObject(sube, c) << std::endl;

    //Expression* sube = new BinaryOperation(new Number(1), '/', new Number(2));


    /*ScopedPtr ptr(sube);
    std::cout << ptr.get()->evaluate() << std::endl;
    std::cout << ptr->evaluate() << std::endl;
    std::cout << (*ptr).evaluate() << std::endl;
    Expression* p = ptr.release();
    std::cout << p->evaluate() << std::endl;
    ptr.reset();
    ptr.reset(expr);
    std::cout << ptr->evaluate() << std::endl;*/

    SharedPtr ptr;    
    std::cout << (ptr.get() == nullptr) << std::endl;
    ptr.reset();
    std::cout << (ptr.get() == nullptr) << std::endl;

    SharedPtr ptr3(c);

    ptr3 = ptr;

    
    //ptr1.reset();
    //ptr1 = ptr3;
    return 0;
}