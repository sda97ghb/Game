#include "Test/Test.h"

#include <iostream>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    test::main();
    std::cout << "Done." << std::endl;
    return 0;
}
