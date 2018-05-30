#include<stdlib.h>  
#include<stdio.h>  
#include<sys/types.h>  
#include<sys/sysinfo.h>  
#include<unistd.h>  
#define __USE_GNU  
#include<sched.h>  
#include<ctype.h>  
#include<string.h>  
  
int main(int argc, char* argv[])  
{  
    //sysconf获取有几个CPU  
	int num = sysconf(_SC_NPROCESSORS_CONF);  
	int created_thread = 0;  
	int myid;  
	int i;  
	int j = 0;  
  
    //原理其实很简单，就是通过cpu_set_t进行位与操作  
	cpu_set_t mask;  
	cpu_set_t get;  
  
	if (argc != 2)  
	{  
		printf("usage : ./cpu num\n");  
		exit(1);  
	}  
  
	myid = atoi(argv[1]);  
  
	printf("system has %i processor(s). \n", num);  
  
    //先进行清空，然后设置掩码  
	CPU_ZERO(&mask);  
	CPU_SET(myid, &mask);  
  
    //设置进程的亲和力  
	if (sched_setaffinity(0, sizeof(mask), &mask) == -1)  
	{  
		printf("warning: could not set CPU affinity, continuing...\n");  
	}  
	while (1)  
	{  
  
		CPU_ZERO(&get);  
	//获取当前进程的亲和力  
		if (sched_getaffinity(0, sizeof(get), &get) == -1)  
		{  
			printf("warning: cound not get cpu affinity, continuing...\n");  
		}  
		for (i = 0; i < num; i++)  
		{  
			if (CPU_ISSET(i, &get))  
			{  
				printf("this process %d is running processor : %d\n",getpid(), i);  
			}  
		}  
	}  
	return 0;  
}  


进程设置CPU运行，其实只能是单线程。多线程设定CPU如下：

[cpp] view plain copy

#define _GNU_SOURCE  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>  
#include <pthread.h>  
#include <sched.h>  
  
void *myfun(void *arg)  
{  
    cpu_set_t mask;  
    cpu_set_t get;  
    char buf[256];  
    int i;  
    int j;  
    //同样的先去获取CPU的个数  
    int num = sysconf(_SC_NPROCESSORS_CONF);  
    printf("system has %d processor(s)\n", num);  
  
    for (i = 0; i < num; i++) {  
	CPU_ZERO(&mask);  
	CPU_SET(i, &mask);  
    //这个其实和设置进程的亲和力基本是一样的  
	if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {  
	    fprintf(stderr, "set thread affinity failed\n");  
	}  
	CPU_ZERO(&get);  
	if (pthread_getaffinity_np(pthread_self(), sizeof(get), &get) < 0) {  
	    fprintf(stderr, "get thread affinity failed\n");  
	}  
	for (j = 0; j < num; j++)   
	{  
	    if (CPU_ISSET(j, &get))   
	    {  
		printf("thread %d is running in processor %d\n", (int)pthread_self(), j);  
	    }  
	}  
	j = 0;  
	while (j++ < 100000000) {  
	    memset(buf, 0, sizeof(buf));  
	}  
    }  
    pthread_exit(NULL);  
}  
  
int main(int argc, char *argv[])  
{  
    pthread_t tid;  
    if (pthread_create(&tid, NULL, (void *)myfun, NULL) != 0)  
    {  
	fprintf(stderr, "thread create failed\n");  
  

return -1;  
}  
pthread_join(tid, NULL);  
return 0;  
}  
