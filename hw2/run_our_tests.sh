# Compile
make
echo

# Run staff tests
TEST_NUMBER=74
for i in $(seq 1 $TEST_NUMBER)
do
  echo "Running test "$i
  ./hw2 < our_tests/t"$i".in >& our_tests/t"$i".myout
  diff our_tests/t"$i".out our_tests/t"$i".myout
done
