/*
 *  RPNCalc.h
 *  Hannah Jiang (hjiang03)
 *  2/22/2023
 *
 *  CS 15 PROJECT 2 CalcYouLater
 *
 *  FILE PURPOSE:
 *  Interface for the RPNCalc class. It includes all the functions
 *  that will be used in the RPNCalc.cpp file, as well as, the
 *  other files that will be used. Most functions are private to
 *  only allow select functions for users to access.
 *
 */


#ifndef __RPNCALC_H__
#define __RPNCALC_H__

#include <iostream>
#include "DatumStack.h"

class RPNCalc {
public:

    // Constructor
    RPNCalc();

    // Destructor
    ~RPNCalc();

    // run's the RPNCalc
    void run();

private:

    // query function
    bool query(std::istream &command);
    
    // functions that add a Datum object to DatumStack
    void add_num(int num);
    void add_bool(std::string input);

    // functions that edit the DatumStack
    void dup();
    void boolean_opp();
    void swap();
    void math(std::string input);
    void compare(std::string input);
    void exec();
    void file();
    void ifCommand();
    
    // String functions that read/add an RString
    std::string readRString(std::string input);
    std::string parseRString(std::istream &input);

    bool got_int(std::string s, int *resultp);
    void print();

    // Checks whether or not commands are valid
    bool isBool(std::string input);
    bool isMath(std::string input);
    bool isCompare(std::string input);

    DatumStack stack;

};

#endif
