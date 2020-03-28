#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t lock;

int main()
{
    int tables[7] = {0,0,0,0,0,0,0}, wait[7] = {15,10,10,5,0,0,0}, queue[4] = {0,0,0,0};
    //queue can only be filled by 4-people groups, since at least 1 of 2-people table would be refilled by the time the next 2-people group arrives .
    int i,q,token,overtake = 0;
    int num = 20;
    srand(time(NULL));
    for(i=0;i<num;i++){
        
        //If none is waitting in the queue
        if(overtake == 0){token = rand()%3;}
        
        
        //1-person "group"
        if(token == 0){
            pthread_mutex_lock(&lock);
            tables[3] = 1;
            pthread_mutex_unlock(&lock);
}
    
        //2-people group
        else if(token == 1){ 
            pthread_mutex_lock(&lock);
            if(tables[1] != 1){
                tables[1] = 1;
            }else if(tables[2] != 1){
                tables[2] = 1;}
                pthread_mutex_unlock(&lock);
        }
       
        //4-people group    
        else if(token == 2){ 
            pthread_mutex_lock(&lock);
            if(tables[0]!=1){
                tables[0] = 1;
            }else{
                //Simulate queue of 4-people groups
                for(q=0;q<4;q++){
                    if(queue[q] == 0){queue[q] = 15;}
                    break;
                }
            }
            pthread_mutex_unlock(&lock);
        }
        //show//////////////////////////////////////////////////////
        if(token == 0){printf("num customer 1\n");}
        else if(token == 1){printf("num customer 2\n");}
        else if(token == 2){printf("num customer 4\n");}
        for(q=0;q<7;q++){printf(" %d", tables[q]);}
        printf("\n");
        for(q=0;q<7;q++){printf(" %d", wait[q]);}
        printf("\n");
        printf("The queue :");
        for(q=0;q<4;q++){printf(" %d", queue[q]);}
        printf("\n");
        ////////////////////////////////////////////////////////////
        
        //wait(5);
        for(q=0;q<4;q++){
            if(tables[q] == 1){
              wait[q] = wait[q] - 5;  
            } 
        }
        //decrease queue
        for(q=0;q<4;q++){
            if(queue[q] != 0){
                queue[q] = queue[q] - 5;
                //if the person already served time in the queue. 
                if(queue[q] == 0){overtake = 1;}
            }
        }
	    //show/////////////////////////////////////////////////////
        printf("After 5 mins\n");
        for(q=0;q<7;q++){printf(" %d", wait[q]);}
        printf("\n----------------------------------------------------------------------------\n");
	    for(q=0;q<4;q++){
            if(wait[q] == 0){
                if(q==0){wait[0] = 15;}
                if(q==1){wait[1] = 10;}
                if(q==2){wait[2] = 10;}
                if(q==3){wait[3] = 5;}
                tables[q] = 0;
            }
        }
        /////////////////////////////////////////////////////////
    }
    return 0;
}