#pragma once

namespace shelly::core {

/// @brief Orchestrator class for the shell. Instantiates all of the components, and executes them as needed.
///        
///        Contains entry point for Shelly after the config and log initialization is finsihed.
class Shell {
public:

    /// @brief Instantiate Shelly.
    /// @todo Add logs and config classes that are initialized in main.
    Shell();

    /// @brief Entry point for Shelly after the config and log initialization is finsihed.
    /// @return Exit status of the program.
    int run();

protected:
private:
};

} // namespace shelly::core