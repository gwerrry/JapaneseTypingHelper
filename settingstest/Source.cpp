#include "ConfigFile.h"
#include "fileio.h"
#include "fileparser.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#pragma warning(disable : 4996)

#define WIN32
#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define TEST_CONFIGFILE_CLASS
#ifdef TEST_CONFIGFILE_CLASS
int main() {
	ConfigFile file("a.txt");
	bool buf = 1;

	file.setBool("oogabooga", true);
	file.getBool("oogabooga", buf);
	std::cout << buf << std::endl;

	file.setBool("oogabooga", false);
	file.getBool("oogabooga", buf);
	std::cout << buf << std::endl;
}
#endif