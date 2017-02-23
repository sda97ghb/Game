#include "Test/Test.h"
//#include "Test/PhysicsPainter.h"

#include <iostream>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
//    PhysicsPainter::instance().run(argc, argv);
    test::main(argc, argv);
    std::cout << "Done." << std::endl;
    return 0;
}
