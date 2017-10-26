#pragma once

#include<WinSock2.h>
#include <WS2tcpip.h>
#include <sys/types.h>
#include<stdio.h>
#include<string>
#include<pthread.h>
#include<memory>
#include"funs.h"
#include"NewUser.h"
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "pthreadVC2.lib")
#define MAX 1024
#define PORT  8899
#define LOG_PORT 8900
#define HOST_IP "127.0.0.1"
using namespace std;

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// NewUser 摘要
	/// </summary>
	public ref class NewUser : public System::Windows::Forms::Form
	{
	public:
		NewUser(void)
		{
			InitializeComponent();
			//
			//TODO:  在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~NewUser()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(87, 255);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"注册帐号";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &NewUser::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(87, 54);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 21);
			this->textBox1->TabIndex = 1;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(87, 111);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 21);
			this->textBox2->TabIndex = 2;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(87, 185);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 21);
			this->textBox3->TabIndex = 3;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(240, 111);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 4;
			this->button2->Text = L"获取验证码";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &NewUser::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(28, 63);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 12);
			this->label1->TabIndex = 5;
			this->label1->Text = L"手机号";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(28, 122);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(53, 12);
			this->label2->TabIndex = 6;
			this->label2->Text = L"设置密码";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(28, 188);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(41, 12);
			this->label3->TabIndex = 7;
			this->label3->Text = L"验证码";
			// 
			// NewUser
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(362, 304);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"NewUser";
			this->Text = L"NewUser";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		string mobile;


		w_ConvertToString(textBox1->Text, mobile);


		string sendStr = "CA.exe " + mobile + " 23456";
		system(sendStr.c_str());
	
	}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	char Buff[MAX];
	SOCKET MSGsocClient;
	SOCKADDR_IN MSGaddrSrv;
	//build a sockeet   
	MSGsocClient = socket(AF_INET, SOCK_DGRAM, 0);
	//MSGaddrSrv;        // a instance of SOCKADDR_IN, which is used in format of SOCKADDR.  
	inet_pton(AF_INET, HOST_IP, (void *)&MSGaddrSrv.sin_addr.S_un.S_addr);        //set the host IP  
	MSGaddrSrv.sin_family = AF_INET;     //set the protocol family  
	MSGaddrSrv.sin_port = htons(LOG_PORT);      //set the port number  

												// array to store the data that server feedback.  
	char cSendBuf[MAX];
	char EncryptMSG[MAX];
	int efromlen = sizeof(SOCKADDR);


	//	string Encry = ECB_AESEncryptStr(aesKey, cSendBuf);
	//	strcpy_s(EncryptMSG, MAX, Encry.c_str());
	//	sendto(MSGsocClient, EncryptMSG, strlen(EncryptMSG) + 1, 0, (SOCKADDR*)&MSGaddrSrv, sizeof(SOCKADDR));

	char NamePwd[MAX];
	string temp, temp2;
	w_ConvertToString(textBox1->Text, temp);
	if (temp.size() == 11)
	{
		temp += "@";                                  //@符号表示是注册 ，#表示是登录
		w_ConvertToString(textBox2->Text, temp2);
		temp += temp2;
		strcpy_s(NamePwd, temp.c_str());


		sendto(MSGsocClient, NamePwd, strlen(NamePwd) + 1, 0, (SOCKADDR*)&MSGaddrSrv, sizeof(SOCKADDR));

		recv(MSGsocClient, Buff, MAX, 0);
		string LeftTime = Buff;
		//System::String^ temp= marshal_as<String^>(LeftTime)
		label1->Text = gcnew System::String(Buff);

		MessageBox::Show(gcnew System::String(Buff));


		//收到登录应答消息后

		if (LeftTime == "欢迎老哥登录成功！")
		{
			//	pthread_t ListenToServer;
			//pthread_create(&ListenToServer, NULL, Pro, this);


		}
		//MessageBox(gcnew System::String(Buff));
	}
	else
		MessageBox::Show("账号长度必须是手机号");

}
};
}
