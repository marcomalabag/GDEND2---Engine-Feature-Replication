#include "AppWindow.h"

int main()
{
	AppWindow::initialize();
	AppWindow* runningApp = AppWindow::getInstance();
	runningApp->initializeEngine();
	runningApp->createInterface();
	while(runningApp->isRun())
	{
		runningApp->broadcast();
	}
	AppWindow::terminate();
	return 0;
}