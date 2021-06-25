#!/bin/bash
test_=$1

echo "TEST t$test_"
./hw5 < more_tests/t$test_.in 2>&1 > more_tests/t$test_.llvm
lli more_tests/t$test_.llvm > more_tests/t$test_.res
diff more_tests/t$test_.res more_tests/t$test_.out

