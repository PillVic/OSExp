#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>


#define LEN 1024

void ERR_EXIT(char *m){
    perror(m);
    exit(EXIT_FAILURE);
}
int main(){
    umask(0);
    if(mkfifo("mypipe",0644)<0){
	ERR_EXIT("mypipe");
    }
    int rfd = open("mypipe", O_RDONLY);
    if(rfd < 0){
	ERR_EXIT("open");
    }
    char buf[LEN];
    while(1){
	buf[0] = 0;
	printf("Please wait...\n");
	ssize_t s = read(rfd, buf, sizeof(buf)-1);
	if(s >0){
	    buf[s-1] = 0;
	    printf("[client]: %s\n", buf);
	    if(strcmp(buf,"end")==0){
		break;
	    }
	}else{
	    ERR_EXIT("read");
	}
    }
    close(rfd);
    unlink("mkpipe");
    return 0;
}
