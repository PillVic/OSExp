#define LEN 128

typedef struct{
    int state;//状态标志,0表示可写,1表示可读
    char text[LEN];
}block;
