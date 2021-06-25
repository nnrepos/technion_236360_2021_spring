#!/bin/bash

dos2unix -q more_tests/*
for t in {1..28}
do ./run_test.sh $t
done

for t in {1..45}
do ./run_error_test.sh $t
done
