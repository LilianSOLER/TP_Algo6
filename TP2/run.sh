#!/bin/sh
make
echo "\n"
./a234 data/arbre$1
echo "\n"
make clean