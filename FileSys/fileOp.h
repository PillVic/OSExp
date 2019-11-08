#include"file.h"

bool IsInitialized(char *rootPath); //格式化

void initialize();//格式化文件系统
void loadSystem();//挂载该文件系统
void unloadSystem();//卸载该文件系统

file* getFile(char *fileName);
directory* getDirectory(char *PATH);

void readFile(file * file);
void deleteFile(file *fileName);
void makeFile(file *file, char* PATH);
void writeFile(file* fileA);

void changeDirectory(directory *directoryName);//更改工作目录
void deleteDirectory(directory *directoryName);
void makeDirectory(directory *directoryName);



