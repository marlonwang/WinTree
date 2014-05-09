/*
 * main.cpp
 *
 *  Created on: 2014-4-23
 *      Author: WAY
 */

#include "dirlist.h"
#include "tree.h"

/**************************************
 * int main(int argc, PCHAR argv[])
 * 功能：调用 ListFileInDirectory
 *     遍历目录下的文件和文件夹
 * 参数：argv[1]为需遍历的路径，若为空则取当前路径
 **************************************/
int main(int argc, PCHAR argv[])
{
	if(argc==2)
	{
		//EnumerateFileInDirectory(argv[1]);
        ListAllFileInDirectory(argv[1],1);
	}
	else
	{
		CHAR szCurrentPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,szCurrentPath);
		//EnumerateFileInDirectory(szCurrentPath);
		ListAllFileInDirectory(szCurrentPath,1);
	}

	return 0;
}

