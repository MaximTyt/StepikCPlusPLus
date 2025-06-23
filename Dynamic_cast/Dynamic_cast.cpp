#include<iostream>
// объ€вл€ем наследников Shape
struct Rectangle;
struct Triangle;
struct Circle;

// все 6 вариантов функций пересечени€
bool is_intersect(Rectangle* a, Rectangle* b) { std::cout << "R x R\n"; return true; }
bool is_intersect(Rectangle* a, Triangle* b) { std::cout << "R x T\n"; return true; }
bool is_intersect(Rectangle* a, Circle* b) { std::cout << "R x C\n"; return true; }
bool is_intersect(Triangle* a, Triangle* b) { std::cout << "T x T\n"; return true; }
bool is_intersect(Triangle* a, Circle* b) { std::cout << "T x C\n"; return true; }
bool is_intersect(Circle* a, Circle* b) { std::cout << "C x C\n"; return true; }

// базовый класс фигуры
struct Shape
{
    virtual ~Shape() {}
    virtual bool intersect(Rectangle* r) = 0;
    virtual bool intersect(Triangle* t) = 0;
    virtual bool intersect(Circle* c) = 0;
    virtual bool intersect(Shape* s) = 0;
};

// пр€моугольник
struct Rectangle : Shape
{
    bool intersect(Rectangle* r) { return is_intersect(this, r); }
    bool intersect(Triangle* t) { return is_intersect(this, t); }
    bool intersect(Circle* c) { return is_intersect(this, c); }
    bool intersect(Shape* s) {
        return s->intersect(this);
    }
};

// треугольник
struct Triangle : Shape
{
    bool intersect(Rectangle* r) { return is_intersect(r, this); }
    bool intersect(Triangle* t) { return is_intersect(t, this); }
    bool intersect(Circle* c) { return is_intersect(this, c); }
    bool intersect(Shape* s) {
        return s->intersect(this);
    }
};

// круг
struct Circle : Shape
{
    bool intersect(Rectangle* r) { return is_intersect(r, this); }
    bool intersect(Triangle* t) { return is_intersect(t, this); }
    bool intersect(Circle* c) { return is_intersect(c, this); }
    bool intersect(Shape* s) {
        return s->intersect(this);
    }
};

// реализаци€ самой функции
bool is_intersect(Shape* a, Shape* b)
{
    return a->intersect(b);
}

int main() {
    Shape* a = new Triangle();
    Shape* b = new Circle();
    Shape* c = new Triangle();
    std::cout << "a == b = > " << is_intersect(a, b) << std::endl;
    std::cout << "a == c = > " << is_intersect(a, c) << std::endl;
    std::cout << "b == c = > " << is_intersect(b, c) << std::endl;
    return 0;
}