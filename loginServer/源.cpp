#include"SQL.h"
using namespace std;
#define LOG_PORT  8900         //登录服务器的端口
#define HOST_IP 127.0.0.1
int main()
{
	char x[128];
	int version_a = 1;//low bit  
	int version_b = 1;//high bit  
					  //makeword  
	WORD versionRequest = MAKEWORD(version_a, version_b);
	WSAData wsaData;
	int error;
	error = WSAStartup(versionRequest, &wsaData);

	if (error != 0) {
		printf("ERROR!");

	}
	//check whether the version is 1.1, if not print the error and cleanup wsa?  
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		printf("WRONG WINSOCK VERSION!");
		WSACleanup();

	}
	char requestStr[MAX];
	/*
	SOCKET socClient;
	SOCKADDR_IN addrSrv;
	//build a sockeet
	socClient = socket(AF_INET, SOCK_DGRAM, 0);
	addrSrv;        // a instance of SOCKADDR_IN, which is used in format of SOCKADDR.
	inet_pton(AF_INET, "127.0.0.1", (void *)&addrSrv.sin_addr.S_un.S_addr);        //set the host IP
	addrSrv.sin_family = AF_INET;     //set the protocol family
	addrSrv.sin_port = htons(CLIENT_PORT);      //set the port number

	// array to store the data that server feedback.
	*/
	SOCKET socServer = socket(AF_INET, SOCK_DGRAM, 0);
	//infomation of address, always NOT being operated directly.  

	//Struct sin_addr is  used to defind IP address,  it's a property of addr_in.  
	//It's nest three structs as S_un_b, S_un_w and S-un.(union)  
	SOCKADDR_IN addr_Srv;
	addr_Srv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//set protocol family  
	addr_Srv.sin_family = AF_INET;
	//set host port  
	addr_Srv.sin_port = htons(LOG_PORT);

	//bind socket to  the host  
	bind(socServer, (SOCKADDR*)&addr_Srv, sizeof(SOCKADDR));
	int fromlen = sizeof(SOCKADDR);
	SOCKADDR_IN in_addr;        //接入地址

								//addrSrv.sin_port = htons(MSG_HOST_PORT);      //set the port number  
	char DecryptMSG[MAX];
	string tmpstr;
	FILE *log;   //写日志
	char Buf[MAX];
	cout << "聆听消息线程启动成功\n";
	string GetMsg;
	char res[MAX];
	char KeyWord[12];
	char History[4 * MAX];
	char temp[128];
	char sqlcommand[1024];
	char UserName[12];
	char UserPwd[9];
	while (true)
	{

		
		recvfrom(socServer, Buf, MAX, 0, (SOCKADDR*)&in_addr, &fromlen);
		cout << "recv " << Buf << endl;
			GetMsg = Buf;
			if (GetMsg.find('H') == 0) //表示是获取夺宝记录的消息类型
			{
				SelectLog(GetMsg, KeyWord, History,sqlcommand);
				






					sendto(socServer, History, strlen(History), 0, (SOCKADDR*)&in_addr, sizeof(SOCKADDR));


				
				
			}
			if (GetMsg.find('@') == 11)
			{
				string temp1(GetMsg, 0, 11);
				string temp2(GetMsg, 12, 8);
			
				strcpy_s(UserName, 12, (char *)temp1.c_str());
				strcpy_s(UserPwd, 9, (char *)temp2.c_str());

				 NewUser(UserName, UserPwd, x);

				 sendto(socServer, x, strlen(x), 0, (SOCKADDR*)&in_addr, sizeof(SOCKADDR));


			}
			else if(GetMsg.find('#') == 11)
			{
				string Name(GetMsg, 0, 11);
				string PWD(GetMsg, 12, 8);
				char theName[13];
				char thePWD[10];
				strcpy_s(theName, Name.c_str());
				strcpy_s(thePWD, PWD.c_str());
				cout << theName << "  " << thePWD << endl;
				if (CheckPWD(theName, thePWD) == 0)
				{
					sendto(socServer, "欢迎老哥登录成功！", strlen("欢迎老哥登录成功！") + 1, 0, (SOCKADDR*)&in_addr, sizeof(SOCKADDR));

				}
				else
					sendto(socServer, "账号或者密码错误，请重试", strlen("账号或者密码错误，请重试") + 1, 0, (SOCKADDR*)&in_addr, sizeof(SOCKADDR));

			}
	}
	cout << "end" << endl;
}