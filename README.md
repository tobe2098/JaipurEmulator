# JaipurEmulator
Emulates the game (both players can see each other's hands)



# Use instructions
## C library must be
```
#include <stdio.h>

typedef struct {
    int x;
    double y;
} MyCustomType;

MyCustomType* process_custom_type(MyCustomType* input) {
    static MyCustomType result = {0, 0.0};  // Initialized once
    result.x = input->x * 2;  // Modified on each call
    result.y = input->y * 3.14;  // Modified on each call
    return &result;
}
```
## Package

### Julia library

```
using Libdl

lib = Libdl.dlopen("./libmyclib.so")  # or .dylib on macOS, .dll on Windows

struct MyCustomType
    x::Cint
    y::Cdouble
end

function process_custom_type(input::MyCustomType)
    result_ptr = ccall(
        (:process_custom_type, lib),
        Ptr{MyCustomType},
        (Ref{MyCustomType},),
        input
    )
    return result_ptr  # Return the pointer directly
end

# Create a wrapper type to work with the pointer
struct MyCustomTypePtr
    ptr::Ptr{MyCustomType}
end

# Define methods to access the struct members
Base.getproperty(m::MyCustomTypePtr, s::Symbol) = getproperty(unsafe_load(m.ptr), s)

# Usage
input = MyCustomType(5, 2.5)
result_ptr = process_custom_type(input)
result = MyCustomTypePtr(result_ptr)

println("Result: x = $(result.x), y = $(result.y)")

Libdl.dlclose(lib)
```