#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "global.h"

class ConfigFile {
private:
	template<typename T>
	bool addValue(std::string key, T value);

	template<typename T>
	bool setValue(std::string key, T value);

	template<typename T>
	bool getValue(std::string key, T& buffer);

	bool getValue(std::string key, void* buffer);
	bool setup();
	bool load();
public:
	ConfigFile() {}

	ConfigFile(std::string filePath);

	bool removeValue(std::string key);
	bool valueExists(std::string key);

	bool addInt(std::string key, int value);
	bool addBool(std::string key, bool value);
	bool addString(std::string key, ccptr value);

	bool setInt(std::string key, int value);
	bool setBool(std::string key, bool value);
	bool setString(std::string key, ccptr value);

	bool getInt(std::string key, int& buffer);
	bool getBool(std::string key, bool& buffer);
	std::string getString(std::string key);

private:
	std::filesystem::path m_filePath;
};