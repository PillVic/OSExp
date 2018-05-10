/*
 * 利用共享内存解决读写者问题
 * */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<unistd.h>
#include"block.h"

int main(){
    //Initial 
    int shmid = shmget((key_t)1234, sizeof(block), 0666|IPC_CREAT);
    if(shmid==-1){
	perror("shmget error!\n");
	exit(EXIT_FAILURE);
    }
    block *pshm = shmat(shmid, 0, 0);
    if(pshm==(void*)-1){
	perror("shmat failed!\n");
	exit(EXIT_FAILURE);
    }
    printf("Shared Memory ID :[%d]\n", shmid);
    (*pshm).state = 0;
    //work
    while(1){
	if((*pshm).state==0){
	    sleep(1);
	    printf("Waiting...\n");
	}
	if((*pshm).text[0]!=0){
	    printf("[GET]:%s",(*pshm).text);
	    (*pshm).state = 0;
	    if(strcmp(((*pshm).text),"end\n")==0){
		//set the end flag
		break;
	    }
	    (*pshm).text[0] = 0;
	}else{
	    sleep(1);
	}
    }
    printf("exit....\n");
    return 0;
}
