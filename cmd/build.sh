#!/bin/sh

# Exit immediately if a cmd exits with non-zero status
set -e

# Default Unix fallback
PREFIX="/usr/local"

# Check if /usr/local exists and is writable, or if we can create it
if [ -w "/usr/local" ] || { [ ! -d "/usr/local" ] && [ -w "/usr" ]; }; then
	echo "--> System /usr/local is writable. Using standard installation path."
else
	echo "--> /usr/local is write-protected. Falling back to user home directory."
	PREFIX="$HOME/.local"
fi
echo "--> PREFIX: $PREFIX"

# Build and install
cmake -S src -B build -DCMAKE_INSTALL_PREFIX="$PREFIX" 
cmake --build build 
cmake --install build

