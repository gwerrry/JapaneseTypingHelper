#include "fileio.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <direct.h>
#include <cstdio>

using namespace std;
namespace fs = std::filesystem;

string FileIO::extract_path(std::string path) {
	size_t pos = path.find_last_of("\\/");
	return (string::npos == pos)
		? ""
		: path.substr(0, pos);
}

vector<string> FileIO::read_file(std::string path) {
	vector<string> lines;
	ifstream file(path);
	string line;

	while(getline(file, line)) {
		lines.push_back(line);
	}

	return lines;
}

bool FileIO::delete_file(std::string path) {
	return remove(path.c_str());
}

bool FileIO::create_directory(std::string dir) {
	return _mkdir(dir.c_str());
}

bool FileIO::create_file(std::string path) {
	fstream file;
	file.open(path, ios::out);
	if(!file) {
		//cout << "Error in creating file!!!";
		return false;
	}
	return true;
}

bool FileIO::file_exists(std::string path) {
	return fs::exists(path);
}

void FileIO::clear_file(std::string path) {
	std::ofstream file;
	file.open(path, std::ofstream::out | std::ofstream::trunc);
}

void FileIO::replace_file(std::string path, std::string other_file) {
	vector<string> lines = read_file(other_file);

	clear_file(path);

	ofstream outfile;
	outfile.open(path);
	for(int i = 0; i < lines.size(); i++) {
		outfile << lines[i] << endl;
	}

	delete_file(other_file);
}