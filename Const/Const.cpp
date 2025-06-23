

#include <iostream>

int main()
{
    int a = 10;
    int b = 20;
    int* p = &a;
    int** p4 = &p;
    int* const* p2 = &p;
    int const ** p3 = new int const * [5];
    *p3 = new int[5 * 3];
    //p3[0][0] = 1;
    *p3 = &b;
    
    std::cout << "p3[0][0] = " << p3[0][0] << std::endl;

    /*p3 = p4;
    std::cout << "p3[0][0] = " << p3[0][0] << std::endl;*/
    //std::cout << "Hello World!\n";
}


