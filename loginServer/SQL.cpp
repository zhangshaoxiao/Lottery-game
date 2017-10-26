#include"SQL.h"
using namespace std;

int Insert(void * req, char table[16]) //第一个参数是传进来的数据结构，第二个参数表名
{
	return 0;
};

int Delete(char DelRow[MAX], char table[16])
{
	return 0;
};
int Compare(char a[], char b[])  //字符串比较函数，系统自带的不好用
{
	int len;
	len = strlen(a) < strlen(b) ? strlen(a) : strlen(b);
	for (int i = 0; i <len; i++)
	{
		if (a[i] != b[i])
			return -1;
	}
	return 0;
};


_RecordsetPtr select(char *KeyWord, char *RowName, char *result, char *table)
{
	for (int i = 0; i <32; i++)
	{
		result[i] = '\0';
	}
	char temp[100];       //临时变量，用于存储查询的部分结果
	_RecordsetPtr pRst;
	char sqlcommand[1024];
	for (int i = 0; i < 1024; i++)
		sqlcommand[i] = '\0';
	strcpy_s(sqlcommand, "select * from  ");

	strcat_s(sqlcommand, table);

	strcat_s(sqlcommand, "  where ");
	strcat_s(sqlcommand, RowName);
	strcat_s(sqlcommand, "  = '");

	strcat_s(sqlcommand, KeyWord);
	strcat_s(sqlcommand, "';");

	//_RecordsetPtr pRst;
	_ConnectionPtr  sqlSp;
	_bstr_t strConnect = "Provider = SQLOLEDB.1; Integrated Security = SSPI; Persist Security Info = False; Initial Catalog =FUCK; Data Source = .";//连接数据库字符串
																																						   //初始化COM库  
	::CoInitialize(NULL);
	//添加一个指向Connection对象的指针m_pConnection  
	_ConnectionPtr m_pConnection(__uuidof(Connection));
	//创键Connection对象  
	if (FAILED(m_pConnection.CreateInstance(__uuidof(Connection))))
	{
		cout << "创键Connection对象时出错\n";
	}

	try
	{
		//连接数据库  
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
	}
	catch (_com_error e)
	{
		cout << "连接数据库时出错\n ";
		cout << e.Description();
		cin.get();
		return pRst;
	}
	try                                   //将查询到的结果存储在记录集
	{
		pRst = m_pConnection->Execute(sqlcommand, NULL, adCmdText);
		//执行SQL： select * from Table_BB 
		if (!pRst->BOF)
		{
			pRst->MoveFirst();
			vector<_bstr_t> column_name;

			//存储表的所有列名，显示表的列名
			for (int i = 0; i< pRst->Fields->GetCount(); i++)
			{
				//	cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
				column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
				//使用容器把列名加进去
			}
			cout << endl;


		//	iter++;
		//	strcpy_s(result, sizeof((_bstr_t)pRst->GetCollect(*iter)), (_bstr_t)pRst->GetCollect(*iter));
		//	strcat_s(result, sizeof((char *)((_bstr_t)pRst->GetCollect(*iter))), (char *)((_bstr_t)pRst->GetCollect(*iter)));
			//strcat_s(result, temp);       //把temp的结果连接到result

		}
		else
		{
			cout << "Data is empty!" << endl;
			cout << "kong\n";
			return pRst;
		}
		//先把查到的一个结果存储在temp
	
		//这一段专门用来查密码，在别的调用中都是凑数的


		//对表进行遍历访问,显示表中每一行的内容
		/*
		while (!pRst->EndOfFile)
		{
		vector<_bstr_t>::iterator iter = column_name.begin(); //使用迭代器遍历每一个行的数据
		for (iter; iter != column_name.end(); iter++)
		{
		if (pRst->GetCollect(*iter).vt != VT_NULL)
		{
		cout << (_bstr_t)pRst->GetCollect(*iter) << " ";
		try {
		strcpy_s(temp, (_bstr_t)pRst->GetCollect(*iter));        //先把查到的一个结果存储在temp
		//strcat_s(result, sizeof((char *)((_bstr_t)pRst->GetCollect(*iter))), (char *)((_bstr_t)pRst->GetCollect(*iter)));
		strcat_s(result, sizeof(temp), temp);       //把temp的结果连接到result
		}
		catch (_com_error me)
		{
		cout << endl << me.Description() << endl;
		}

		}
		else
		{
		cout << "NULL" << endl;
		}

		}

		pRst->MoveNext();
		cout << endl;
		}
		*/     //这一大段的作用是循环显示查询到的结果并列表显示
	}
	catch (_com_error &e)

	{
		cout << e.Description() << endl;
		//cout<<e.HelpFile()<<endl;
		return pRst;
	}
	return pRst;                  //释放智能指针之后，不能作为返回值
	m_pConnection->Close();
	printf("查询用户成功\n");

	//释放程序占用的COM 资源  
	::CoUninitialize();

	//return pRst;
}

