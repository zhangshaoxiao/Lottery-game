#include"SQL.h"
using namespace std;

int Insert(void * req, char table[16]) //��һ�������Ǵ����������ݽṹ���ڶ�����������
{
	return 0;
};

int Delete(char DelRow[MAX], char table[16])
{
	return 0;
};
int Compare(char a[], char b[])  //�ַ����ȽϺ�����ϵͳ�Դ��Ĳ�����
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
	char temp[100];       //��ʱ���������ڴ洢��ѯ�Ĳ��ֽ��
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
		return pRst;
	}
	try                                   //����ѯ���Ľ���洢�ڼ�¼��
	{
		pRst = m_pConnection->Execute(sqlcommand, NULL, adCmdText);
		//ִ��SQL�� select * from Table_BB 
		if (!pRst->BOF)
		{
			pRst->MoveFirst();
			vector<_bstr_t> column_name;

			//�洢���������������ʾ�������
			for (int i = 0; i< pRst->Fields->GetCount(); i++)
			{
				//	cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
				column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
				//ʹ�������������ӽ�ȥ
			}
			cout << endl;


		//	iter++;
		//	strcpy_s(result, sizeof((_bstr_t)pRst->GetCollect(*iter)), (_bstr_t)pRst->GetCollect(*iter));
		//	strcat_s(result, sizeof((char *)((_bstr_t)pRst->GetCollect(*iter))), (char *)((_bstr_t)pRst->GetCollect(*iter)));
			//strcat_s(result, temp);       //��temp�Ľ�����ӵ�result

		}
		else
		{
			cout << "Data is empty!" << endl;
			cout << "kong\n";
			return pRst;
		}
		//�ȰѲ鵽��һ������洢��temp
	
		//��һ��ר�����������룬�ڱ�ĵ����ж��Ǵ�����


		//�Ա���б�������,��ʾ����ÿһ�е�����
		/*
		while (!pRst->EndOfFile)
		{
		vector<_bstr_t>::iterator iter = column_name.begin(); //ʹ�õ���������ÿһ���е�����
		for (iter; iter != column_name.end(); iter++)
		{
		if (pRst->GetCollect(*iter).vt != VT_NULL)
		{
		cout << (_bstr_t)pRst->GetCollect(*iter) << " ";
		try {
		strcpy_s(temp, (_bstr_t)pRst->GetCollect(*iter));        //�ȰѲ鵽��һ������洢��temp
		//strcat_s(result, sizeof((char *)((_bstr_t)pRst->GetCollect(*iter))), (char *)((_bstr_t)pRst->GetCollect(*iter)));
		strcat_s(result, sizeof(temp), temp);       //��temp�Ľ�����ӵ�result
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
		*/     //��һ��ε�������ѭ����ʾ��ѯ���Ľ�����б���ʾ
	}
	catch (_com_error &e)

	{
		cout << e.Description() << endl;
		//cout<<e.HelpFile()<<endl;
		return pRst;
	}
	return pRst;                  //�ͷ�����ָ��֮�󣬲�����Ϊ����ֵ
	m_pConnection->Close();
	printf("��ѯ�û��ɹ�\n");

	//�ͷų���ռ�õ�COM ��Դ  
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

		//�洢���������������ʾ�������
		for (int i = 0; i< pRst->Fields->GetCount(); i++)
		{
			//	cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
			//ʹ�������������ӽ�ȥ
		}
		cout << endl;





		vector<_bstr_t>::iterator iter = column_name.begin();

		if (pRst->GetCollect(*iter).vt != VT_NULL)
		{
			iter++;
			cout << (_bstr_t)pRst->GetCollect(*iter) << " ";
			try {
				//if (temp[0] == '\0') //����Ϊ�վ�ճ���������ƴ��
					strcpy_s(result, (_bstr_t)pRst->GetCollect(*iter)); //�ȰѲ鵽��һ������洢��temp
			//	else
			//		strcat_s(temp, (_bstr_t)pRst->GetCollect(*iter));
				//strcat_s(result, sizeof((char *)((_bstr_t)pRst->GetCollect(*iter))), (char *)((_bstr_t)pRst->GetCollect(*iter)));
				//strcat_s(result, sizeof(temp), temp);       //��temp�Ľ�����ӵ�result
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
	//�ȰѲ鵽��һ������洢��temp
	 //  strcat_s(result, sizeof((char *)((_bstr_t)pRst->GetCollect(*iter))), (char *)((_bstr_t)pRst->GetCollect(*iter)));
	//	strcat_s(result, temp);       //��temp�Ľ�����ӵ�result
		cout << "��ѯ���Ľ������  "<<result << endl;
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
try                                   //����ѯ���Ľ���洢�ڼ�¼��
{
	His = m_pConnection->Execute(cmd, NULL, adCmdText);
	vector<_bstr_t> column_name;
	if (!His->BOF)
	{
		His->MoveFirst();


		//�洢���������������ʾ�������
		for (int i = 0; i < His->Fields->GetCount(); i++)
		{
			//	cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
			column_name.push_back(His->Fields->GetItem(_variant_t((long)i))->Name);
			//ʹ�������������ӽ�ȥ
		}
		cout << endl;


		//	iter++;
		//	strcpy_s(result, sizeof((_bstr_t)pRst->GetCollect(*iter)), (_bstr_t)pRst->GetCollect(*iter));
		//	strcat_s(result, sizeof((char *)((_bstr_t)pRst->GetCollect(*iter))), (char *)((_bstr_t)pRst->GetCollect(*iter)));
		//strcat_s(result, temp);       //��temp�Ľ�����ӵ�result

	}

	while (!His->EndOfFile)
	{
		vector<_bstr_t>::iterator iter = column_name.begin(); //ʹ�õ���������ÿһ���е�����
		for (iter; iter != column_name.end(); iter++)
		{
			if (His->GetCollect(*iter).vt != VT_NULL)
			{
				//cout <<"test  " <<(_bstr_t)His->GetCollect(*iter) << " ";
				try {
					//strcpy_s(temp, sizeof((_bstr_t)His->GetCollect(*iter)), (char *)(_bstr_t)His->GetCollect(*iter));        //�ȰѲ鵽��һ������洢��temp
					result += (_bstr_t)His->GetCollect(*iter);											 //strcat_s(result, sizeof((char *)((_bstr_t)pRst->GetCollect(*iter))), (char *)((_bstr_t)pRst->GetCollect(*iter)));
					result += "  ";
					//strcat_s(History, sizeof(temp), temp);       //��temp�Ľ�����ӵ�result
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
	if (CheckPWD(UserName, UserPwd) == -1)            //���޴���
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
			return pRst;
		}
		try                                   //����ѯ���Ľ���洢�ڼ�¼��
		{
			pRst = m_pConnection->Execute(sqlcommand, NULL, adCmdText);
		}

		catch (_com_error e)
		{
			cout << e.Description() << endl;
		}
		cout << "���û�ע��ɹ�" << endl;
		strcpy_s(x, 11,"ע��ɹ�!");

	}
	else if (CheckPWD(UserName, UserPwd) == 1)
	{
		strcpy_s(x, 20, "���ֻ����Ѿ�ע�ᣡ");
	}
}