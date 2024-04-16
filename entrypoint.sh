#!/bin/bash
# Ignore errors during compilation and runtime
g++ -std=c++17 sorting/bubble_sort.cpp -o my_application || echo "Compilation failed"
./my_application || echo "Application failed"

# Start zsh shell
exec zsh
