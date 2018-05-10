/*
 * 利用共享内存解决读写者问题
 * */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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
	if((*pshm).state==1){
	    sleep(1);
	    printf("Waiting...\n");
	}
	printf("[SEND]:");
	fgets((*pshm).text, LEN,stdin);
	(*pshm).state = 1;
	if(strcmp(((*pshm).text),"end\n")==0){
	    //set the end flag
	    break;
	}
    }
    printf("exit....\n");
    return 0;
}
