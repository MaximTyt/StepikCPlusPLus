/* Этот код просто напоминание как выглядит класс Foo и функция foo_says.
 * Не нужно его расскоментировать и/или менять.
 */
 #include <iostream>
 
 struct Foo {
     void say() const { std::cout << "Foo says: " << msg << "\n"; }
     ~Foo() {
         std::cout << this << std::endl;
     }
 protected:
     Foo(const char *msg) : msg(msg) { }
 private:
     const char *msg;
 };
 
 void foo_says(const Foo &foo) { foo.say(); }
 
 

 // Вам нужно определить функцию get_foo, как описано в задании,
 // чтобы компилировался и работал как ожидается следующий код:
 //
 // foo_says(get_foo("Hello!"));


 struct Foo_ : Foo {
     Foo_(const char* msg) : Foo(msg)
     {}
     ~Foo_() {
         std::cout << this << std::endl;
     }
 };

Foo get_foo(const char* msg) {
    return Foo_ (msg);
}

int main() {
    foo_says(get_foo("Hello, world! My name is Foo. I'm fine. And you?"));
    return 0;
}