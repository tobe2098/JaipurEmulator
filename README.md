# JaipurEmulator
Emulates the game (both players can see each other's hands)



# Use instructions
## C library must be
```
#include <stdlib.h>

typedef struct {
    int x;
    double y;
    int** matrix;
    int rows;
    int cols;
} MyCustomType;

MyCustomType* create_custom_type(int x, double y, int rows, int cols) {
    MyCustomType* obj = (MyCustomType*)malloc(sizeof(MyCustomType));
    obj->x = x;
    obj->y = y;
    obj->rows = rows;
    obj->cols = cols;
    
    obj->matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        obj->matrix[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            obj->matrix[i][j] = 0;
        }
    }
    
    return obj;
}

MyCustomType* process_custom_type(MyCustomType* input) {
    MyCustomType* result = create_custom_type(input->x * 2, input->y * 3.14, input->rows, input->cols);
    // Process matrix if needed
    return result;
}

void free_custom_type(MyCustomType* obj) {
    if (obj) {
        for (int i = 0; i < obj->rows; i++) {
            free(obj->matrix[i]);
        }
        free(obj->matrix);
        free(obj);
    }
}
```
## Package

### Julia library

```using Libdl

# Load the shared library
lib = Libdl.dlopen("./libmyclib.so")  # or .dylib on macOS, .dll on Windows

# Define the struct in Julia to match the C struct
struct MyCustomType
    x::Cint
    y::Cdouble
    matrix::Ptr{Ptr{Cint}}
    rows::Cint
    cols::Cint
end

# Define functions to call C functions
function create_custom_type(x::Int, y::Float64, rows::Int, cols::Int)
    ccall(
        (:create_custom_type, lib),
        Ptr{MyCustomType},
        (Cint, Cdouble, Cint, Cint),
        x, y, rows, cols
    )
end

function process_custom_type(input::Ptr{MyCustomType})
    ccall(
        (:process_custom_type, lib),
        Ptr{MyCustomType},
        (Ptr{MyCustomType},),
        input
    )
end

function free_custom_type(obj::Ptr{MyCustomType})
    ccall(
        (:free_custom_type, lib),
        Cvoid,
        (Ptr{MyCustomType},),
        obj
    )
end

# Usage example
input_ptr = create_custom_type(5, 2.5, 3, 3)
input = unsafe_load(input_ptr)

println("Input: x = $(input.x), y = $(input.y)")

output_ptr = process_custom_type(input_ptr)
output = unsafe_load(output_ptr)

println("Output: x = $(output.x), y = $(output.y)")

# Accessing matrix elements (be careful with this!)
for i in 1:input.rows
    row = unsafe_load(input.matrix, i)
    for j in 1:input.cols
        value = unsafe_load(row, j)
        println("input.matrix[$i][$j] = $value")
    end
end

# Clean up
free_custom_type(input_ptr)
free_custom_type(output_ptr)

# Close the library when done
Libdl.dlclose(lib)
```