int  CheckPWD(char *Name, char * PWD)

{   
	
	char temp[MAX];
    char result[4*MAX];
	_RecordsetPtr pRst = select(Name, "UserName", result, "UserInfo");
   // vector<_bstr_t>::iterator iter;
	if (!pRst->BOF)
	{
		pRst->MoveFirst();
		vector<_bstr_t> column_name;

		//存储表的所有列名，显示表的列名
		for (int i = 0; i< pRst->Fields->GetCount(); i++)
		{
			//	cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			//使用容器把列名加进去
		}
		cout << endl;





		vector<_bstr_t>::iterator iter = column_name.begin();

		if (pRst->GetCollect(*iter).vt != VT_NULL)
		{
			iter++;
			cout << (_bstr_t)pRst->GetCollect(*iter) << " ";
			try {
				//if (temp[0] == '\0') //数组为空就粘贴，否则就拼接
					strcpy_s(result, (_bstr_t)pRst->GetCollect(*iter)); //先把查到的一个结果存储在temp
			//	else
			//		strcat_s(temp, (_bstr_t)pRst->GetCollect(*iter));
				//strcat_s(result, sizeof((char *)((_bstr_t)pRst->GetCollect(*iter))), (char *)((_bstr_t)pRst->GetCollect(*iter)));
				//strcat_s(result, sizeof(temp), temp);       //把temp的结果连接到result
			}
			catch (_com_error me)
			{
				cout << endl << me.Description() << endl;
			}
		}


		
	//	iter++;
		//strcpy_s(temp, (_bstr_t)pRst->GetCollect(*iter));
	}
	else
	{
		cout << "Data is empty!" << endl;
		cout << "kong\n";
		return -1;
	}
	//先把查到的一个结果存储在temp
	 //  strcat_s(result, sizeof((char *)((_bstr_t)pRst->GetCollect(*iter))), (char *)((_bstr_t)pRst->GetCollect(*iter)));
	//	strcat_s(result, temp);       //把temp的结果连接到result
		cout << "查询到的结果：：  "<<result << endl;
		cout << "PWD  " << PWD << endl;
		if (Compare(result, PWD) == 0)
			return 0;
		else 
			return 1;
}


