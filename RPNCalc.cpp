/*
 *  RPNCalc.cpp
 *  Hannah Jiang (hjiang03)
 *  2/22/2023
 *
 *  CS 15 PROJECT 2 CalcYouLater
 *
 *  FILE PURPOSE:
 *  Holds all the necessary functions that are able
 *  to be used in the CalcYouLater. It's the implementation
 *  of RPNCalc class. It holds the run function that runs the entire
 *  CalcYouLater implementation. It has all the files that are
 *  necessary for this class to run.
 *
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>

#include "RPNCalc.h"

/*
 * name:      RPNCalc 
 * purpose:   constructs the game/initializes the RPNCalc object
 * arguments: none
 * returns:   none
 */
RPNCalc::RPNCalc() {
    stack.clear();
}

/*
 * name:      ~RPNCalc 
 * purpose:   deletes all the heap-allocated data
 * arguments: none
 * returns:   none
 */
RPNCalc::~RPNCalc() {}

/*
 * name:      run 
 * purpose:   reads in commands and throws runtime_error messages
 * arguments: none
 * returns:   none
 */
void RPNCalc::run() {
    bool run = true;
    
    while (run) {
        try {
            bool b = query(std::cin);
            if (b == true) {
                run = false;
            }
        } catch (std::runtime_error &e) {
            // catches all the run_time error messages and pops the top two
            // Datum objects off the stack
            if (stack.size() >= 2) { stack.pop(); stack.pop(); } 
            else { stack.clear(); }

            std::string error_message = e.what();  
            std::cerr << "Error: " << error_message << "\n";
        }
    }
}

/*
 * name:      query 
 * purpose:   reads in input from a stream and carries out commands
 *            also returns a bool for when exiting the game
 * arguments: std::istream &input
 * returns:   bool
 */
bool RPNCalc::query(std::istream &input) {
    std::string command;
    int num;
    input >> command;

    if (got_int(command, &num)) { add_num(num); } 
    else if (isBool(command)) { add_bool(command); }
    else if (isMath(command)) { math(command); }
    else if (isCompare(command)) { compare(command); }
    else if (command == "dup") { dup(); }
    else if (command == "{") { 
        std::string rstring = parseRString(input); 
        Datum new_datum(rstring);
        stack.push(new_datum);
    } 
    else if (command == "exec") { exec(); }
    else if (command == "file") { file(); }
    else if (command == "if") { ifCommand(); }
    else if (command == "swap") { swap(); }
    else if (command == "clear") { stack.clear(); }
    else if (command == "drop") { stack.pop(); }
    else if (command == "not") { boolean_opp(); }
    else if (command == "print") { print(); }
    else if (command == "" or command == "\n") { return false; }
    else if (command == "quit" or input.eof()) { 
        std::cerr << "Thank you for using CalcYouLater.\n";
        return true;
    } else {
        std::cerr << command << ": unimplemented\n";
    }
    return false;
}

/*
 * name:      add_num 
 * purpose:   adds a number Datum to the stack
 * arguments: std::string input
 * returns:   none
 */
void RPNCalc::add_num(int num) {
    Datum new_datum(num);
    stack.push(new_datum);
}

/*
 * name:      got_int 
 * purpose:   returns a bool if the string provided is an integer
 *            as well as returning it as an int
 * arguments: std::string s, int *resultp
 * returns:   bool
 */
