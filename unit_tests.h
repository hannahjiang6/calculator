/*
 *  unit_tests.h
 *  Hannah Jiang (hjiang03)
 *  2/22/2023
 *
 *  CS 15 PROJECT 2 CalcYouLater
 *
 *  FILE PURPOSE:
 *  File to test cases for my program: CalcYouLater
 *  includes parser, DatumStack, and RPNCalc tested functions
 *  
 *  NOTE: all the RPNCalc functions are commented out because
 *  they were made private after testing
 *
 */

#include <iostream>
#include <string>
#include <cassert>
#include <fstream>

#include "parser.h"
#include "DatumStack.h"
#include "RPNCalc.h"

// testing the default constructor
void defaultConstructor() {
    DatumStack datum;
    assert(datum.size() == 0);
    assert(datum.isEmpty() == true);
}

// testing the array constructor
void arrayConstructor() {
    Datum data[2] = {Datum(5), Datum(4)};
    DatumStack datum(data, 2);

    assert(datum.top() == data[1]);
    assert(datum.size() == 2);
    assert(datum.isEmpty() == false);
}

// testing the top function
void top() {
    Datum data[4] = {Datum(5), Datum(4), Datum(true), Datum(false)};
    DatumStack datum(data, 4);

    assert(datum.top().getBool() == false);
    assert(datum.size() == 4);
    assert(datum.isEmpty() == false);
}

// testing the top function error message
void top_fail() {
    bool runtime_error = false;
    std::string error_message = "";
    DatumStack datum;
    try {
        datum.top();

    } catch (std::runtime_error &e) {
        runtime_error = true;
        error_message = e.what();
    }
    assert(runtime_error);
    assert(error_message == "empty_stack");
}

// testing the isEmpty function if false
void isEmpty_false() {
    Datum data[4] = {Datum(5), Datum(4), Datum(true), Datum(false)};
    DatumStack datum(data, 4);

    assert(datum.isEmpty() == false);
}

// testing the isEmpty function if true
void isEmpty_true() {
    DatumStack datum;
    
    assert(datum.isEmpty() == true);
}

// testing the clear function
void clear() {
    Datum data[4] = {Datum(5), Datum(4), Datum(true), Datum(false)};
    DatumStack datum(data, 4);

    datum.clear();

    assert(datum.isEmpty() == true);
    assert(datum.size() == 0);
}

// testing the pop function 
void pop() {
    Datum data[4] = {Datum(5), Datum(4), Datum(true), Datum(false)};
    DatumStack datum(data, 4);

    datum.pop();

    assert(datum.size() == 3);
    assert(datum.top().getBool() == true);
}

// testing the pop function fail
void pop_fail() {
    bool runtime_error = false;
    std::string error_message = "";
    DatumStack datum;
    try {
        datum.pop();

    } catch (std::runtime_error &e) {
        runtime_error = true;
        error_message = e.what();
    }
    assert(runtime_error);
    assert(error_message == "empty_stack");    
}

// testing push function
void push1() {
    DatumStack datum;

    datum.push(Datum(3));

    assert(datum.size() == 1);
    assert(datum.top().getInt() == 3);    
}

// testing push function 100 times
void push100() {
    DatumStack datum;

    for (int i = 0; i < 100; i++) {
        datum.push(Datum(3));
    }

    assert(datum.size() == 100);
    assert(datum.top().getInt() == 3);    
}

// testing the parser file
void pt1() {
    std::string test;

    std::ifstream infile;
   
    infile.open("test1.txt");
    infile.get();
    
    test = parseRString(infile);
    std::cout << test << std::endl;
    assert(test == "{ 1 2 + }");
    infile.close();
}

// testing the parser file
void pt2() {
    std::string test;

    std::ifstream infile;
   
    infile.open("test2.txt");
    infile.get();
    
    test = parseRString(infile);
    std::cout << test << std::endl;
    assert(test == "{ alice in wonderland }");
    infile.close();
}

// testing the parser file
void pt3() {
    std::string test;

    std::ifstream infile;
   
    infile.open("test3.txt");
    infile.get();
    
    test = parseRString(infile);
    std::cout << test << std::endl;
    assert(test == "{ }");
    infile.close();
}

