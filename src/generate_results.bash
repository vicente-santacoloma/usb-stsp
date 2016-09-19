#!/bin/bash

rm RESULT/$1 2> /dev/null
for i in {1..10}
do
    echo "RUN: $i"
    echo "RUN: $i" >> RESULT/$1
    ./tsp-test ALL_tsp/$1 >> RESULT/$1
    echo "" >> RESULT/$1
    sleep 1
done
