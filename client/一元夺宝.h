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
extern "C"
//void * Pro(void *X);


/*************************************************************************************



消息封装还需要完善


****************************************************************/




namespace Client {


	

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	//using namespace  System.Windows.Forms;
	/// <summary>
	/// 一元夺宝 摘要
	/// </summary>

	public ref class 一元夺宝 : public System::Windows::Forms::Form
	{
	public:
	

	private: System::Windows::Forms::Button^  button2;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;


	private: System::ComponentModel::BackgroundWorker^  backgroundWorker2;

	public:
		char *Buff;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	public:
		int ttt = 100;
		一元夺宝(void)
		{
			InitializeComponent();
		
			//
			//TODO:  在此处添加构造函数代码
			//
		}
		
		int  Listen()
		{


			SOCKET MSGsocClient;

			SOCKADDR_IN MSGaddrSrv;
			char BBBB[MAX];
			//build a sockeet   
			MSGsocClient = socket(AF_INET, SOCK_DGRAM, 0);
			//MSGaddrSrv;        // a instance of SOCKADDR_IN, which is used in format of SOCKADDR.  
			inet_pton(AF_INET, HOST_IP, (void *)&MSGaddrSrv.sin_addr.S_un.S_addr);        //set the host IP  
			MSGaddrSrv.sin_family = AF_INET;     //set the protocol family  
			MSGaddrSrv.sin_port = htons(PORT);      //set the port number  

													// array to store the data that server feedback.  
			char cSendBuf[MAX];

			int efromlen = sizeof(SOCKADDR);
			char MSSG[1024] = "#12345678909$00401%4232";
			//	string Encry = ECB_AESEncryptStr(aesKey, cSendBuf);
			//	strcpy_s(EncryptMSG, MAX, Encry.c_str());
			//	sendto(MSGsocClient, EncryptMSG, strlen(EncryptMSG) + 1, 0, (SOCKADDR*)&MSGaddrSrv, sizeof(SOCKADDR));

			sendto(MSGsocClient, MSSG, strlen(MSSG) + 1, 0, (SOCKADDR*)&MSGaddrSrv, sizeof(SOCKADDR));
			while (true)
			{
				//MessageBox::Show("test");
				recv(MSGsocClient, BBBB, MAX, 0);


				//string LeftTime = BBBB;
				//System::String^ temp= marshal_as<String^>(LeftTime)
				//	label1->Text = gcnew System::String(BBBB);
				if (strlen(BBBB) < 3)       //如果传来的消息是剩余秒数
				{
					ttt = atoi(BBBB);
					//	this->progressBar1->Value = ttt;
					timer1->Start();
					MessageBox::Show(gcnew System::String(BBBB) + "s后结束本波");
				}
				else   //传来的消息是中奖消息
				{
					MessageBox::Show(gcnew System::String(BBBB));
					backgroundWorker1->CancelAsync();
				}
			}
			return 0;
		};
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~一元夺宝()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::WebBrowser^  webBrowser1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::Timer^  timer1;




	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::ComponentModel::IContainer^  components;
	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->backgroundWorker2 = (gcnew System::ComponentModel::BackgroundWorker());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// webBrowser1
			// 
			this->webBrowser1->Dock = System::Windows::Forms::DockStyle::Left;
			this->webBrowser1->Location = System::Drawing::Point(0, 0);
			this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser1->Name = L"webBrowser1";
			this->webBrowser1->Size = System::Drawing::Size(770, 569);
			this->webBrowser1->TabIndex = 0;
			this->webBrowser1->Url = (gcnew System::Uri(L"http://localhost:8080/index.html", System::UriKind::Absolute));
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(1048, 157);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"登录";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &一元夺宝::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(333, 57);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 12);
			this->label1->TabIndex = 2;
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &一元夺宝::timer1_Tick);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(1048, 23);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 21);
			this->textBox1->TabIndex = 3;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(1048, 83);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 21);
			this->textBox2->TabIndex = 4;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(1154, 21);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L"监听服务器";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &一元夺宝::button2_Click);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &一元夺宝::backgroundWorker1_DoWork);
			// 
			// backgroundWorker2
			// 
			this->backgroundWorker2->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &一元夺宝::backgroundWorker2_DoWork);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(1048, 375);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 7;
			this->button3->Text = L"参与抢购";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &一元夺宝::button3_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::Cross;
			this->pictureBox1->ImageLocation = L"http://localhost:8080/test.jpg";
			this->pictureBox1->Location = System::Drawing::Point(901, 21);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(77, 76);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 8;
			this->pictureBox1->TabStop = false;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(1154, 375);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 9;
			this->button4->Text = L"历史记录";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &一元夺宝::button4_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(793, 235);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(436, 109);
			this->richTextBox1->TabIndex = 10;
			this->richTextBox1->Text = L"";
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(1154, 157);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(75, 23);
			this->button6->TabIndex = 12;
			this->button6->Text = L"注册";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &一元夺宝::button6_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(996, 32);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 12);
			this->label2->TabIndex = 14;
			this->label2->Text = L"手机号";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(998, 92);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(29, 12);
			this->label3->TabIndex = 15;
			this->label3->Text = L"密码";
			// 
			// 一元夺宝
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1241, 569);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->webBrowser1);
			this->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Name = L"一元夺宝";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"抢呀";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &一元夺宝::一元夺宝_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	