int  SelectLog(string &GetMsg ,char KeyWord[], char History[], char sqlcomd[])
{

	char cmd[MAX];

	for (int i = 0; i < MAX; i++)
		cmd[i] = '\0';

	strcpy_s(cmd, 	"select A.OrderNo,A.UserNo ,A.GoodsName,A.IsWin ,CONVERT (varchar(100), B.NowTime,2) from LogTable as A left join LogTable as B on A.UserNo = B.UserNo where A.UserNo = ");


	strcat_s(cmd,  KeyWord);
	
string result;
string No(GetMsg, 1, 11);
cout << No << endl;
_RecordsetPtr His;
//strcpy_s(KeyWord, (char *)No.c_str());
strcpy_s(KeyWord,12,(char *) No.c_str());

//His = select(KeyWord,"UserNo",res,"LogTable");
//	_RecordsetPtr pRst;


//_RecordsetPtr pRst;
_ConnectionPtr  sqlSp;
_bstr_t strConnect = "Provider = SQLOLEDB.1; Integrated Security = SSPI; Persist Security Info = False; Initial Catalog =FUCK; Data Source = .";//连接数据库字符串
																																				//初始化COM库  
::CoInitialize(NULL);
//添加一个指向Connection对象的指针m_pConnection  
_ConnectionPtr m_pConnection(__uuidof(Connection));
//创键Connection对象  
if (FAILED(m_pConnection.CreateInstance(__uuidof(Connection))))
{
	cout << "创键Connection对象时出错\n";
}

try
{
	//连接数据库  
	m_pConnection->Open(strConnect, "", "", adModeUnknown);
}
catch (_com_error e)
{
	cout << "连接数据库时出错\n ";
	cout << e.Description();
	cin.get();

}
try                                   //将查询到的结果存储在记录集
{
	His = m_pConnection->Execute(cmd, NULL, adCmdText);
	vector<_bstr_t> column_name;
	if (!His->BOF)
	{
		His->MoveFirst();


		//存储表的所有列名，显示表的列名
		for (int i = 0; i < His->Fields->GetCount(); i++)
		{
			//	cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
			column_name.push_back(His->Fields->GetItem(_variant_t((long)i))->Name);
			//使用容器把列名加进去
		}
		cout << endl;


		//	iter++;
		//	strcpy_s(result, sizeof((_bstr_t)pRst->GetCollect(*iter)), (_bstr_t)pRst->GetCollect(*iter));
		//	strcat_s(result, sizeof((char *)((_bstr_t)pRst->GetCollect(*iter))), (char *)((_bstr_t)pRst->GetCollect(*iter)));
		//strcat_s(result, temp);       //把temp的结果连接到result

	}

	while (!His->EndOfFile)
	{
		vector<_bstr_t>::iterator iter = column_name.begin(); //使用迭代器遍历每一个行的数据
		for (iter; iter != column_name.end(); iter++)
		{
			if (His->GetCollect(*iter).vt != VT_NULL)
			{
				//cout <<"test  " <<(_bstr_t)His->GetCollect(*iter) << " ";
				try {
					//strcpy_s(temp, sizeof((_bstr_t)His->GetCollect(*iter)), (char *)(_bstr_t)His->GetCollect(*iter));        //先把查到的一个结果存储在temp
					result += (_bstr_t)His->GetCollect(*iter);											 //strcat_s(result, sizeof((char *)((_bstr_t)pRst->GetCollect(*iter))), (char *)((_bstr_t)pRst->GetCollect(*iter)));
					result += "  ";
					//strcat_s(History, sizeof(temp), temp);       //把temp的结果连接到result
				}
				catch (_com_error me)
				{
					cout << endl << me.Description() << endl;
				}

			}
			else
			{
				cout << "NULL" << endl;
			}

		}
		result += "\n";
		His->MoveNext();

	}
}
	catch (_com_error se)
	{

	}
	strcpy_s(History,4*MAX , (char *)result.c_str());
}



int NewUser(char UserName[12], char UserPwd[9],char *x)
{
	if (CheckPWD(UserName, UserPwd) == -1)            //查无此人
	{
		_RecordsetPtr pRst;
		char sqlcommand[1024];
		for (int i = 0; i < 1024; i++)
			sqlcommand[i] = '\0';
		strcpy_s(sqlcommand, "insert into UserInfo values('");

		strcat_s(sqlcommand, UserName);

		strcat_s(sqlcommand, "','");
		strcat_s(sqlcommand, UserPwd);
		strcat_s(sqlcommand, "','0','0xFFFF')");

		
		//_RecordsetPtr pRst;
		_ConnectionPtr  sqlSp;
		_bstr_t strConnect = "Provider = SQLOLEDB.1; Integrated Security = SSPI; Persist Security Info = False; Initial Catalog =FUCK; Data Source = .";//连接数据库字符串
																																						//初始化COM库  
		::CoInitialize(NULL);
		//添加一个指向Connection对象的指针m_pConnection  
		_ConnectionPtr m_pConnection(__uuidof(Connection));
		//创键Connection对象  
		if (FAILED(m_pConnection.CreateInstance(__uuidof(Connection))))
		{
			cout << "创键Connection对象时出错\n";
		}

		try
		{
			//连接数据库  
			m_pConnection->Open(strConnect, "", "", adModeUnknown);
		}
		catch (_com_error e)
		{
			cout << "连接数据库时出错\n ";
			cout << e.Description();
			cin.get();
			return pRst;
		}
		try                                   //将查询到的结果存储在记录集
		{
			pRst = m_pConnection->Execute(sqlcommand, NULL, adCmdText);
		}

		catch (_com_error e)
		{
			cout << e.Description() << endl;
		}
		cout << "新用户注册成功" << endl;
		strcpy_s(x, 11,"注册成功!");

	}
	else if (CheckPWD(UserName, UserPwd) == 1)
	{
		strcpy_s(x, 20, "此手机号已经注册！");
	}
}