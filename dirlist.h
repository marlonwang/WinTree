/*
 * dirlist.h
 * function	  : list directory and subdir of current dir
 *  Created on: 2014-4-23
 *      Author: WAY
 */

#ifndef DIRLIST_H_
#define DIRLIST_H_

#include<windows.h>
DWORD ShowFileTime(PFILETIME lptime);
DWORD EnumerateFileInDirectory(LPSTR szPath);

#endif /* DIRLIST_H_ */
