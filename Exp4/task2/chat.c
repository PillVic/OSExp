/* * 通过使用消息队列实现线程之间的消息通信 * 相互发送消息，接收消息
 */
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

#define LEN 128
#define CHATTIME  5

typedef struct{
    long int messageType;
    char data[LEN];
}message;


int msgChild,msgFather;
message ChildData,FatherData;

void chat(char Pname[],int getId, message *read, int sendId, message *write);
void* childThread(void* arg);
int main(){
    int id;
    //Build message queue
    msgChild=msgget((key_t)1234,0666|IPC_CREAT);
    msgFather=msgget((key_t)1234,0666|IPC_CREAT);
    if(msgChild==-1||msgFather==-1){
	printf("msgget failed\n");
	exit(EXIT_FAILURE);
    }
    
    ChildData.messageType = 1;
    FatherData.messageType = 1;

    strcpy(FatherData.data,"START\n");
    if(msgsnd(msgFather, (void*)&FatherData,sizeof(message), 0)){
	printf("message send error!\n");
    }

    pthread_t childID;
    int ret = pthread_create(&childID,NULL,(void *)childThread, NULL);
    if(ret !=0){
	perror("Thread Create error.\n");
	exit(EXIT_FAILURE);
    }
    //Father Thread
    chat("Father", msgFather, &FatherData,msgChild,&ChildData);
    wait(0);
    return 0;
}
void chat(char PName[],int getId, message *readP,int sendId, message * writeP){
	int time = CHATTIME;
	while(time){
	    if(msgrcv(getId, readP,sizeof(message),1,0) < 0 ){
		//get the message
		perror("msgrc");
		exit(1);
	    }
	    printf("%s [GET]:  %s", PName, (*readP).data); 
	    fflush(stdout);
	    if(strcmp((*readP).data,"end\n")==0){
		//set end flag
		break;
	    }
	    //get a line as inputed string  including space
	    printf("%s [SEND]: ", PName);
	    fflush(stdout);
	    fgets((*writeP).data,LEN,stdin);
	    if((msgsnd(sendId, (void*)writeP, sizeof(message), 0))<0){
		//send the message
		printf("message posted error\n");
		exit(1);
	    }
	    if(strcmp((*writeP).data,"end\n")==0){
		//set end flag
		break;
	    }
	    time--;
	}
	printf("Process %s exit...\n",PName);
}
void* childThread(void* arg){
    chat("Child", msgChild, &ChildData,msgFather, &FatherData);
}
