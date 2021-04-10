.PHONY: all clean zip

all: scanner.lex part_a.cpp part_b.cpp
	flex scanner.lex
	g++ -std=c++11 lex.yy.c part_a.cpp -o part_a.out
	g++ -std=c++11 lex.yy.c part_b.cpp -o part_b.out

clean:
	rm lex.yy.c part_*.out

zip:
	zip final.zip scanner.lex part_a.cpp part_b.cpp tokens.hpp
