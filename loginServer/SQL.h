
#ifndef SQL_H
#define SQL_H
#include <stdio.h>  
#include <tchar.h>  
#include<iostream>
#include <vector>

#include "Winsock2.h"  

#include "string"  
#pragma comment(lib,"ws2_32.lib")
#import "c:\Program Files\Common Files\System\ADO\msado15.dll"  no_namespace rename("EOF", "EndOfFile")  //�����ļ�
using namespace std;


#define MAX 1024

int Compare(char a[MAX], char b[MAX]);
int NewUser(char UserName[12],char UserPwd [9],char *x);  //������ʺ�
int Delete(char DelRow[MAX], char table[16]);//  ɾ��ĳһ��
int Insert(void * req, char table[16]);  //��һ�������Ǵ����������ݽṹ���ڶ�����������

int SelectLog(string &GetMsg,char KeyWord[], char History[], char sqlcommand[]);
_RecordsetPtr select(char *KeyWord, char *ColName, char *result, char* table); //chͬ�ϣ�pRst�ǽ����ݴ����Ľṹ
int  CheckPWD(char *Name,char *	PWD);																	   //��һ�������ǲ�ѯ�ؼ��֣��ڶ����Ƕ�Ӧ����������3���洢������о����ԣ�ֻ�洢���룩�������������Ǳ�����
#endif
