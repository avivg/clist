#!/bin/bash

make -C example || { echo "Make examples failed"; exit 3; }
example/basic_example > out.txt || { echo "Running example failed"; exit 3; }
head -1 out.txt | egrep 'x: 100, y: 200' || { echo "FAIL"; exit 3; }
head -2 out.txt | tail -1 | egrep 'x: 300, y: 400' || { echo "FAIL"; exit 3; }
(( `cat out.txt | wc -l` == 2 )) || { echo "FAIL"; exit 3; }
rm out.txt

example/classic_example > out.txt || { echo "Running example failed"; exit 3; }
head -1 out.txt | egrep 'x: 100, y: 200' || { echo "FAIL"; exit 3; }
head -2 out.txt | tail -1 | egrep 'x: 300, y: 400' || { echo "FAIL"; exit 3; }
(( `cat out.txt | wc -l` == 2 )) || { echo "FAIL"; exit 3; }
rm out.txt