#include"SQL.h"
#include<time.h>
#include<stdio.h>
#define  _CRT_SECURE_NO_WARNINGS
static int OrderNo = 11111;
int AddLogToDB(Log NewLog)
{

	char tmp1[8];
	char tmp2[2];
	_itoa_s(NewLog.OrderNo, tmp1, 10);
	_itoa_s(NewLog.IsWin, tmp2, 10);
	
	char sqlcommand[1024];
	for (int i = 0; i < 1024; i++)
		sqlcommand[i] = '\0';


	strcpy_s(sqlcommand, "insert into LogTable values ('");  //���ݿ�ı���ΪLogTable

	strcat_s(sqlcommand,tmp1);

	strcat_s(sqlcommand, "','");
	strcat_s(sqlcommand,NewLog.GoodsNo);
	strcat_s(sqlcommand, "', '");

	strcat_s(sqlcommand, NewLog.GoodsName);
	strcat_s(sqlcommand, "','");
	strcat_s(sqlcommand, NewLog.UserNo);
	strcat_s(sqlcommand, "','");
	strcat_s(sqlcommand, NewLog.NowTime);
	strcat_s(sqlcommand, "','");
	strcat_s(sqlcommand, tmp2);
	strcat_s(sqlcommand, "');");
	//_RecordsetPtr pRst;
	_ConnectionPtr  sqlSp;
	_bstr_t strConnect = "Provider = SQLOLEDB.1; Integrated Security = SSPI; Persist Security Info = False; Initial Catalog =FUCK; Data Source = .";//�������ݿ��ַ���
																																			//��ʼ��COM��  
	::CoInitialize(NULL);
	//���һ��ָ��Connection�����ָ��m_pConnection  
	_ConnectionPtr m_pConnection(__uuidof(Connection));
	//����Connection����  
	if (FAILED(m_pConnection.CreateInstance(__uuidof(Connection))))
	{
		cout << "����Connection����ʱ����\n";
	}

	try
	{
		//�������ݿ�  
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		cout << "�������ݿ�ʱ����\n ";
		cout << e.Description();
		cin.get();
		
	}
	


	//char testSql[1024]("insert into LogTable values('11811','12345','qwertyuiop','12357984844','2017/10/23','1');");
	try {
		cout << sqlcommand << endl;
		m_pConnection->Execute(sqlcommand, NULL, adCmdText);
	}
	catch(_com_error se)
	{
		cout << se.Description() << endl;
	}
//	m_pConnection->Execute(sqlcommand, NULL, adCmdText);
	return 0;
}


void MakeLog( class FishServer & fish,string LuckyFish, char * GoodsNo, char *GoodsName)
{
	
	auto Name = fish.FishNo.begin();
	vector<Log> theLog;
	Log temp;
	while (Name != fish.FishNo.end())
	{
		
		temp.OrderNo = OrderNo;
		strcpy_s(temp.UserNo, (*Name).c_str());
		strcpy_s(temp.GoodsNo, GoodsNo);
		strcpy_s(temp.GoodsName, GoodsName);
		if (*Name != LuckyFish)
			temp.IsWin = 0;
		else temp.IsWin = 1;
		time_t t = time(0);
		struct tm ptm;
		time_t nowtime;
		time(&nowtime);
		localtime_s(&ptm, &nowtime);
		strftime(temp.NowTime, sizeof(temp.NowTime), "%Y/%m/%d ", &ptm);
		theLog.push_back(temp);
		Name++;
	}
	
	auto it = theLog.begin();
	while (it != theLog.end())
	{
		AddLogToDB(*it);
		it++;
	}
}