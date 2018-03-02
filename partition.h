//
//  partition.h
//  testfork
//
//  Created by @merouone on 1/14/18.
//  Copyright © 2018 MePro. All rights reserved.
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
 *  partition of two Arrays S and T
 */
/**
 *  partition of two Arrays S and T
 */
void  partitionST(int *s,int *t, int s_size , int t_size, int parentPipeForS[2] , int parentPipeForT[2])
{
    
    if(debug){
        printf(">>========================= PartitionSTPID = [%d] ========================= \n",getpid());
        printArray(getpid(), s, s_size);
        printArray(getpid(), t, t_size);
    }
    
    pid_t pS , pT;                      // two process ids
    int myPipeForS[2], myPipeForT[2];   // two pipes
    // prepare two pipes before the first fork
    if (pipe(myPipeForS) == -1 || pipe(myPipeForT) == -1) {
        printf("Error pipe creation parentPipeForS Or parentPipeForTLINE : %d",__LINE__);
        exit(EXIT_FAILURE);
    }
    pS = fork();
    // first process
    switch (pS)
    {
        case 0:
            //printArray(getpid(), s, s_size);
            //
            if( close(myPipeForS[0]) == -1 || close(myPipeForT[1]) == -1){ //
                printf("Error closing pipes myPipeForT[0] or myPipeForS[1] LINE : %d\n",__LINE__);
                exit(EXIT_FAILURE);
            }
            // exchange with the other process
            MaxMinVal previousMax;
            MaxMinVal previousMin;
            for ( ; ; )
            {
                MaxMinVal max;
                MaxMinVal min;
                max = getMax(s,s_size);
                //
                if( write(myPipeForS[1], &max, sizeof(MaxMinVal)) == -1){
                    printf("!!!>>> Error writing in myPipeForS[1] LINE : %d \n",__LINE__);
                    exit(EXIT_FAILURE);
                }
                else{
                    if (debug)
                        printf(" S is writing in myPipeForS[1] %d LINE : %d \n",max.value,__LINE__);
                }
                
                if( read(myPipeForT[0], &min,sizeof(MaxMinVal)) == -1){
                    printf("!!!>>> Error reading in myPipeForT[0] LINE : %d \n",__LINE__);
                    exit(EXIT_FAILURE);
                }
                else{
                    if(debug)
                        printf("S is reading from myPipeForT[0] %d LINE : %d \n ",min.value,__LINE__);
                }
               
                if(max.value <= min.value)
                    //                if(
                    //                   previousMax.value == min.value &&
                    //                   previousMin.value == max.value
                    //                   )
                {
                    // write to parent pipe the result after partition
                    if( write(parentPipeForS[1], s, sizeof(int) * s_size) == -1){
                        printf("!!!>>> Error writing in myPipeForS[1] LINE : %d \n",__LINE__);
                        exit(EXIT_FAILURE);
                    }
                    // go out of the loop
                    break;
                }
                // just continue and what you need to do
                permutate2(s,s_size,max.position,min.value);
                // keep a copy
                previousMin = copyMaxMinVal(&min);
                previousMax = copyMaxMinVal(&max);
                
            }
            
            exit(0);
            break;
        case -1:
            printf("Error %d\n",__LINE__);
            break;
        default:
        {   // second process
            pT = fork();
            if(pT == 0) // this process
            {
                // printArray(getpid(), t, t_size);
                //
                if( close(myPipeForT[0]) == -1 || close(myPipeForS[1]) == -1){ //
                    printf("Error closing pipes myPipeForT[0] or myPipeForS[1] LINE : %d\n",__LINE__);
                    exit(EXIT_FAILURE);
                }
                // init a previous value
                MaxMinVal previousMax;
                MaxMinVal previousMin;
                for ( ; ; )
                {
                    MaxMinVal max;
                    MaxMinVal min;
                    min = getMin(t,t_size);
                    
                    if( read(myPipeForS[0], &max,sizeof(MaxMinVal)) == -1){
                        printf("!!!>>> Error reading in myPipeForS[0] LINE : %d \n",__LINE__);
                        exit(EXIT_FAILURE);
                    }
                    else{
                        if(debug)
                            printf(" T is reading from myPipeForS[0] %d LINE : %d \n",max.value,__LINE__);
                    }
                    
                    if( write(myPipeForT[1], &min, sizeof(MaxMinVal)) == -1){
                        printf("!!!>>> Error writing in myPipeForT[1] LINE : %d \n",__LINE__);
                        exit(EXIT_FAILURE);
                    }
                    else{
                        if(debug)
                            printf(" T is writing in myPipeForT[1] %d LINE : %d \n",min.value,__LINE__);
                    }
                    if(min.value >= max.value)
                    {
                        if( write(parentPipeForT[1], t, sizeof(int) * t_size) == -1){
                            printf("!!!>>> Error writing in myPipeForS[1] LINE : %d \n",__LINE__);
                            exit(EXIT_FAILURE);
                        }
                        break;
                    }
                    
                    permutate2(t,t_size,min.position,max.value);
                    // keep a copy
                    previousMin = copyMaxMinVal(&min);
                    previousMax = copyMaxMinVal(&max);
                }
                
                exit(0);
            }else if(pT < 0)
                printf("Error %d",__LINE__);
            
        }
    }
    // close my pipes
    if(close(myPipeForS[0]) == -1 || close(myPipeForS[1]) == -1 ){
        printf("!!!>>> Error closing myPipeForT[0] Or myPipeForT[1] LINE : %d ",__LINE__);
        exit(EXIT_FAILURE);
    }
    // close my pipes
    if(close(myPipeForT[0]) == -1 || close(myPipeForT[1]) == -1){
        printf("!!!>>> Error closing myPipeForT[0] Or myPipeForT[0] LINE : %d ",__LINE__);
        exit(EXIT_FAILURE);
    }
    
    
}


#endif /* partition_h */
