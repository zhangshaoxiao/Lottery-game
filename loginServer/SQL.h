
#ifndef SQL_H
#define SQL_H
#include <stdio.h>  
#include <tchar.h>  
#include<iostream>
#include <vector>

#include "Winsock2.h"  

#include "string"  
#pragma comment(lib,"ws2_32.lib")
#import "c:\Program Files\Common Files\System\ADO\msado15.dll"  no_namespace rename("EOF", "EndOfFile")  //置入文件
using namespace std;


#define MAX 1024

int Compare(char a[MAX], char b[MAX]);
int NewUser(char UserName[12],char UserPwd [9],char *x);  //添加新帐号
int Delete(char DelRow[MAX], char table[16]);//  删除某一行
int Insert(void * req, char table[16]);  //第一个参数是传进来的数据结构，第二个参数表名

int SelectLog(string &GetMsg,char KeyWord[], char History[], char sqlcommand[]);
_RecordsetPtr select(char *KeyWord, char *ColName, char *result, char* table); //ch同上，pRst是将数据传出的结构
int  CheckPWD(char *Name,char *	PWD);																	   //第一个参数是查询关键字，第二个是对应的列名，第3个存储结果（有局限性，只存储密码），第三个参数是表名。
#endif
