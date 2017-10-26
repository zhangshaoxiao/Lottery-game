// Server.cpp: 定义控制台应用程序的入口点。
//


#include"FishServer.h"
#include<iostream>
#include<pthread.h>
#include"SQL.h"
#pragma comment(lib, "pthreadVC2.lib")
#pragma comment(lib,"ws2_32.lib")
//vector<FishIP>  FishPool;


struct UNI
{
	class MsgServer Msg;
	class FishServer Fish;
};
void * Pro(void *X)
{
	UNI *p = (UNI*)X;
	p->Msg.RecvMsg(p->Fish);
	return 0;
}
int main()
{
	CtrlServer Ctrl;
	//FishServer Fish;
	//MsgServer Msg;   
	UNI test;
	
	
	pthread_t Listen;
	pthread_create(&Listen, NULL, Pro, &test);
	//启动监听线程
	while (true)
	{
		test.Fish.FishNo.clear();
		Ctrl.ReadConfig(test.Fish,test.Msg);    //首先读取配置文件
		pthread_t  TIMER;
		pthread_create(&TIMER, NULL, UpdateTimer, &test.Msg.Seconds);
		//开启定时器

//Msg.RecvMsg(Fish);

		pthread_join(TIMER, NULL);


		test.Fish.Encyc(test.Msg);
		cout << "sdad" << endl;
		string Broadcast = "中奖的老哥是：" + test.Msg.LuckyFish;

		test.Msg.SendMsg(Broadcast);

		MakeLog(test.Fish, test.Msg.LuckyFish, (char *)test.Fish.BaitNo.c_str(), (char *)test.Fish.BaitName.c_str());
		cout << "本次夺宝结束，请更新配置文件之后按回车进行下一波\n";
		cin.get();
	}
	pthread_join(Listen, NULL);
}

