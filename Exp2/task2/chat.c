#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define LEN 100

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
	exit(0);
    }else{
	//Father Process
	chat("Father", msgFather, &FatherData);
//	printf("Father Process Created..\n");
//	while(1){
//	    char msg[100]; 
//	    printf("Father: ");
//	    scanf("%s",msg);
//	    printf("\n");
//	}
	exit(0);
    }
    return 0;
}
void chat(char PName[],int msgId, message *data){
	printf("%s Process Created..\n", PName);
	char msg[100];
	while(1){
	    char msg[100];
	    printf("%s:  ", PName);
	    scanf("%s",msg);
	    printf("\n");
	}
}
