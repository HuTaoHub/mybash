#include "mybash.h"

//输出提示符信息
void OutPutInfo()
{
	
}

//从键盘获取命令
char* GetCmd()
{
	char* cmd = (char*)malloc(sizeof(char) * 128);
	memset(cmd, 0, sizeof(char) * 128);
	fgets(cmd, 127, stdin);
	cmd[strlen(cmd) - 1] = '\0';	//去掉'\n'
	
	return cmd;
}

//命令解析
returncode CmdResolve(char* cmd, char* cmdbuff[])
{
	if(cmd == NULL || cmdbuff == NULL)
	{
		return ADDR_NULL;
	}
	//分割指令
	char *s = strtok(cmd, " ");
	int i = 0;
	while (s != NULL)
	{
		cmdbuff[i++] = s;
		s = strtok(NULL, " ");
	}
	//最后一个置空
	cmdbuff[i] = NULL;

	if(strcmp(cmdbuff[0], "exit") == 0)
	{
		//退出
		return EXIT;
	}

	if(strcmp(cmdbuff[0], "cd") == 0)
	{
		//切换目录
		return MYCD;
	}
	else
	{
		//进程替换
		return EXEC;
	}
}

//进程替换
void ChildExec(char* cmdbuff[])
{
	if(cmdbuff == NULL)
		return;
	
	char pathname[128] = {"/home/jiege/mybash/"};
	strcat(pathname, cmdbuff[0]);

	pid_t pid = fork();
	if(pid == -1)
	{
		perror("fork err");
		return;
	}

	if(pid == 0)
	{
		execv(pathname, cmdbuff);
		perror("command not exist");
		exit(0);
	}
	else
	{
		wait(NULL);
	}
}