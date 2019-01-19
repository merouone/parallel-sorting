//
//  partition.h
//  ptest
//
//  Created by mepro on 18/01/2019.
//  Copyright © 2019 mepro. All rights reserved.
//

#ifndef partition_h
#define partition_h
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>

#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "tools.h"
/**
 * partition an array
 * *s input array
 * *t input array
 * s_size
 * t_size
 * parent_pipe dedicated for s
 * parent_pipe dedicated for t
 */
void  partitionST(int *s,int *t, int s_size , int t_size, int parentPipeForS[2] , int parentPipeForT[2]);
#endif /* partition_h */
