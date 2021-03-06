#include "mybash.h"

int main()
{
	//处理后台的僵尸进程
	signal(SIGCHLD, Zombie);

	char* cmd = NULL;
	while(1)
	{	
		//输出提示符信息
		OutPutInfo();
		//从键盘获取命令
		cmd = GetCmd();
		//存放解析后的参数
		char* cmdbuff[32] = {0};
		//命令解析
		returncode ret = CmdResolve(cmd, cmdbuff);
		if(ret == EXIT)
		{
			free(cmd);
			cmd = NULL;
			break;
		}
		else if(ret == MYCD)
		{
			//切换路径
			Mycd(cmdbuff[1]);
			free(cmd);
			cmd = NULL;
		}
		//空地址
		else if(ret == ADDR_NULL)
		{
			free(cmd);
			cmd = NULL;
			continue;
		}
		else
		{
			//进程替换
			ChildExec(cmdbuff, cmd);
		}
		
	}

	return 0;
}