//
//  datatype.hpp
//  testfork
//
//  Created by @merouone on 1/13/18.
//  Copyright © 2018 MePro. All rights reserved.
//

#ifndef datatype
#define datatype
#include <time.h>
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

#endif /* datatype_hpp */
