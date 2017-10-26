#pragma   once  
#include"FishServer.h"
#include<iostream>
#include<string>
pthread_mutex_t  TIMER_Mutex;
//extern vector<FishIP>  FishPool;
MsgServer::MsgServer()
{
	Seconds = 10;
	int version_a = 1;//low bit  
	int version_b = 1;//high bit  


	WORD versionRequest = MAKEWORD(version_a, version_b);
	WSAData wsaData;
	int err;
	//wsa startup  
	err = WSAStartup(versionRequest, &wsaData);

	if (err != 0) {
		printf("ERROR!");

	}
	//check whether the version is 1.1, if not print the error and cleanup wsa?  
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		printf("WRONG WINSOCK VERSION!");
		WSACleanup();

	}


	 socServer = socket(AF_INET, SOCK_DGRAM, 0);
	//infomation of address, always NOT being operated directly.  
	
	//Struct sin_addr is  used to defind IP address,  it's a property of addr_in.  
	//It's nest three structs as S_un_b, S_un_w and S-un.(union)  
	addr_Srv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//set protocol family  
	addr_Srv.sin_family = AF_INET;
	//set host port  
	addr_Srv.sin_port = htons(PORT);

	//bind socket to  the host  
	bind(socServer, (SOCKADDR*)&addr_Srv, sizeof(SOCKADDR));
	char Message[MAX];
	//address  of a client  
	

}

int MsgServer::RecvMsg(class FishServer &fish)
{
	
	string str;
	//int Seconds;
	int fromlen = sizeof(SOCKADDR);
	char SendBuf[10]("hello");
	//Seconds = 1000;
	//char RecvBuf[MAX];
	
	try {
		while (true)
		{
			
			recvfrom(socServer, recvBuf, MAX, 0, (SOCKADDR*)&addr_Clt, &fromlen);        //读取消息到缓冲区
			cout << recvBuf << endl;;
			str.assign(recvBuf);
			if (str.find("#")==0)            //如果是登录后请求发送定时器消息
			{
				if (Seconds > 0)
				{
					_itoa_s(Seconds, SendBuf, 10);
					sendto(socServer, SendBuf, strlen(SendBuf) + 1, 0, (SOCKADDR*)&addr_Clt, sizeof(SOCKADDR)); //发送成功消息
					//发送定时器信息
					string No(str, 1, 11);
					UpdateFishList(fish, No, addr_Clt);   //更新全局在线人列表
					cout << "哈！上钩啦：" << No << endl;
				}
				if (Seconds <= 0)
				{
					char Late[MAX] = "对不起，本波夺宝结束啦，请等待下一波";
					sendto(socServer, Late, strlen(Late) + 1, 0, (SOCKADDR*)&addr_Clt, sizeof(SOCKADDR)); //发送超时消息
					string No(str, 1, 11);
					cout << "哈！这个傻逼来晚啦：" << No << endl;																							//发送定时器信息
				}
				if (str.find("$") == 12)   //下注消息
				{
					string UserNo(str, 1, 11);
					string GoodsNo(str, 13, 5);
					string Money(str, 19, 4);
					int money = atoi(Money.c_str());
					string No(str, 1, 11);
					//	fish.FishNo.push_back(No);
					SendShopInfo(fish, UserNo, GoodsNo, money);
					sendto(socServer, "下注成功", strlen("下注成功") + 1, 0, (SOCKADDR*)&addr_Clt, sizeof(SOCKADDR)); //发送超时消息
					cout << "这条鱼下注 " << Money << endl;
				}

			}

			
			 
		}
	}
	catch (exception &e)
	{
		cout <<"error: "<< e.what() << endl;
	}
	return 0;
}
//更新在线人
int MsgServer::UpdateFishList(class FishServer& fish,string No,SOCKADDR_IN addr)
{
	
	struct FishIP newFish;
	newFish.FishNo = No;
	newFish.IP.sin_addr = addr.sin_addr;
	newFish.IP.sin_port = addr.sin_port;
	newFish.IP.sin_family = addr.sin_family;
	strcpy_s(newFish.IP.sin_zero , addr.sin_zero);
	FishPool.push_back(newFish);
	//把连接的人写入鱼塘
	//fish.FishNo.push_back(No);   //把下注的鱼写入下注人列表
	return 0;
}
//更新下注人名单
int MsgServer:: SendShopInfo(class FishServer & fish,string UserNo,string GoodsNo,int Money)
{
	if (GoodsNo == fish.BaitNo) //两者要相等才添加进去
	{
		fish.FishNo.push_back(UserNo);
		fish.FishNum++;
	}

	return 0;
}

CtrlServer::CtrlServer()
{
	//CtrlServer::Seconds = 1000;

}

void * UpdateTimer(void *sec)
{
	int *p=(int *)sec;
	
	while (*p > 0)
	{
		//if (pthread_mutex_trylock(&TIMER_Mutex))
		{
			*p =*p - 1;
		}
	//	pthread_mutex_unlock(&TIMER_Mutex);
		Sleep(1000);
		std::cout << *p << endl;;
	}
	
	pthread_exit((void*)1);
	return 0;
}

int CtrlServer::ReadConfig(class FishServer& fish,class MsgServer & Msg)
{
	FILE *fp;
	fopen_s(&fp, "config.txt", "r");
	//配置格式为@物品编号5#物品名字10%剩余时间4
	char str[1024];
	fgets(str, 1024, fp);
	string config(str);
	fclose(fp);
	string GoodsNo(config, 1, 5);
	string GoodsName(config, 7, 10);
	string LeftTime(config,18, 4);
	cout << "lt  " << LeftTime << endl;
	int LT=atoi(LeftTime.c_str());
	fish.BaitNo = GoodsNo;
	fish.BaitName = GoodsName;
	fish.LeftTime = LT;
	
	Msg.Seconds = LT;
	cout << GoodsNo << "  :  " << GoodsName << "   :" << LT << endl;
	return 0;
}

FishServer::FishServer()
{
	  FishNum=0;   // 鱼的数量
	  LeftTime=0;  //剩余时间，单位 秒

}
//钦定一个人中奖
int FishServer::Encyc(class MsgServer & Msg)
{
	int LuckyNo;
	srand((unsigned)time(NULL));
	if (this->FishNum > 1)

	{
		 LuckyNo = rand() % this->FishNum;
		 auto it = FishNo.begin();

		 for (int i = 0; i < LuckyNo; i++)
			 it++;

		 Msg.LuckyFish = (*it);
	}
	if (this->FishNum == 1)
	{
		auto it = FishNo.begin();
		Msg.LuckyFish = (*it);
		return 0;
	}
	if(this->FishNum==0)
		LuckyNo = 00000000000;
	
	

		

	return 0; 
}

int MsgServer::SendMsg(string theMSG)
{
	
	auto it = FishPool.begin();
	
	for (; it != FishPool.end(); it++)
	{
		sendto(socServer, theMSG.c_str(), strlen(theMSG.c_str()) + 1, 0, (SOCKADDR*)&(it->IP), sizeof(SOCKADDR)); //发送成功消息
		
	}
	
	return 0;
}