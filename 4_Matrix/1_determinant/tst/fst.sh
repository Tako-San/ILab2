#! /bin/bash

g++ -Wall -Wextra -g tstgen.cpp -o gen
for((i=0; i<20; i++))
do
    ./gen $1 $2 | ../cmake-*/matr
done

