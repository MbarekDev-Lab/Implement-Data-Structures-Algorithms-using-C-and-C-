# Debugging Guide

## Quick Start

### Option 1: Using VS Code Debugger (Recommended)

1. **Set breakpoints**: Click in the left margin next to line numbers in your code
2. **Start debugging**: 
   - Press `F5` or
   - Go to Run → Start Debugging
   - Select "Debug Main (lldb)" from the dropdown
3. **Debug controls**:
   - `F5` - Continue
   - `F10` - Step Over
   - `F11` - Step Into
   - `Shift+F11` - Step Out
   - `Shift+F5` - Stop

### Option 2: Using Terminal with lldb

```bash
# Build with debug symbols
cd Essential/Essential
clang++ -std=c++17 -g -O0 -o main main.cpp array_ADT/ArrayADT.cpp

# Start lldb
lldb ./main

# In lldb:
(lldb) breakpoint set --file ArrayADT.cpp --line 637  # Set breakpoint
(lldb) run                                           # Run program
(lldb) print arr1                                    # Print variable
(lldb) step                                          # Step into
(lldb) next                                          # Step over
(lldb) continue                                      # Continue
(lldb) quit                                          # Exit
```

### Option 3: Using GDB-style commands

```bash
# Build with debug symbols
clang++ -std=c++17 -g -O0 -o main main.cpp array_ADT/ArrayADT.cpp

# Run with debugger
lldb ./main

# Common commands:
# b <line> or b <function>  - Set breakpoint
# r                         - Run
# n                         - Next line
# s                         - Step into
# p <variable>              - Print variable
# bt                        - Backtrace
# c                         - Continue
```

## Build Tasks

VS Code tasks are configured:
- **build (debug)**: Compiles with `-g -O0` flags (default, press `Cmd+Shift+B`)
- **build (release)**: Compiles with `-O2` optimization
- **clean**: Removes the executable

## Debug Flags Explained

- `-g`: Include debug symbols
- `-O0`: No optimization (preserves variable names, easier debugging)
- `-O2`: Optimize for performance (harder to debug)

## Tips

1. **Set breakpoints** at function entry points or suspicious code
2. **Watch variables** in the Debug panel (left sidebar)
3. **Inspect call stack** to see function call hierarchy
4. **Use conditional breakpoints** (right-click breakpoint → Edit Breakpoint)

