#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>


int main(){
    pid_t id;
    if((id=fork())==0){
	//Child Process
	printf("Child Process Created..\n");
	while(1){
	    char msg[100];
	    printf("Child:  ");
	    scanf("%s",msg);
	    printf("\n");
	}
	exit(0);
    }else{
	//Father Process
	printf("Father Process Created..\n");
	while(1){
	    char msg[100]; 
	    printf("Father: ");
	    scanf("%s",msg);
	    printf("\n");
	}
	exit(0);
    }
    return 0;
}

