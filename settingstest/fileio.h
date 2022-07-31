#pragma once
#include "global.h"
#include <vector>
#include <string>

namespace FileIO {
	std::vector<std::string> read_file(std::string path);
	bool delete_file(std::string path);
	bool create_file(std::string path);
	bool file_exists(std::string path);
	bool create_directory(std::string dir);
	void replace_file(std::string path, std::string other_file);
	void clear_file(std::string path);
	std::string extract_path(std::string path);
}