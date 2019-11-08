#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>


#include"fileOp.h"

bool IsInitialized(char *rootPath){
   return access(rootPath,F_OK)!=-1;
}

void loadSystem(){

}
