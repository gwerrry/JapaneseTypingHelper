#include "mainwindow.h"
#include "logger.h"
#include "backend.h"
#include "ConfigFile.h"
#include <QtWidgets/QApplication>

#ifdef WIN32

#include <Windows.h>
#include <direct.h>

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

#define getworkingdir _getcwd

#endif

#ifdef LINUX
#include <unistd.h>

//lauch this from terminal if you want debug cause im a lazy bitch
void createConsole() {}

#define getworkingdir getcwd

#endif

ConfigFile* settings;

std::string GetCurrentDir() {
	char buf[256];
	getworkingdir(buf, sizeof(buf));
	return std::string(buf);
}

int main(int argc, char* argv[]) {
	//testing stuff
	createConsole();
	//end testing stuff
	std::string path = GetCurrentDir();

	path += "\\asd\\settings.json";

	settings = new ConfigFile(path);
	settings->addDefaultString("", "asdf");

	LOG(LOG_INFO, "Returned %d", settings->setup());

	QApplication a(argc, argv);
	TypingHelper w;

	w.show();
	return a.exec();
}