#!/bin/bash

args=("$@")
if [ $# -eq 0 ]; then
args=(-i)
fi

find ./include ./src \
	   -path ./include/extern -prune \
	-o -path ./src/extern -prune \
	-o '(' -name '*.c' -o -name '*.h' ')' '!' -path './src/asm/parser.?' \
		-exec clang-format -style=file "${args[@]}" '{}' +
