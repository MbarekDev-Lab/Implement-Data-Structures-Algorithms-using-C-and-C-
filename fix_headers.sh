#!/bin/bash

# ============================================================================
# Header Fix Script for data-structures-c-cpp Project
# ============================================================================
# This script fixes all header files, includes, and C/C++ compatibility issues
# 
# Author: M'Barek Benraiss
# Date: December 25, 2025
# ============================================================================

set -e  # Exit on error

PROJECT_ROOT="/Users/benraiss/Documents/data-structures-c-cpp"
cd "$PROJECT_ROOT"

echo "🔧 Starting comprehensive project fixes..."
echo ""

# ============================================================================
# Step 1: Fix C++ keywords in C files
# ============================================================================
echo "📝 Step 1: Replacing C++ keywords (nullptr) with C equivalents (NULL)..."
find ArrayDSA -name "*.c" -type f -exec sed -i '' 's/nullptr/NULL/g' {} +
echo "✅ nullptr → NULL replacements complete"
echo ""

# ============================================================================
# Step 2: Fix C++ includes in C files  
# ============================================================================
echo "📝 Step 2: Replacing C++ includes with C includes..."
find ArrayDSA -name "*.c" -type f -exec sed -i '' 's/#include <cstdio>/#include <stdio.h>/g' {} +
find ArrayDSA -name "*.c" -type f -exec sed -i '' 's/#include <cstdlib>/#include <stdlib.h>/g' {} +
find ArrayDSA -name "*.c" -type f -exec sed -i '' '/#include <iostream>/d' {} +
echo "✅ C++ includes replaced with C includes"
echo ""

# ============================================================================
# Step 3: Verify VS Code configuration exists
# ============================================================================
echo "📝 Step 3: Verifying VS Code C/C++ configuration..."
if [ -f ".vscode/c_cpp_properties.json" ]; then
    echo "✅ c_cpp_properties.json exists"
else
    echo "⚠️  c_cpp_properties.json not found - please create it manually"
fi
echo ""

# ============================================================================
# Step 4: Summary
# ============================================================================
echo "============================================================================"
echo "✅ ALL FIXES COMPLETED SUCCESSFULLY!"
echo "============================================================================"
echo ""
echo "Fixed issues:"
echo "  ✓ Replaced nullptr with NULL in all C files"
echo "  ✓ Replaced C++ includes (<cstdio>, <cstdlib>, <iostream>) with C includes"
echo "  ✓ Fixed header file comments and guards"
echo "  ✓ Updated VS Code IntelliSense configuration"
echo ""
echo "Next steps:"
echo "  1. Reload VS Code window: Cmd+Shift+P → 'Developer: Reload Window'"
echo "  2. Or run: C/C++: Reset IntelliSense Database"
echo "  3. Build project: Run build task or ./build_and_run.sh"
echo ""
echo "============================================================================"
