//
//  tools.h
//  ptest
//
//  Created by mepro on 18/01/2019.
//  Copyright © 2019 mepro. All rights reserved.
//

#ifndef tools_h
#define tools_h

#include <stdio.h>
#include <time.h>
#include "datatypes.h"

static int debug;

/**
 * max function
 */
MaxMinVal getMax(int *tab,int size);
/**
 * min function
 */
MaxMinVal getMin(int *tab,int size);
/**
 * copy and MaxMinVal
 */
MaxMinVal copyMaxMinVal(MaxMinVal *old);
/**
 *  print the value of a MaxMin Object
 */
void printMaxMinVal(MaxMinVal *v);
/**
 *  print the values of an array found in a process pid
 */
void printArray(pid_t pid , int * tab , int size);
/**
 * copy from array to array
 */
void copyArray(int *source , int *destination ,int start, int copyLength);
/**
 * recopy from array to array
 */
void recopyArray(int *source , int *destination ,int start, int copyLength);
/**
 * permutate a value identified by an index in an array
 */
void permutate(int * tab, int index , int newVal);
/**
 * Permutate 2
 */
void permutate2(int * tab, int size, int index , int newVal);
/**
 * Print the time of execution 
 */
void printExecutionTime(ExecutionTime t , int unit);

#endif /* tools_h */
