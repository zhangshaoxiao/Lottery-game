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
	int RecvMsg(class FishServer &);  //��ȡ���Կͻ��˵���Ϣ
	int GetInfo();//��ȡ����FishServer����Ϣ
	int SendMsg(string thsMSG);//��ͻ��˷�����Ӧ��Ϣ �����Ͷ�ʱ������ȫ�ֹ㲥
	int UpdateFishList(class FishServer& fish,string No, SOCKADDR_IN addr);//����ȫ���û��б�
	int SendShopInfo(class FishServer &,string UserNo,string GoodsNo,int Money);
};



class CtrlServer

{  public:
	//int Seconds;            //��λ����
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
		   string  BaitNo;   //�����ţ�û����������
		   string BaitName;  //������� ������15�����ֻ���31��Ӣ���ַ�
		   int  FishNum;   // �������
		   int  LeftTime;  //ʣ��ʱ�䣬��λ ��
		   std::vector <std::string>  FishNo;//���������ʻ���
		   FishServer();             //���캯��
		   int ShopInfo(std::string fish,int money ); //����������Ϣ
		   int Encyc(class MsgServer &); //�ն�һ�����н�
		   int SendToMSG(class MsgServer &, std::string);
		   int GetCtrlInfo();

};

#endif