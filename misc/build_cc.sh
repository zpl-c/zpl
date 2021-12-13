#!/bin/bash

set -xe

# run from root dir
cmake -B build -S misc -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
ln -s build/compile_commands.json .

