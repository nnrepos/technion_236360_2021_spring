#!/bin/bash
for i in  {1..17}; do
	cat ./tests_a/t$i.in | ./part_a.out > ./tests_a/t$i.myout;
	diff -u ./tests_a/t$i.out ./tests_a/t$i.myout;
done;

for i in  {1..7}; do
	cat ./tests_b/t$i.in | ./part_b.out > ./tests_b/t$i.myout;
	diff -u ./tests_b/t$i.out ./tests_b/t$i.myout;
done;
