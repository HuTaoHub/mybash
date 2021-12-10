#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

typedef enum returncode
{
    //地址空
    ADDR_NULL = 0,
    //退出 1
    EXIT,
    //cd 2
    MYCD,
    //exec 3
    EXEC
}returncode;

//输出提示符信息
void OutPutInfo();

//从键盘获取命令
char* GetCmd();

//命令解析
returncode CmdResolve(char* cmd, char* cmdbuff[]);

//进程替换
void ChildExec(char* cmdbuff[]);