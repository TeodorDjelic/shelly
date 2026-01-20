#pragma once

#include <memory>

#include "FileDescriptor.hpp"
#include "Pipe.hpp"

namespace shelly::platform {

class Process;
class ProcessBuilder;

namespace detail {
    
    class ProcessHandle;
    
}

/// @brief Platform indepentent process object.
class Process {
public:
protected:
private:
    Process();

    std::unique_ptr<detail::ProcessHandle> processHandle;
    friend class ProcessBuilder;
};

/// @brief API builder class for creating processes.
class ProcessBuilder {
public:

    /// @brief Redirects the process' output to the given output file descriptor.
    /// @param output Output file descriptor.
    /// @return Returns this process builder object.
    ProcessBuilder& redirectOutput(const FileDescriptor& output);

    /// @brief Redirects the process' input to the given input file descriptor.
    /// @param output Input file descriptor.
    /// @return Returns this process builder object.
    ProcessBuilder& redirectInput(const FileDescriptor& input);

    /// @brief Spawns the process and returns the process object.
    /// @return Process object.
    std::unique_ptr<Process> spawn();

protected:
private:
    std::unique_ptr<Process> process;
};

} // namespace shelly::platform