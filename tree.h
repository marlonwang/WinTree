/*
 * tree.h
 *
 *  Created on: 2014-4-22
 *      Author: WAY
 */

#ifndef TREE_H_
#define TREE_H_

#include <windows.h>

// 预处理声明
//#pragma comment (lib,"User32.lib") 适用VC

//全局变量  树形形状
const LPCTSTR V_line = "|    ";
const LPCTSTR B_line = "|----";
DWORD ListAllFileInDirectory(LPSTR szPath2,int nTabs);

#endif /* TREE_H_ */