// testing the parser file
void pt4() {
    std::string test;

    std::ifstream infile;
   
    infile.open("test4.txt");
    infile.get();
    
    test = parseRString(infile);
    std::cout << test << std::endl;
    assert(test == "{ hannah { jiang } { } is really cool { } }");
    infile.close();
}

// testing the parser file
void pt5() {
    std::string test;

    std::ifstream infile;
   
    infile.open("test5.txt");
    infile.get();
    
    test = parseRString(infile);
    std::cout << test << std::endl;
    assert(test == "{ stationary.txt }");
    infile.close();
}

// testing the parser file
void pt6() {
    std::string test;

    std::ifstream infile;
   
    infile.open("test6.txt");
    infile.get();
    
    test = parseRString(infile);
    std::cout << test << std::endl;
    assert(test == "{ 1 1 + 2 / }");
    infile.close();
}

testing the parser fail function
void testParser_fail() {
    bool runtime_error = false;
    std::string error_message = "";

    std::string test;
    std::ifstream infile;
   
    infile.open("parserfail");
    infile.get();
    try {

        test = parseRString(infile);

    } catch (std::runtime_error &e) {
        runtime_error = true;
        error_message = e.what();
    }

    assert(error_message == "opener/closer doesn't match");
    infile.close();
}

// void RPNaddNum() {
//     RPNCalc calc;
//     calc.add_num(4);
//     assert(calc.stack.top().getInt() == 4);
// }

// void RPNgetInt() {
//     RPNCalc calc;
//     std::string numString = "12345";
//     int num;

//     calc.got_int(numString, &num);
//     assert(num = 12345);
// }

// void RPNaddBool_false() {
//     RPNCalc calc;
//     std::string boolTest = "#f";
//     calc.add_bool(boolTest);

//     assert(calc.stack.top().getBool() == false);
// }

// void RPNaddBool_true() {
//     RPNCalc calc;
//     std::string boolTest = "#t";
//     calc.add_bool(boolTest);

//     assert(calc.stack.top().getBool() == true);
// }

// void RPNdup() {
//     RPNCalc calc;
//     calc.add_num(4);
//     assert(calc.stack.top().getInt() == 4);

//     calc.dup();
//     calc.stack.pop();
//     assert(calc.stack.top().getInt() == 4);
// }

// void RPNboolOpp() {
//     RPNCalc calc;
//     std::string boolTest = "#t";
//     calc.add_bool(boolTest);

//     assert(calc.stack.top().getBool() == true);

//     calc.boolean_opp();

//     assert(calc.stack.top().getBool() == false);
// }

// void RPNswap() {
//     RPNCalc calc;
//     calc.add_num(4);
//     calc.add_num(6);

//     assert(calc.stack.top().getInt() == 6);
//     calc.swap();
//     assert(calc.stack.top().getInt() == 4);
//     calc.stack.pop();
//     assert(calc.stack.top().getInt() == 6);
// }

// void RPNmathAdd() {
//     RPNCalc calc;
//     calc.add_num(4);
//     calc.add_num(6);
//     std::string input = "+";

//     calc.math(input);
//     assert(calc.stack.top().getInt() == 10);
// }

// void RPNmathSub() {
//     RPNCalc calc;
//     calc.add_num(4);
//     calc.add_num(6);
//     std::string input = "-";

//     calc.math(input);
//     assert(calc.stack.top().getInt() == -2);
// }

// void RPNmathMul() {
//     RPNCalc calc;
//     calc.add_num(4);
//     calc.add_num(6);
//     std::string input = "*";

//     calc.math(input);
//     assert(calc.stack.top().getInt() == 24);
// }

// void RPNmathDiv() {
//     RPNCalc calc;
//     calc.add_num(8);
//     calc.add_num(4);
//     std::string input = "/";

//     calc.math(input);
//     assert(calc.stack.top().getInt() == 2);
// }

// void RPNmathMod() {
//     RPNCalc calc;
//     calc.add_num(6);
//     calc.add_num(6);
//     std::string input = "mod";

//     calc.math(input);
//     assert(calc.stack.top().getInt() == 0);
// }

// void RPNcompareLess() {
//     RPNCalc calc;
//     calc.add_num(4);
//     calc.add_num(6);
//     std::string input = "<";

//     calc.compare(input);
//     assert(calc.stack.top().getBool() == true);
// }