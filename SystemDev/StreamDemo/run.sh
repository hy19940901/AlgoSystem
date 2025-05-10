#!/bin/bash

set -e

# Build shared lib and server binary
make clean
make

# Export LD_LIBRARY_PATH for Linux if needed
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    export LD_LIBRARY_PATH=$(pwd)/bin:$LD_LIBRARY_PATH
fi

# Run the server
./bin/server
