#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    pid_t id;
    if((id=vfork())==0){
	//Child Process
	printf("Child:Fuck you  \n");
	exit(0);
    }else{
	//Father Process
	printf("Father:Come on!    \n");
	exit(0);
    }
    return 0;
}

