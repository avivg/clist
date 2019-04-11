#!/bin/bash

make -C example || { echo "Make example failed"; exit 3; }
example/example > out.txt || { echo "Running example failed"; exit 3; }
fgrep 'x: 100, y: 200' out.txt || { echo "FAIL"; exit 3; }
fgrep 'x: 300, y: 400' out.txt || { echo "FAIL"; exit 3; }
(( `cat out.txt | wc -l` == 3 )) || { echo "FAIL"; exit 3; }
rm out.txt