#pragma endregion
		
	
	private: System::Void webBrowser1_DocumentCompleted(System::Object^  sender, System::Windows::Forms::WebBrowserDocumentCompletedEventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		
			Buff = new char[1024];
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
				temp += "#";
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
			

	private: System::Void 一元夺宝_Load(System::Object^  sender, System::EventArgs^  e) {
		
	}

		
			
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	//BackgroundWorker backgroundWorker1 = new BackgroundWorker();
//	backgroundWorker1.RunWokerAsync(2000/*参数是可选的*/);
	button2->Enabled = false;
	this->backgroundWorker1->WorkerSupportsCancellation = true;

	this->backgroundWorker1->RunWorkerAsync(1);
	

	//backgroundWorker1->RunWorkerAsync();
	
	//backgroundWorker1.RunWorkerAsync();
}



private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
	
	Listen();
}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	//strcpy(Buff, (char *)((int)Buff - 1));
	//label1->Text = gcnew System::String(Buff);
//	label1->Text->Insert(0, "r");

	ttt--;
	char test[5];
	itoa(ttt, test, 10);
	
	cout << test << endl;
	
	//label1->Text = gcnew System::String("fsdfsdf");
	//label1->Text = gcnew System::String(test);
	//label1->Update();
	//Sleep(1000);
	//if (ttt <= 0)
		//timer1->Stop();
}
		




private: System::Void backgroundWorker2_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
	// progressBar1
	
		
	}
	// 

private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	SOCKET MSGsocClient;

	SOCKADDR_IN MSGaddrSrv;
	char BBBB[MAX];
	//build a sockeet   
	MSGsocClient = socket(AF_INET, SOCK_DGRAM, 0);
	//MSGaddrSrv;        // a instance of SOCKADDR_IN, which is used in format of SOCKADDR.  
	inet_pton(AF_INET, HOST_IP, (void *)&MSGaddrSrv.sin_addr.S_un.S_addr);        //set the host IP  
	MSGaddrSrv.sin_family = AF_INET;     //set the protocol family  
	MSGaddrSrv.sin_port = htons(PORT);      //set the port number  

											// array to store the data that server feedback.  
	char cSendBuf[MAX];

	int efromlen = sizeof(SOCKADDR);
	char MSSG[1024] = "#12345678909$34453%4232";
	//	string Encry = ECB_AESEncryptStr(aesKey, cSendBuf);
	//	strcpy_s(EncryptMSG, MAX, Encry.c_str());
	//	sendto(MSGsocClient, EncryptMSG, strlen(EncryptMSG) + 1, 0, (SOCKADDR*)&MSGaddrSrv, sizeof(SOCKADDR));

	sendto(MSGsocClient, MSSG, strlen(MSSG) + 1, 0, (SOCKADDR*)&MSGaddrSrv, sizeof(SOCKADDR));
	recv(MSGsocClient, BBBB, MAX, 0);


		MessageBox::Show(gcnew System::String(BBBB));
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {


	char History[MAX];
	SOCKET MSGsocClient;
	SOCKADDR_IN MSGaddrSrv;
	//build a sockeet   
	MSGsocClient = socket(AF_INET, SOCK_DGRAM, 0);
	//MSGaddrSrv;        // a instance of SOCKADDR_IN, which is used in format of SOCKADDR.  
	inet_pton(AF_INET, HOST_IP, (void *)&MSGaddrSrv.sin_addr.S_un.S_addr);        //set the host IP  
	MSGaddrSrv.sin_family = AF_INET;     //set the protocol family  
	MSGaddrSrv.sin_port = htons(LOG_PORT);      //set the port number  

												// array to store the data that server feedback.  

	int efromlen = sizeof(SOCKADDR);


	//	string Encry = ECB_AESEncryptStr(aesKey, cSendBuf);
	//	strcpy_s(EncryptMSG, MAX, Encry.c_str());
	//	sendto(MSGsocClient, EncryptMSG, strlen(EncryptMSG) + 1, 0, (SOCKADDR*)&MSGaddrSrv, sizeof(SOCKADDR));
	string temp2;
	string temp;
	temp = "H";
	w_ConvertToString(textBox1->Text, temp2);
	//w_ConvertToString(textBox1->Text, temp2);
	temp += temp2;

		sendto(MSGsocClient, temp.c_str(), strlen(temp.c_str()) + 1, 0, (SOCKADDR*)&MSGaddrSrv, sizeof(SOCKADDR));

		recv(MSGsocClient, History, 4*MAX, 0);
		richTextBox1->Text =gcnew System::String(History);
};
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
	NewUser logIn;
	//this->Hide();
	logIn.ShowDialog();        

}
};






}
