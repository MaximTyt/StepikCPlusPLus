//Вам дан класс Rational, который описывает рациональное число. В нем определены методы add, sub, mul и div, которые прибавляют к нему число, отнимают число, 
// умножают на число и делят на число соответственно. Кроме того в нем определен метод neg, который меняет знак на противоположный.
//Вам нужно определить операторы +=, -=, *=, /= для класса Rational так, чтобы они могли принимать в качестве аргументов и объекты типа Rational и целые числа.
// Кроме того вам необходимо определить операторы унарного минуса и плюса для класса Rational.

#include <iostream>

struct Rational
{
    Rational(int numerator = 0, int denominator = 1);

    int get_numerator() const;
    int get_denominator() const;

    void add(Rational rational);
    void sub(Rational rational);
    void mul(Rational rational);
    void div(Rational rational);

    void neg();
    void inv();
    double to_double() const;

    Rational& operator+=(Rational const& rational);
    Rational& operator-=(Rational const& rational);
    Rational& operator*=(Rational const& rational);
    Rational& operator/=(Rational const& rational);

    Rational operator-() const;
    Rational operator+() const;

    operator double() const {
        return to_double();
    }


private:
    int numerator_;
    int denominator_;
};





Rational::Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator)
{}

void Rational::add(Rational rational)
{
    if (denominator_ != rational.denominator_){
        numerator_ *= rational.denominator_;
        rational.numerator_ *= denominator_;
        denominator_ *= rational.denominator_;
    }
    numerator_ += rational.numerator_;
}

void Rational::sub(Rational rational)
{
    if (denominator_ != rational.denominator_) {
        numerator_ *= rational.denominator_;
        rational.numerator_ *= denominator_;
        denominator_ *= rational.denominator_;
    }
    numerator_ -= rational.numerator_;
}

void Rational::mul(Rational rational)
{    
    numerator_ *= rational.numerator_;
    denominator_ *= rational.denominator_;
}

void Rational::div(Rational rational)
{
    numerator_ *= rational.denominator_;
    denominator_ *= rational.numerator_;
}

void Rational::neg()
{
    numerator_ = -numerator_;
}

void Rational::inv()
{
    int temp = numerator_;
    numerator_ = denominator_;
    denominator_ = temp;
}

double Rational::to_double() const
{
    return (double)numerator_ / denominator_;
}

Rational& Rational::operator+=(Rational const& rational)
{
    add(rational);
    return *this;
}

Rational& Rational::operator-=(Rational const& rational)
{
    sub(rational);
    return *this;
}

Rational& Rational::operator*=(Rational const& rational)
{
    mul(rational);
    return *this;
}

Rational& Rational::operator/=(Rational const& rational)
{
    div(rational);
    return *this;
}

Rational Rational::operator-() const
{
    Rational r(numerator_, denominator_);
    r.neg();
    return r;
}

Rational Rational::operator+() const
{       
    return Rational(numerator_, denominator_);
}

// Определите для класса Rational операторы сложения, вычитания, умножения и деления, так чтобы объекты типа Rational можно было складывать 
// (вычитать, умножать и делить) не только друг с другом но и с целыми числами.

Rational operator+(Rational a, Rational const& b)
{    
    return a += b;
}

Rational operator-(Rational a, Rational const& b)
{
    return a -= b;
}

Rational operator*(Rational a, Rational const& b)
{
    return a *= b;
}

Rational operator/(Rational a, Rational const& b)
{
    return a /= b;
}

// Еще одна важная группа операторов, которые полезно реализовать для класса рациональных чисел — это операторы сравнения. 
// Реализуйте операторы <, <=, >, >=, ==, != для класса Rational так, чтобы можно было сравнивать объекты класса Rational не только друг с другом, 
// но и с целыми числами.
// При решении задания не используйте метод to_double, он введен в класс, в первую очередь, для удобства тестирования.Вы можете определять любые 
// вспомогательные методы или функции если необходимо.

int Rational::get_numerator() const {
    return numerator_;
}

int Rational::get_denominator() const {
    return denominator_;
}

bool operator==(Rational const& a, Rational const& b) {
    return a.get_numerator() * b.get_denominator() == a.get_denominator() * b.get_numerator();
}

bool operator!=(Rational const& a, Rational const& b) {
    return !(a == b);
}

bool operator>(Rational const& a, Rational const& b) {
    return a.get_numerator() * b.get_denominator() > a.get_denominator() * b.get_numerator();
}

bool operator<(Rational const& a, Rational const& b) {
    return b > a;
}

bool operator>=(Rational const& a, Rational const& b) {
    return !(b > a);
}

bool operator<=(Rational const& a, Rational const& b) {
    return !(a > b);
}



void swap(Rational& a, Rational& b) {
    Rational c = a;
    a = b;
    b = c;
}



int main()
{
    Rational a(4, 5);
    Rational b(5, 4);
    Rational c(2, 3);
    /*c = a + b;
    c = a - b;
    c = a * b;
    c = a / b;
    c = 2 + b;
    c = a + 2;
    std::cout << "a == b => " << (a == b) << std::endl;
    std::cout << "a > b => " << (a > b) << std::endl;
    std::cout << "a >= b => " << (a >= b) << std::endl;
    std::cout << "a < b => " << (a < b) << std::endl;
    std::cout << "a <= b => " << (a <= b) << std::endl;
    std::cout << "a == 4/5 => " << (a == Rational(4, 5)) << std::endl;
    std::cout << "5/4 == b => " << (Rational(5, 4) == b) << std::endl;
    std::cout << "2 == 2/1 => " << (2 == Rational(2, 1)) << std::endl;*/
    std::cout << "a = " << a.get_numerator() << '/' << a.get_denominator() << " = " << a.to_double() << std::endl;
    std::cout << "a = " << a.get_numerator() << '/' << a.get_denominator() << " = " << double(a) << std::endl;
    std::cout << "c = " << c.get_numerator() << '/' << c.get_denominator() << " = " << double(c) << std::endl;
    return 0;
}