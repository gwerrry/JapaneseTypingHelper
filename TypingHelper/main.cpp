#include "typinghelper.h"
#include "logger.h"
#include "uibackend.h"

#include <QtWidgets/QApplication>
#include <Windows.h>

void createConsole() {
	AllocConsole();
	FILE* pFileCon = NULL;
	pFileCon = freopen("CONOUT$", "w", stdout);

	COORD coordInfo;
	coordInfo.X = 130;
	coordInfo.Y = 9000;

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coordInfo);
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);
}

int main(int argc, char* argv[]) {

	//testing stuff
	createConsole();
	//end testing stuff

	QApplication a(argc, argv);
	TypingHelper w;

	w.show();
	return a.exec();
}
