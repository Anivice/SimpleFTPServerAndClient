#include <debug.h>
#include <iostream>
#include <simple_err.h>

void func3()
{
    throw simple_error_t(SUCCESS_CDX, "error test");
}

void func2()
{
    func3();
}

void func1()
{
    func2();
}

int main (int, char ** argv)
{
    initialize_symbol_vector(argv[0]);

    auto func = []()
    {
        func1();
    };
    try
    {
        func();
    }
    catch (simple_error_t & e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
