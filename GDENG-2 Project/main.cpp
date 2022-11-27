#include "AppWindow.h"

int main()
{
	AppWindow::initialize();
	
	AppWindow::getInstance()->initializeEngine();
	AppWindow::getInstance()->createInterface();
	
	AppWindow::getInstance()->createInitialObjects();
	
	while(AppWindow::getInstance()->isRun())
	{
		AppWindow::getInstance()->broadcast();
	}
	
	AppWindow::terminate();
	return 0;
}