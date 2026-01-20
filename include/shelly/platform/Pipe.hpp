#pragma once

#include <memory>

namespace shelly::platform {

class Pipe;
class FileDescriptor;

namespace detail {

class PipeHandle;

}

/// @brief API function for creating pipes.
/// @return New pipe.
std::unique_ptr<Pipe> makePipe();

/// @brief Platform indepentent pipe object.
class Pipe {
public:

    /// @brief Returns pipe input file descriptor.
    /// @return Pipe input file descriptor.
    const FileDescriptor& getInputFileDescriptor() const;

    
    /// @brief Returns pipe output file descriptor.
    /// @return Pipe output file descriptor.
    const FileDescriptor& getOutputFileDescriptor() const;

protected:
private:
    std::unique_ptr<detail::PipeHandle> pipeHandle;
};

} // namespace shelly::platform