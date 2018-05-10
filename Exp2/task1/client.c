#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

#define LEN 64
void ERR_EXIT(char *m){
    perror(m);
    exit(EXIT_FAILURE);
}

int main(){
    int wfd = open("mypipe", O_WRONLY);
    if(wfd < 0){
	ERR_EXIT("open");
    }
    char buf[LEN];
    while(1){
	buf[0] = 0;
	printf("Please input:  ");
	fflush(stdout);
	if(fgets(buf,LEN, stdin)!=NULL){
	    fflush(stdin);
	    write(wfd, buf, strlen(buf));
	    if(strcmp(buf,"end\n")==0){
		break;
	    }

	}else {
	    ERR_EXIT("read");
	    break;
	}
    }
    close(wfd);
    return 0;
}

