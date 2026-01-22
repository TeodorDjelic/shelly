#include <iostream>

#include "shelly/core/Shell.hpp"

int main(int, char**){
    shelly::core::Shell shell;

    /// @todo Add logging.
    std::cout << "Shelly starting..." << std::endl;

    return shell.run();
}
