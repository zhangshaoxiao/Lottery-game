#pragma once
#include"FishServer.h"
#include<iostream>
#include<vector>
#import "c:\Program Files\Common Files\System\ADO\msado15.dll"  no_namespace rename("EOF", "EndOfFile")  //�����ļ�
using namespace std;
struct Log
{
	int OrderNo;   //������  ����
	char NowTime[64];   //����
	char GoodsNo[6];  //������ ��5λ����
	char UserNo[12];  //11λ���������� ���û���
	char GoodsName[11];  //�������֣����10����ĸ
	int IsWin;  //�Ƿ��н�
} ;
void MakeLog(class FishServer & fish, string LuckyFish, char * GoodsNo, char *GoodsName);  //����һ������־

int AddLogToDB(Log NewLog);  //���һ����־��¼
