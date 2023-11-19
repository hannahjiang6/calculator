###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Hannah Jiang (hjiang03)

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

## CAUTION:  DO NOT JUST USE THE OLD RULES FOR 'clean'!!!
##           You do NOT want to remove Datum.o!!

# Compiles CalcYouLater
CalcYouLater: main.o RPNCalc.o DatumStack.o Datum.o
	$(CXX) $(LDFLAGS) -o CalcYouLater main.o RPNCalc.o DatumStack.o Datum.o

# This rule builds main.o
main.o: main.cpp RPNCalc.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# This rule builds RPNCalc.o
RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.cpp
	$(CXX) $(CXXFLAGS) -c RPNCalc.cpp

# This rule builds DatumStack.o
DatumStack.o: DatumStack.cpp DatumStack.h
	$(CXX) $(CXXFLAGS) -c DatumStack.cpp

# This rule builds parser.o
parser.o: parser.cpp parser.h
	$(CXX) $(CXXFLAGS) -c parser.cpp

# Compiles and runs unit_test
unit_test: unit_test_driver.o RPNCalc.o DatumStack.o Datum.o parser.o 
	$(CXX) $(CXXFLAGS) $^


# This rule provides my final submission 
provide:
	provide comp15 proj2_calcyoulater DatumStack.h \
				   DatumStack.cpp RPNCalc.h \
				   RPNCalc.cpp main.cpp \
				   parser.cpp parser.h \
				   test1.txt test2.txt test3.txt \
				   test4.txt test5.txt test6.txt \
				   fib.cylc fact.cylc n_fibs.cylc \
				   unit_tests.h README Makefile

## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^


clean: 
	rm DatumStack.o parser.o RPNCalc.o *~ a.out