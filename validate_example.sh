#!/bin/bash

make -C example
example/example > out.txt
fgrep 'x: 100, y: 200' out.txt || { echo "FAIL"; exit 3; }
fgrep 'x: 300, y: 400' out.txt || { echo "FAIL"; exit 3; }
(( `cat out.txt | wc -l` == 3 )) || { echo "FAIL"; exit 3; }
rm out.txt