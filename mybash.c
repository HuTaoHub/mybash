#include "mybash.h"

//输出提示符信息
void OutPutInfo()
{
	// struct passwd
	// {
	// 	char *pw_name;	 /* username */
	// 	char *pw_passwd; /* user password */
	// 	uid_t pw_uid;	 /* user ID */
	// 	gid_t pw_gid;	 /* group ID */
	// 	char *pw_gecos;	 /* user information */
	// 	char *pw_dir;	 /* home directory */
	// 	char *pw_shell;	 /* shell program */
	// };
	char flg = '$';
	struct passwd* pw = getpwuid(getuid());
	if(pw == NULL)
	{
		return;
	}
	//判断是普通用户还是root用户
	if(pw->pw_uid == 0)
	{
		flg = '#';
	}
	/*
	*普通用户：
	*	用户名@主机名:当前工作路径名$
	*root用户
	*	root@主机名:当前工作路径名#
	*/
	//获取主机名
	struct utsname buff;
	uname(&buff);
	//获取当前工作路径的绝对路径
	char pathname[128] = {0};
	getcwd(pathname, 127);

	printf("%s@%s:%s%c",pw->pw_name,buff.nodename, pathname,flg);
	fflush(stdout);
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
void ChildExec(char* cmdbuff[], const char* cmd)
{
	if(cmdbuff == NULL || cmd == NULL)
		return;
	
	char pathname[128] = {"/home/jiege/mybash/bin"};
	strcat(pathname, cmdbuff[0]);

	//判断是前台/后台运行
	int ret = IsBack(cmd);	//默认前台0
	

	pid_t pid = fork();
	if(pid == -1)
	{
		perror("fork err");
		return;
	}

	if(pid == 0)
	{
		execv(pathname, cmdbuff);
		perror("command not found");
		exit(0);
	}
	else
	{
		//前台运行
		if(ret == 0)
		{
			wait(NULL);
		}
		//后台运行通过注册的信号zombie去处理僵尸进程
	}
}
//处理后台的僵尸进程
void Zombie()
{
	wait(NULL);
}

//判断是否在后台运行
int IsBack(const char* cmd)
{
	if(cmd == NULL)
		return -1;
	if(strstr(cmd, "&") != NULL)
		return 1;
	return 0;
}