#!/bin/bash
test_=$1

echo "TEST te$test_"
./hw5 < more_tests/te$test_.in 2>&1 > more_tests/te$test_.res
diff more_tests/te$test_.res more_tests/te$test_.out

