//
//  datatypes.h
//  ptest
//
//  Created by mepro on 18/01/2019.
//  Copyright © 2019 mepro. All rights reserved.
//

#ifndef datatypes_h
#define datatypes_h

/**
 *  Min Max Value type holds a value (min or max) and it prosition in the array
 */
typedef struct {
    int value;
    int position;
} MaxMinVal;

/**
 *  Execution time structure to keep track of time that this program uses
 */
typedef struct {
    clock_t begin;
    clock_t end;
} ExecutionTime;

enum TIME_UNIT {TU_SECONDS = 1, TU_MILLISECONDS = 1000 , TU_MICROSECONDS = 1000000 };


#endif /* datatypes_h */
