//
//  main.c
//  ptest
//
//  Created by mepro on 18/01/2019.
//  Copyright © 2019 mepro. All rights reserved.
//

#include "parallelSorting.h"


int counter = 1;
extern int debug = 0;


int s_array[] = {6,4,2,9,12,};
int t_array[] = {5,1,3,5,-1,-12,6,30};

int s_array_size = sizeof(s_array)/sizeof(int);
int t_array_size = sizeof(t_array)/sizeof(int);




/**
 *  main function call
 */
int main(int argc, const char * argv[]) {
    // global array
    int st_array[ s_array_size + t_array_size ];
    ExecutionTime xTime;
    // begin counting time for execution
    xTime.begin = clock();
    
    int myPipeForS[2], myPipeForT[2];   // two pipes
    // prepare two pipes before the first fork
    if (pipe(myPipeForS) == -1 || pipe(myPipeForT) == -1) {
        printf("Error pipe creation parentPipeForS Or parentPipeForTLINE : %d",__LINE__);
        exit(EXIT_FAILURE);
    }
    
    printf("S in --------------\n");
    printArray(getpid(), s_array, s_array_size);
    
    printf("T in --------------\n");
    printArray(getpid(), t_array, t_array_size);
    //
    parallelSorting( s_array, t_array , s_array_size , t_array_size,myPipeForS,myPipeForT);
    //
    //partitionST( s_array, t_array , s_array_size , t_array_size,myPipeForS,myPipeForT);
    
    //
    int readS_ok = 0 ,readT_ok = 0;
    ssize_t reads , readt;
    while (!readS_ok || !readT_ok)
    {
        // read what childen process have written !!
        if(!readS_ok){
            if(read(myPipeForS[0], s_array, s_array_size * sizeof(int)) !=-1)
                readS_ok = 1;
            printf("S out --------------\n");
            printArray(getpid(), s_array, s_array_size);
        }
        //
        if(!readT_ok){
            if(read(myPipeForT[0], t_array, t_array_size * sizeof(int)) != -1)
                readT_ok = 1;
            printf("T out --------------\n");
            printArray(getpid(), t_array, t_array_size);
            
        }
        //printf(" readSok = %d , readTok = %d \n",readS_ok,readT_ok);
    }
    // one final array with
    printf("ST out --------------\n");
    recopyArray(s_array, st_array, 0, s_array_size);
    recopyArray(t_array, st_array, s_array_size, s_array_size + t_array_size);
    printArray(getpid(), st_array, s_array_size + t_array_size);
    
    if(close(myPipeForS[0]) == -1 || close(myPipeForS[1]) == -1 || close(myPipeForT[0]) == -1 || close(myPipeForT[1]) == -1){
        printf("!!!>>> Error closing myPipeForT[0] Or myPipeForT[1] LINE : %d ",__LINE__);
        exit(EXIT_FAILURE);
    }
    // end counting time for execution
    xTime.end = clock();
    
    printExecutionTime(xTime,TU_MILLISECONDS);
    
    
    
    return 0;
}
