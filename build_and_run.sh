#!/bin/bash

# Navigate to the project root directory
cd "$(dirname "$0")"

# Compile C++ version
echo "Compiling..."

# Compile C++ ArrayMenu.cpp and Essential.cpp together
clang++ -std=c++17 -o main Essential.cpp "ArrayDSA/ArrayMenuusing_cpp/ArrayMenu.cpp"

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "✓ Compilation successful!"
    echo ""
    echo "Running program..."
    echo "---"
    ./main
else
    echo "✗ Compilation failed!"
    exit 1
fi