bool RPNCalc::got_int(std::string s, int *resultp) {
    /* Holds the first non-whitespace character after the integer */
    char extra;

    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/*
 * name:      add_bool 
 * purpose:   adds a bool Datum to the stack
 * arguments: std::string input
 * returns:   none
 */
void RPNCalc::add_bool(std::string input) {
    if (input == "#t") {
        Datum new_datum(true);
        stack.push(new_datum);
    } else {
        Datum new_datum(false);
        stack.push(new_datum);
    }
}

/*
 * name:      math 
 * purpose:   does the math calculation depending on the inputted
 *            operand command and then pushes a datum holding
 *            the new number to the stack
 * arguments: std::string input
 * returns:   none
 */
void RPNCalc::math(std::string input) {
    int num = stack.top().getInt();
    stack.pop();
    int num2 = stack.top().getInt();
    stack.pop();
    if (input == "+") {
        num = num2 + num;
        add_num(num);
    } else if (input == "-") {
        num = num2 - num;
        add_num(num);
    } else if (input == "*") {
        num = num2 * num;
        add_num(num);
    } else if (input == "/" or "mod") {
        if (num == 0) {
            std::cerr << "Error: division by 0\n";
        } else if (input == "/") {
            num = num2 / num;
            add_num(num);
        } else {
            num = num2 % num;
            add_num(num);
        }
    } 
}

/*
 * name:      compare 
 * purpose:   compares two number Datums and returns a boolean Datum
 *            depending on whether the result was true or false
 *            to the Datum stack
 * arguments: std::string input
 * returns:   none
 */
void RPNCalc::compare(std::string input) {
    int num = stack.top().getInt();
    stack.pop();
    int num2 = stack.top().getInt();
    stack.pop();
    if (input == "<") {
        if (num2 < num) { 
            Datum new_datum(true); stack.push(new_datum); 
        } else { Datum new_datum(false); stack.push(new_datum); }
    } else if (input == ">") {
        if (num2 > num) { 
            Datum new_datum(true); stack.push(new_datum); 
        } else { Datum new_datum(false); stack.push(new_datum); }
    } else if (input == "<=") {
        if (num2 <= num) { 
            Datum new_datum(true); stack.push(new_datum);
        } else { Datum new_datum(false); stack.push(new_datum); }
    } else if (input == ">=") {
        if (num2 >= num) { 
            Datum new_datum(true); stack.push(new_datum); 
        } else { Datum new_datum(false); stack.push(new_datum); }
    } else if (input == "==") {
        if (num2 == num) { 
            Datum new_datum(true); stack.push(new_datum); 
        } else { Datum new_datum(false); stack.push(new_datum); }
    } 
}

/*
 * name:      isBool 
 * purpose:   checks whether the inputted command was a bool
 * arguments: std::string input
 * returns:   boolean
 */
bool RPNCalc::isBool(std::string input) {
    if (input == "#f" or input == "#t") {
        return true;
    }
    return false;
}

/*
 * name:      isNum 
 * purpose:   checks whether the inputted command was a math operand
 * arguments: std::string input
 * returns:   boolean
 */
bool RPNCalc::isMath(std::string input) {
    if (input == "+" or input == "-" or input == "*" or
        input == "/" or input == "mod") {
        return true;
    }
    return false;
}

/*
 * name:      isCompare 
 * purpose:   checks whether the inputted command was a comparison operand
 * arguments: std::string input
 * returns:   boolean
 */
bool RPNCalc::isCompare(std::string input) {
    if (input == ">" or input == "<" or input == "<=" or 
        input == ">=" or input == "==") {
        return true;
    }
    return false;
}

/*
 * name:      print 
 * purpose:   prints the top Datum's data
 * arguments: none
 * returns:   none
 */
void RPNCalc::print() {
    if (stack.top().isInt() == true) {
        // prints the number value
        std::cout << stack.top().getInt() << std::endl;
    } else if (stack.top().isBool() == true) {
        // get the boolean value and print depending on value
        if (stack.top().getBool() == true) {
            std::cout << "#t" << std::endl;
        } else {
            std::cout << "#f" << std::endl;
        }
    } else if (stack.top().isRString() == true) {
        // prints the RString data
        std::cout << stack.top().getRString() << std::endl;
    }
}

/*
 * name:      dup 
 * purpose:   duplicates the top datum
 * arguments: none
 * returns:   none
 */
void RPNCalc::dup() {
    // duplicates the first Datum
    Datum datum(stack.top());
    stack.push(datum);
}

/*
 * name:      boolean_opp 
 * purpose:   adds a Datum containing the opposite boolean value of the
 *            boolean datum at the top of the stack
 * arguments: none
 * returns:   none
 */
void RPNCalc::boolean_opp() {
    bool b = stack.top().getBool();
    stack.pop();
    // adds the opposite boolean Datum depending on the current boolean Datum
    if (b == true) {
        Datum new_datum(false);
        stack.push(new_datum);
    } else {
        Datum new_datum(true);
        stack.push(new_datum);
    }
}

/*
 * name:      exec 
 * purpose:   takes an rstring and processes its contents 
 *            as a sequence of commands. Throws an exception if
 *            not an rstring
 * arguments: none
 * returns:   none
 */
void RPNCalc::exec() {
    if (stack.top().isRString() == true) {
        std::string rstring = stack.top().getRString();
        stack.pop();
        std::string new_string = readRString(rstring);
        std::stringstream input(new_string);

        while (not input.eof()) {
            query(input);
        }

    } else { 
        std::cerr << "cannot execute non rstring\n";
    }
}

/*
 * name:      file 
 * purpose:   takes an rstring and processes the filename. Afterwards 
 *            it reads in the file's contents as a sequence of commands. 
 * arguments: none
 * returns:   none
 */
void RPNCalc::file() {
    Datum rstring(stack.top());
    stack.pop();
    if (rstring.isRString()) {
        std::string rstringData = rstring.getRString();
        std::string filename = readRString(rstringData);
        std::string input;

        // opening the file
        std::ifstream file(filename);
        if (not file) {
            std::cerr << "Unable to read " << filename << "\n";
        } else {
            // sends in the input stream for the query function
            while (not file.eof()) {
                try {
                    query(file); 
                } catch (std::runtime_error &e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
            }
            // closes the file after the end
            file.close();
        }
    } else {
        std::cerr << "Error: file operand not rstring\n";
    }
}

/*
 * name:      ifCommand 
 * purpose:   executes different rstrings depending on the bool condition
 * arguments: none
 * returns:   none
 */
void RPNCalc::ifCommand() {
    Datum rstring1(stack.top());
    stack.pop();
    Datum rstring2(stack.top());
    stack.pop();
    Datum testCase(stack.top());
    stack.pop();

    bool b = false;

    if (testCase.isBool()) {
        b = testCase.getBool();
        if (rstring1.isRString() and rstring2.isRString()) {
            if (b) {
                stack.push(rstring2);
                exec();
            } else {
                stack.push(rstring1);
                exec();
            }
        } else {
            std::cerr << "Error: expected rstring in if branch\n";
        }
    } else {
        std::cerr << "Error: expected boolean in if test\n";
    }
}

/*
 * name:      readRString 
 * purpose:   returns an RString without the brackets around it
 * arguments: std::string input
 * returns:   string
 */
std::string RPNCalc::readRString(std::string input) {
    return (input.substr(2, input.length()-4));
}

/*
 * name:      swap 
 * purpose:   swaps the top two Datums on the stack
 * arguments: none
 * returns:   none
 */
void RPNCalc::swap() {
    // puts the first datum in the stack into a temp datum
    Datum datum1(stack.top());
    stack.pop();

    // puts the second datum in the stack into a temp datum
    Datum datum2(stack.top());
    stack.pop();

    // adds both datums back but in reverse (swap)
    stack.push(datum1);
    stack.push(datum2);
}

/*
 * name:      parseRString 
 * purpose:   reads in the input from the file and creates a
 *            string with the input. throws an exception if the file
 *            input is invalid.
 * arguments: istream &input
 * returns:   string
 */
std::string RPNCalc::parseRString(std::istream &input) {
    // declaring variables
    std::stringstream ss;
    std::string i;
    // counters for the brackets
    int closer = 0;
    int opener = 1;

    ss << "{ ";
    // run while not end of file
    while (not input.eof()) {
        input >> i;
        // if encounter a bracket format certain way
        if (i == "{") { 
            opener++; 
        } else if (i == "}") { 
            closer++; 
            // only return string if the closer == opener brackets
            if (closer == opener) {
                ss << i;
                return ss.str();
            }
        }
        ss << i << " "; 
    }
    // throws an error if closer/opener doesn't match
    throw std::runtime_error("opener/closer doesn't match");
}