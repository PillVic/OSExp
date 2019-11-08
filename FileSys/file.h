#include<time.h>

#define LEN 128
#define LINENUM 1024
/*
 * 将整个文件系统中的文件都写入一个文件中
 * 前面先写文件的信息：文件名，文件所包含行，文件大小等,所有有效行
 * 后面写整个文件系统中的所有文件内容的行
 * 目录：在系统文件中以“{\\direcStard”开始 以“\\direcEnd}”结束，带有一个计算系数
 * 在读取文件内容时，先获得文件的index中的行，
 * 然后联系目录参数，计算出实际的在系统中的物理行数，然后进行读取
 * */
typedef struct{
    char name[LEN];
    int size;
    int index[LINENUM];//以行为单位记录文件内容，通过检索行获得内容
}file;

typedef struct{
   char name[LEN];
   int size;
   int calNum;
}directory;
