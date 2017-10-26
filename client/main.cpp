#include "一元夺宝.h"
#include"NewUser.h"

using namespace Client;
[STAThread]
int main()
{

	Application::EnableVisualStyles();
	Application::Run(gcnew 一元夺宝());


	return 0;
}