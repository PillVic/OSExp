/*
 * 通过使用消息队列实现父子进程之间的消息通信
 * 相互发送消息，接收消息
 */
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/wait.h>

#define LEN 100
#define CHATTIME  10

typedef struct{
    long int messageType;
    char data[LEN];
}message;

void chat(char Pname[],int msgId, message *data);

int main(){
    pid_t id;
    //Build message queue
    int msgChild,msgFather;
    msgChild=msgget((key_t)1234,0666|IPC_CREAT);
    msgFather=msgget((key_t)1234,0666|IPC_CREAT);
    message ChildData,FatherData;
    if(msgChild==-1||msgFather==-1){
	printf("msgget failed\n");
	exit(EXIT_FAILURE);
    }
    if((id=fork())==0){
	//Child Process
	chat("Child", msgChild, &ChildData );
    }else{
	//Father Process
	chat("Father", msgFather, &FatherData);
    }
    wait(0);
    return 0;
}
void chat(char PName[],int msgId, message *data){
	printf("%s Process Created..\n", PName);
	int time=CHATTIME;
	while(time--){
	    char msg[100];
	    printf("%s:  ", PName);
	    //读取整行输入，使得能够允许输入空格
	    fgets(msg,LEN,stdin);
	    printf("%s : %d Setence \n",PName, 10-time);
	}
	printf("Process %s exit...\n",PName);
}
