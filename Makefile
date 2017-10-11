CC=g++

all: dfa_intersection DFA_minimizer dfa_for_single_pattern

dfa_intersection: dfa.hpp dfa_intersection.cpp
	$(CC) -Wall -std=c++11 dfa_intersection.cpp -o dfa_intersection

dfa_for_single_pattern: dfa_for_single_pattern.cpp
	$(CC) -Wall -std=c++11 dfa_for_single_pattern.cpp -o dfa_for_single_pattern

DFA_minimizer: DFA_minimizer.cc
	$(CC) -Wall -std=c++11 DFA_minimizer.cc -o DFA_minimizer

clean:
	rm -f dfa_intersection
	rm -f DFA_minimizer
	rm -f dfa_for_single_pattern

.PHONY: all clean
