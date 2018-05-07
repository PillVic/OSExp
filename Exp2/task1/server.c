#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#define LEN 1024
void ERR_EXIT(char *m){
    do{
	perror(m);
	exit(EXIT_FAILURE);
    }while(0);
}

int main(){
    int wfd = open("mypipe", O_WRONLY);
    if(wfd < 0){
	ERR_EXIT("open");
    }
    char buf[LEN];
    while(1){
	buf[0] = 0;
	printf("Please Enter:  ");
	fflush(stdout);
	ssize_t s = read(0, buf, sizeof(buf)-1);
	if(s >0){
	    buf[s] = 0;
	    write(wfd, buf, strlen(buf));
	}else if( s <=0){
	    ERR_EXIT("read");
	}
    }
    close(wfd);
    return 0;
}

