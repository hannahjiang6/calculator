/*
 *  parser.cpp
 *  Hannah Jiang (hjiang03)
 *  2/22/2023
 *
 *  CS 15 PROJECT 2 CalcYouLater
 *
 *  FILE PURPOSE:
 *  Implementation of the parseRString function
 *
 */

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "parser.h"

/*
 * name:      parseRString 
 * purpose:   reads in the input from the file and creates a
 *            string with the input. throws an exception if the file
 *            input is invalid.
 * arguments: istream &input
 * returns:   string
 */
std::string parseRString(std::istream &input) {
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