#include<stdio.h>
#include<string.h>

#include"translate.h"

#define LEN 128

char pwd[LEN];
char cmd[LEN];
char name[LEN];

int main(){
    strcpy(pwd, "/"); //root directory
    printf("")
    while(1){
	printf("[%s] ",pwd);
	scanf("%s %s" ,cmd, name);
	if(strcmp(cmd,"end") == 0){
	    //Set the end flag
	    break;
	}else{

	}
    }
    return 0;
}
