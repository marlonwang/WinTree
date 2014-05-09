/*
 * dirlist.cpp
 *  function  : 遍历目录下的文件和子文件
 *  Created on: 2014-4-23
 *      Author: WAY
 */
#include "dirlist.h"

/* #include <windows.h>  已经在 dirlist.h 中声明过 */
#include <stdio.h>

/********************************************
 * DWORD EnumerateFileInDirectory(LPSTR szPath)
 * 功能：遍历目录下的文件和子目录，将显示文件和文件夹隐藏、加密属性
 * 参数：LPSTR szPath 需遍历的路径
 * 返回值：0 执行完成 ， 1 代码发生错误
 ********************************************/
DWORD EnumerateFileInDirectory(LPSTR szPath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	CHAR szFilePath[MAX_PATH];

	//构造子目录和文件夹路径的字符串 *通配符
	lstrcpy(szFilePath,szPath);
	//lstrcpy(szFilePath,"\\*.txt"); 匹配.txt文件
	lstrcat(szFilePath,"\\*");

	//查找第一个文件目录,获得查找句柄
	hListFile=FindFirstFile(szFilePath,&FindFileData);
	//判断句柄
	if(hListFile==INVALID_HANDLE_VALUE)
	{
		printf("ERROR ：%d",(int)GetLastError());
		return 1;
	}
	else
	{
		do
		{
			/*
			//不显示代表本级目录和上级目录的. 和  ..
			if(lstrcmp(FindFileData.cFileName,TEXT("."))==0 ||
					lstrcmp(FindFileData.cFileName,TEXT(".."))==0)
			{
				continue;
			}
			*/
			//打印文件目录时间
			ShowFileTime(&(FindFileData.ftCreationTime));
			printf("\t");
			//判断文件属性 加密文件或者文件夹
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED)
				printf("<加密> ");
			//判断文件属性 隐藏文件或文件夹
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
			{
				printf("<隐藏> ");
			}
			//判断文件属性 是否为目录
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				printf("<DIR> ");
			}
			//打印文件名、目录名
			printf("\t\t%s",FindFileData.cFileName);
			printf("\n");
		}
		while(FindNextFile(hListFile,&FindFileData));
	}
	return 0;
}

/*****************************************************
 * DWORD ShowFileTime(PFILETIME lptime)
 * 功能：转换文件时间并打印
 * 参数：PFILETIME lptime 指向文件时间的指针
 * 返回值:0
 *****************************************************/
DWORD ShowFileTime(PFILETIME lptime)
{
	//文件时间结构
	FILETIME ftlocal;
	//系统时间结果
	SYSTEMTIME st;
	//调整为系统所在时区时间
	FileTimeToLocalFileTime(lptime,&ftlocal);
	//时间转换为SYSTEMTIME格式，便于显示
	FileTimeToSystemTime(&ftlocal,&st);
	//显示时间字符串
	printf("%4d-%02d-%02d %02d:%02d:%02d",
			st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	return 0;
}
