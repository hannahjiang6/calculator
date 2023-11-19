/*
 *  DatumStack.h
 *  Hannah Jiang (hjiang03)
 *  2/22/2023
 *
 *  CS 15 PROJECT 2 CalcYouLater
 *
 *  FILE PURPOSE:
 *  This holds the DatumStack class. The class holds functions that
 *  make a stack data structure, but is implemented using and without
 *  #include <stack>. This class will allow Datum objects to be placed
 *  onto a DatumStack which will be maintained by these functions. All
 *  functions will be purposefully used to edit a stack.
 * 
 */


#ifndef __DATUMSTACK_H__
#define __DATUMSTACK_H__

#include <list>
#include "Datum.h"

class DatumStack {
public:

    DatumStack();
    DatumStack(Datum arr[], int size);

    Datum top();

    bool isEmpty();
    void clear();
    int size();

    void pop();
    void push(Datum Datum);

private:
    
    std::list<Datum> datum;

};

#endif
