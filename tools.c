//
//  tools.c
//  ptest
//
//  Created by mepro on 18/01/2019.
//  Copyright © 2019 mepro. All rights reserved.
//

#include "tools.h"

//#include "tools.h"

/**
 * max function
 */
MaxMinVal getMax(int *tab,int size)
{
    MaxMinVal max; // 0 => position 1=> value
    
    for( int i = 0 ; i<size; i++)
    {
        if( i == 0)
        {
            max.value = tab[i];
            max.position = 0;
        }
        
        if( i+1 < size)
        {
            if(tab[i+1] > max.value)
            {
                max.value = tab[i+1];
                max.position = i+1;
            }
        }
    }
    return max;
}

/**
 * min function
 */
MaxMinVal getMin(int *tab,int size)
{
    MaxMinVal min;
    for(int i=0 ; i<size; i++)
    {
        if( i == 0)
        {
            min.value = tab[i];
            min.position = 0;
        }
        
        if( i+1 < size)
        {
            if(tab[i+1] < min.value)
            {
                min.value = tab[i+1];
                min.position = i+1;
            }
        }
    }
    return min;
}

/**
 * copy and MaxMinVal
 */
MaxMinVal copyMaxMinVal(MaxMinVal *old){
    MaxMinVal copy;
    copy.position  = old->position;
    copy.value = old->value;
    return copy;
}

/**
 *  print the value of a MaxMin Object
 */
void printMaxMinVal(MaxMinVal *v){
    printf("MaxMinVal{Index = %d Value = %d}\n",v->position,v->value);
}

/**
 *  print the values of an array found in a process pid
 */
void printArray(pid_t pid , int * tab , int size)
{
    printf("\t \t \t \t[printArray] : ");
    for( int i = 0 ; i<size ; i++)
    {
        printf(" %d | \t",tab[i]);
    }
    printf("\n");
    
}
/**
 * copy from array to array
 */
void copyArray(int *source , int *destination ,int start, int copyLength){
    if(debug)
    {
        printf(" =========>> copy Array <<======== \n");
        for(int i = 0 ; i< copyLength - start; i++){
            destination[i] = source[i + start];
            printf("copying %d in poisition i %d from j position %d \n",source[i + start],i,i + start);
        }
        printf(" <<========= copy Array ========>> \n");
    }else{
        for(int i = 0 ; i< copyLength - start; i++){
            destination[i] = source[i + start];
        }
    }
}

/**
 * recopy from array to array
 */
void recopyArray(int *source , int *destination ,int start, int copyLength){
    if(debug){
        printf(" =========>> copy Array <<======== \n");
        
        for(int i = 0 ; i< copyLength - start; i++){
            destination[i + start] = source[i];
            printf("copying %d in poisition i %d from j position %d \n",source[i + start],i,i + start);
        }
        printf(" <<========= copy Array ========>> \n");
    }else{
        for(int i = 0 ; i< copyLength - start; i++){
            destination[i + start] = source[i];
        }
    }
}

/**
 * permutate a value identified by an index in an array
 */
void permutate(int * tab, int index , int newVal)
{
    tab[index] = newVal;
}

/**
 *
 */
void permutate2(int * tab, int size, int index , int newVal)
{
    
    tab[index] = newVal;
    if(debug)
    {
        printf(" =========>> permutate Array <<======== \n");
        printArray(getpid(), tab , size);
        printf(" <<========= permutate Array ========>> \n");
    }
}


void printExecutionTime(ExecutionTime t , int unit)
{
    double time_spent = (double)((t.end - t.begin) * (double)unit ) / CLOCKS_PER_SEC;
    printf("___________________________________________________\n");
    printf("|\t \t \t \t[Execution Time]\n");
    switch (unit)
    {
        case TU_SECONDS:
            printf("| \t Time execution %f  SECONDS \n",time_spent);
            break;
        case TU_MICROSECONDS :
            printf("| \t Time execution %f  MICROSECONDS \n",time_spent);
            break;
        case TU_MILLISECONDS:
            printf("| \t Time execution %f  MILLISECONDS \n",time_spent);
            break;
        default:
            break;
    }
    printf("|__________________________________________________\n\n");
    
    
}


//#endif /* tools_h */
