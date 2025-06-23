//На прошлом степе вы познакомились с реализацией паттерна посетитель. Теперь пришло время воспользоваться этими знаниями. 
// Ваш класс должен печатать (используя std::cout) текстовое представление арифметического выражения. Т.е. для объекта класса Number он должен 
// напечатать число, которое в нем хранится, а для объекта класса BinaryOperation он должен напечатать левый операнд, затем операцию, а затем правый операнд.

//Учтите, что операции + и - имеют меньший приоритет, чем операции* и / , т.е.возможно вам придется печатать дополнительные круглые скобки, чтобы сохранить 
// правильный порядок операций.

//Классы иерархии Expression и абстрактный класс Visitor приведены в комментарии в шаблоне для удобства.

//При проверке задания лишние пробелы или лишние скобки будут игнорироваться, т.е.вывод "1+2" эквивалентен выводу 
// "( ( 1 )  +   ( 2 ) )", а вот вывод "1 + 2 * 3" не эквивалентен выводу "((1 + 2) * 3)".
// Вы можете попытаться минимизировать количество скобок в выводе, но это не требуется.

#include <iostream>

struct Number;
struct BinaryOperation;

struct Visitor {
    virtual void visitNumber(Number const* number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const* operation) = 0;
    virtual ~Visitor() { }
};

struct Expression
{
    virtual double evaluate() const = 0;
    virtual void visit(Visitor* vistitor) const = 0;
    virtual ~Expression() { }
};

struct Number : Expression
{
    Number(double value)
        : value(value)
    {}
    double evaluate() const;

    double get_value() const { return value; }

    void visit(Visitor* visitor) const { visitor->visitNumber(this); }

private:
    double value;
};

struct BinaryOperation : Expression
{
    BinaryOperation(Expression const* left, char op, Expression const* right)
        : left(left), op(op), right(right)
    { }

    ~BinaryOperation() {
        delete left;
        delete right;
    }
    double evaluate() const;

    Expression const* get_left() const { return left; }
    Expression const* get_right() const { return right; }
    char get_op() const { return op; }

    void visit(Visitor* visitor) const { visitor->visitBinaryOperation(this); }

private:
    Expression const* left;
    Expression const* right;
    char op;
};


struct PrintVisitor : Visitor {
    void visitNumber(Number const* number);    

    void visitBinaryOperation(BinaryOperation const* bop);
    
private:
    bool is = false;
};


void PrintVisitor::visitNumber(Number const* number) {
    std::cout << number->get_value() << ' ';
}

void PrintVisitor::visitBinaryOperation(BinaryOperation const* bop) {
    bool is_prev = this->is;
    char c = bop->get_op();
    bool is_cur = is_prev && (c == '-' or c == '+');
    if (is_cur)
        std::cout << "(" << ' ';

    this->is = c == '*' or c == '/';  
    bop->get_left()->visit(this);

    std::cout << c << ' ';

    this->is = c == '*' or c == '/';
    bop->get_right()->visit(this);

    if (is_cur)
        std::cout << ")" << ' ';
    this->is = is_prev;
}

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
}


int main()
{
    Expression* a = new Number(4);
    Expression* sube = new BinaryOperation(new Number(1), '+', new Number(2));
    Expression* expr0 = new BinaryOperation(sube, '-', sube);
    Expression* expr = new BinaryOperation(sube, '*', new Number(1.8));
    Expression* expr1 = new BinaryOperation(sube, '-', expr);
    Expression* expr2 = new BinaryOperation(new Number(5), '+', new BinaryOperation(new Number(2), '*', new Number(3)));
    PrintVisitor v;
    a->visit(&v);
    std::cout << std::endl;
    sube->visit(&v);
    std::cout << std::endl;
    expr0->visit(&v);
    std::cout << std::endl;
    expr->visit(&v);
    std::cout << std::endl;
    expr1->visit(&v);
    std::cout << std::endl;
    expr2->visit(&v);
    std::cout << std::endl;
    return 0;
}

