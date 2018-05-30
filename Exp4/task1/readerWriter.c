/*
 * 用记录型信号量完成线程的同步问题
 * 子线程按行读取文件内容到内存
 * 父线程从内存读取内容打印到屏幕
 * */
#include<stdio.h>
#include<stdlib.h>

#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

#define LEN 128

sem_t s;

void* childThread(void *arg);

double arr[LEN]={0};
int main(){
    //Semaphore Build
    sem_init(&s, 0, 1);
    //Thread Create
    pthread_t childId;
    int ret = pthread_create(&childId,NULL,(void*)childThread,NULL);
    if(ret!=0){
	perror("Thread Create Error.\n");
	exit(EXIT_FAILURE);
    }
    //Father Thread
    int index =0;
    while(index<LEN){
	//P()
	sem_wait(&s);
	printf("[%d]: %.0f \n",index,arr[index]);
	index++;
    }
    sem_destroy(&s);
    return 0;
}
void* childThread(void *arg){
    arr[1] = 1;
    arr[2] = 1;
    int length=2;
    while(length<LEN){
	arr[++length] = arr[length-1]+arr[length-2];
	//V()
	sem_post(&s);
	sleep(1);//拖慢计算速度 以便更好的观察线程同步
    }
}
