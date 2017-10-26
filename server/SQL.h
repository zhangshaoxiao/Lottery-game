#pragma once
#include"FishServer.h"
#include<iostream>
#include<vector>
#import "c:\Program Files\Common Files\System\ADO\msado15.dll"  no_namespace rename("EOF", "EndOfFile")  //置入文件
using namespace std;
struct Log
{
	int OrderNo;   //订单号  主键
	char NowTime[64];   //日期
	char GoodsNo[6];  //货物编号 ，5位数字
	char UserNo[12];  //11位阿拉伯数字 ，用户名
	char GoodsName[11];  //货物名字，最多10个字母
	int IsWin;  //是否中奖
} ;
void MakeLog(class FishServer & fish, string LuckyFish, char * GoodsNo, char *GoodsName);  //创建一条新日志

int AddLogToDB(Log NewLog);  //添加一条日志记录
