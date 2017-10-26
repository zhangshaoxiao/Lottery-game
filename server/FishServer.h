#ifndef FishServer_H
#define FishServer_H
using namespace std;
#include<vector>
#include<string>
#include<winsock.h>
#include<time.h>
#include<pthread.h>
#define MAX 1024
#define HOST_IP 127.0.0.1
#define PORT 8899
struct FishIP
{

	string FishNo;
	SOCKADDR_IN IP;

};
//vector<FishIP>  FishPool;


class MsgServer
{
public:
	 int Seconds;
	 vector<FishIP>  FishPool;
	string LuckyFish;
	SOCKET socServer;
	//infomation of address, always NOT being operated directly.  
	SOCKADDR_IN addr_Srv;
	SOCKADDR_IN addr_Clt;
	char recvBuf[MAX];
	MsgServer();
	int RecvMsg(class FishServer &);  //获取来自客户端的消息
	int GetInfo();//获取来自FishServer的消息
	int SendMsg(string thsMSG);//向客户端发送响应消息 ，发送定时器或者全局广播
	int UpdateFishList(class FishServer& fish,string No, SOCKADDR_IN addr);//更新全局用户列表
	int SendShopInfo(class FishServer &,string UserNo,string GoodsNo,int Money);
};



class CtrlServer

{  public:
	//int Seconds;            //单位：秒
	//pthread_mutex_t  Mutex;
	
	
	CtrlServer();
	friend void * UpdateTimer(void *sec);
	int ReadConfig(class FishServer &,class MsgServer &);
	int SendtoFishServer(class FishServer &);

};


class FishServer
{
public:
	public :
		   string  BaitNo;   //鱼饵编号，没错，货就是鱼
		   string BaitName;  //鱼饵名字 ，少于15个汉字或者31个英文字符
		   int  FishNum;   // 鱼的数量
		   int  LeftTime;  //剩余时间，单位 秒
		   std::vector <std::string>  FishNo;//参与的玩家帐户名
		   FishServer();             //构造函数
		   int ShopInfo(std::string fish,int money ); //接受抢购信息
		   int Encyc(class MsgServer &); //钦定一个人中奖
		   int SendToMSG(class MsgServer &, std::string);
		   int GetCtrlInfo();

};

#endif