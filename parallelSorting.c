//
//  parallelSorting.c
//  ptest
//
//  Created by mepro on 19/01/2019.
//  Copyright © 2019 mepro. All rights reserved.
//

#include "parallelSorting.h"

//#include "tools.h"

/**
 *  Parallel Sorting of two arrays S and T
 */
void parallelSorting(int *s,int *t, int s_size , int t_size, int *parentPipeForS , int *parentPipeForT)
{
    if(debug){
        printf(">>************************** parallelSorting = [%d] ************************** \n",getpid() );
        printArray(getpid(), s, s_size);
        printArray(getpid(), t, t_size);
        printf("<<************************** parallelSorting = [%d] ************************** \n\n\n",getpid() );
    }
    
    int myPipeForS[2], myPipeForT[2];   // two pipes
    // prepare two pipes before the first fork
    if (pipe(myPipeForS) == -1 || pipe(myPipeForT) == -1) {
        printf("Error pipe creation parentPipeForS Or parentPipeForTLINE : %d",__LINE__);
        exit(EXIT_FAILURE);
    }
    
    partitionST( s, t , s_size , t_size , myPipeForS , myPipeForT);
    
    int readS_ok = 0 ,readT_ok = 0;
    ssize_t reads , readt;
    
    while (!readS_ok || !readT_ok)
    {
        // read what childen process have written !!
        if(!readS_ok){
            if(read(myPipeForS[0], s, s_size * sizeof(int)) != -1)
                readS_ok = 1;
        }
        //
        if(!readT_ok){
            if(read(myPipeForT[0], t, t_size * sizeof(int)) != -1)
                readT_ok = 1;
        }
    }
    
    // for s
    if( s_size > 1)
    {
        int childPipeForS[2], childPipeForT[2];   // two pipes
        int new_s_size = (s_size / 2) + (s_size % 2);
        int new_t_size = s_size / 2;
        int new_s[new_s_size];
        int new_t[new_t_size];
        
        if (pipe(childPipeForS) == -1 || pipe(childPipeForT) == -1) {
            printf("Error pipe creation parentPipeForS Or parentPipeForTLINE : %d",__LINE__);
            exit(EXIT_FAILURE);
        }
        
        copyArray(s, new_s, 0, new_s_size);
        copyArray(s, new_t, new_s_size, s_size);
        parallelSorting( new_s, new_t , new_s_size , new_t_size ,childPipeForS, childPipeForT);
        
        int readS_ok = 0 ,readT_ok = 0;
        ssize_t reads , readt;
        
        while (!readS_ok || !readT_ok)
        {
            // read what childen process have written !!
            if(!readS_ok){
                if(read(childPipeForS[0], new_s, new_s_size * sizeof(int)) !=-1){
                    readS_ok = 1;
                }
            }
            if(!readT_ok){
                if(read(childPipeForT[0], new_t, new_t_size * sizeof(int)) != -1){
                    readT_ok = 1;
                }
            }
            //printf(" readSok = %d , readTok = %d \n",readS_ok,readT_ok);
        }
        
        if(debug){
            printf("***************************WRITE**************************************\n");
            printArray(getpid(), s, s_size);
            printArray(getpid(), new_s, new_s_size);
            printArray(getpid(), new_t, new_t_size);
            printArray(getpid(), s, s_size);
            printf("***************************WRITE**************************************\n");
        }
        recopyArray(new_s, s, 0, new_s_size);
        recopyArray(new_t, s, new_s_size, s_size);
        
        if( write(myPipeForS[1], s, sizeof(int) * s_size) == -1){
            printf("!!!>>> Error writing in myPipeForS[1] LINE : %d \n",__LINE__);
            exit(EXIT_FAILURE);
        }
        
        if(
           close(childPipeForS[0]) == -1 || close(childPipeForS[1]) == -1 ||
           close(childPipeForT[0]) == -1 || close(childPipeForT[1]) == -1
           ){
            printf("!!!>>> Error closing myPipeForT[0] Or myPipeForT[1] LINE : %d ",__LINE__);
            exit(EXIT_FAILURE);
        }
        
        //
    }
    // for t
    if( t_size > 1)
    {
        int childPipeForS[2], childPipeForT[2];   // two pipes
        int new_s_size = (t_size / 2) + (t_size % 2);
        int new_t_size = t_size / 2;
        int new_s[new_s_size];
        int new_t[new_t_size];
        
        if (pipe(childPipeForS) == -1 || pipe(childPipeForT) == -1) {
            printf("Error pipe creation parentPipeForS Or parentPipeForTLINE : %d",__LINE__);
            exit(EXIT_FAILURE);
        }
        
        copyArray(t, new_s, 0, new_s_size);
        copyArray(t, new_t, new_s_size, t_size);
        parallelSorting(new_s, new_t, new_s_size, new_t_size, childPipeForS, childPipeForT);
        
        int readS_ok = 0 ,readT_ok = 0;
        ssize_t reads , readt;
        
        while (!readS_ok || !readT_ok)
        {
            // read what childen process have written !!
            if(!readS_ok){
                if(read(childPipeForS[0], new_s, new_s_size * sizeof(int)) !=-1){
                    readS_ok = 1;
                }
            }
            if(!readT_ok){
                if(read(childPipeForT[0], new_t, new_t_size * sizeof(int)) != -1){
                    readT_ok = 1;
                }
            }
            //printf(" readSok = %d , readTok = %d \n",readS_ok,readT_ok);
        }
        
        recopyArray(new_s, t, 0, new_s_size);
        recopyArray(new_t, t, new_s_size, t_size);
        
        if( write(parentPipeForT[1], t, sizeof(int) * t_size) == -1){
            printf("!!!>>> Error writing in myPipeForS[1] LINE : %d \n",__LINE__);
            exit(EXIT_FAILURE);
        }
        
        
    }
    
    
    if( write(parentPipeForS[1], s, sizeof(int) * s_size) == -1){
        printf("!!!>>> Error writing in myPipeForS[1] LINE : %d \n",__LINE__);
        exit(EXIT_FAILURE);
    }
    
    if( write(parentPipeForT[1], t, sizeof(int) * t_size) == -1){
        printf("!!!>>> Error writing in myPipeForS[1] LINE : %d \n",__LINE__);
        exit(EXIT_FAILURE);
    }
    
    
    if(
       close(myPipeForS[0]) == -1 || close(myPipeForS[1]) == -1 ||
       close(myPipeForT[0]) == -1 || close(myPipeForT[1]) == -1)
    {
        printf("!!!>>> Error closing myPipeForT[0] Or myPipeForT[1] LINE : %d ",__LINE__);
        exit(EXIT_FAILURE);
    }
    
}
