/*
 *  DatumStack.cpp
 *  Hannah Jiang (hjiang03)
 *  2/22/2023
 *
 *  CS 15 PROJECT 2 CalcYouLater
 *
 *  FILE PURPOSE:
 *  This file holds the DatumStack functions. The functions will be
 *  used in implementing the RPNCalc files. These functions are made
 *  to create a working stack data structure without using 
 *  the pre-made #include <stack>. With using the #include <list> the
 *  DatumStack was easily implemnted and only holds necessary functions
 *  that will be used in the RPNCalc.cpp.
 *
 */

#include <iostream>
#include <list>
#include <stdexcept>

#include "DatumStack.h"

/*
 * name:      DatumStack
 * purpose:   default constructor that initializes an empty stack
 * arguments: none
 * returns:   none
 */
DatumStack::DatumStack() {

}

/*
 * name:      DatumStack
 * purpose:   array constructor that initializes a stack of int size
 * arguments: Datum arr[], int size
 * returns:   none
 */
DatumStack::DatumStack(Datum arr[], int size) {
    for (int i = 0; i < size; i++) {
        datum.push_front(arr[i]);
    }
}

/*
 * name:      top
 * purpose:   returns the top element of the stack and throws an error
 *            if the stack is empty
 * arguments: none
 * returns:   Datum
 */
Datum DatumStack::top() {
    if (datum.size() <= 0) {
        throw std::runtime_error("empty_stack");
    }
    return datum.front();
}

/*
 * name:      isEmpty
 * purpose:   returns a bool if the stack is empty
 * arguments: none
 * returns:   bool
 */
bool DatumStack::isEmpty() {
    if (datum.size() == 0) {
        return true;
    }
    return false;
}  

/*
 * name:      clear
 * purpose:   clears the entire stack and stack becomes empty
 * arguments: none
 * returns:   none
 */
void DatumStack::clear() {
    datum.clear();
}

/*
 * name:      size
 * purpose:   returns the num of Datum in the stack
 * arguments: none
 * returns:   int
 */
int DatumStack::size() {
    return datum.size();
}
    
/*
 * name:      pop
 * purpose:   removes the first element in the stack and throw an error
 *            if the stack is empty
 * arguments: none
 * returns:   none
 */
void DatumStack::pop() {
    if (datum.size() <= 0) {
        throw std::runtime_error("empty_stack");
    }
    datum.pop_front();
}

/*
 * name:      push
 * purpose:   pushs a Datum onto the front of the stack
 * arguments: none
 * returns:   none
 */
void DatumStack::push(Datum Datum) {
    datum.push_front(Datum);
}