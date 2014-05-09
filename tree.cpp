/*
 * tree.cpp
 * function   : 树 的深度遍历方法 遍历指定目录中的所有文件、
 *              包括子目录下的文件
 *  Created on: 2014-4-22
 *      Author: WAY
 */

#include "tree.h"
#include <stdio.h>

/********************************************
 *DWORD ListAllFileInDirectory(LPSTR szPath)
 * 功能： 遍历目录及所有子目录，打印路径
 * 参数： LPSTR szPath, 为将遍历的目录
 * 返回值：0 执行完成, 1 发生错误
 ********************************************/
DWORD ListAllFileInDirectory(LPSTR szPath2,int nTabs)
{
	CHAR szFilePath[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;

	CHAR szFullPath[MAX_PATH]; //完整路径 卷标+目录+文件名

	//构造代表子目录和文件的路径字符串 通配符*
	lstrcpy(szFilePath,szPath2);
	lstrcat(szFilePath,"\\*");

	//查找第一个文件目录，获得查找句柄
	hListFile=FindFirstFile(szFilePath,&FindFileData);
	if(hListFile==INVALID_HANDLE_VALUE)
	{
		printf("ERROR :%d",(int)GetLastError());
		return 1;
	}
	else
	{
		do
		{
			//过滤 .和.. 不需要遍历
			if(lstrcmp(FindFileData.cFileName,TEXT("."))==0 ||
					lstrcmp(FindFileData.cFileName,TEXT(".."))==0)
			{
				continue;
			}

			//构造成全路径
			wsprintf(szFullPath,"%s\\%s",
					szPath2,FindFileData.cFileName);

			//打印
			//若是文件就打印，若是目录就打印并递归到子目录
			if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				for(int i=1;i<nTabs;i++)
				{
					printf("%s",V_line); //输出一个 竖直线
				}
				printf("%s",B_line); //输出一个 水平线
				printf("%s\n",FindFileData.cFileName);
			}

			//若为目录则递归调用 列举下级目录
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				for(int i=1;i<nTabs;i++)
				{
					printf("%s",V_line); //输出一个 竖直线
				}
				printf("%s",B_line);	//输出一个 水平线
				printf("%s\n",FindFileData.cFileName);

				ListAllFileInDirectory(szFullPath,nTabs+1);
			}
		}
		while(FindNextFile(hListFile,&FindFileData));
	}
	return 0;
}



