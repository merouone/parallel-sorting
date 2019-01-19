//
//  parallelSorting.h
//  ptest
//
//  Created by mepro on 19/01/2019.
//  Copyright © 2019 mepro. All rights reserved.
//

#ifndef parallelSorting_h
#define parallelSorting_h

#include <stdio.h>
#include "partition.h"


/**
 *  Parallel Sorting of two arrays S and T
 */
void parallelSorting(int *s,int *t, int s_size , int t_size, int *parentPipeForS , int *parentPipeForT);
#endif /* parallelSorting_h */
