/* *实现进程的创建、撤销和CPU切换*/
/*
 * 子线程计算斐波那契数列
 * 主线程提供用于查询第N项为多少 当输入0时，程序结束
 * 当查询的项未被计算到时，将主线程挂起等待，子线程计算到该项，再唤醒主线程
 * */
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define LEN 1000

int length = 0; //表示已被计算的数列的长度
double arr[LEN];

void* childThread(void *arg);
void* checkThread(void *arg);

int main(){
    pthread_t childID;
    int ret = pthread_create(&childID,NULL,(void *)childThread, NULL);
    if(ret !=0){
	perror("Thread Create error.\n");
	exit(EXIT_FAILURE);
    }
    pthread_t fatherId = pthread_self();
    while(1){
	int index;
	printf("[Input]: ");
	scanf("%d",&index);
	if(index == 0){
	    //set the end flag
	    //cancel the child thread then exit
	    printf("Program Exit....\n");
	    pthread_cancel(childID);
	    break;
	    exit(0);
	}else if(index < 0||index > LEN){
	    printf("[ERROR]: OUT OF RANGE.\n");
	    continue;
	}
	if(index >length){
	    /*wait till the child thread have calculated it*/
	    printf("[Wait] Tell You Later.\n");
	    pthread_t checkId;
	    if(pthread_create(&checkId,NULL,(void*)checkThread,&index)!=0){
		perror("Thread Create Error.\n");
		exit(EXIT_FAILURE);
	    }
	    pthread_join(checkId,NULL);
	}
	printf("Array [%d]: %.0lf\n",index, arr[index-1]);
    }
    return 0;
}
void* childThread(void *arg){
    //Child Thread
    // Calculate The resource to be used
    arr[0] = 1;
    arr[1] = 1;
    length = 2;
    while(length<LEN){
	arr[length] = arr[length-1]+arr[length-2];
	length++;
	//计算速度太快，sleep减慢一下速度，体现线程切换的效果
	sleep(1);//一次计算拖慢到1秒
    }
//    printf("[Message]: Child Thread Task Done\n");
    pthread_exit(NULL);
    return ((void*)0);
}
void* checkThread(void *arg){
    while(*(int*)arg>length);
    int index = *(int*)arg;
    pthread_exit(NULL);
    return ((void*)0);
}
