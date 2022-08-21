#pragma once
#include <string>
#include <vector>
#include <filesystem>

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#elif __linux__
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

std::string get_current_dir();

class ConfigFile {
public:
	typedef enum class ConfigType {
		STRING,
		INT,
		BOOL,
		help
	} value_type;

private:
	typedef struct config_element {
		std::string key;
		value_type type;
		bool bool_value;
		int int_value;
		std::string string_value;
	} ConfigPair;

	std::filesystem::path m_filePath;
	std::vector<ConfigPair> m_data;

	value_type ti2vt(const type_info& typeinfo);
	bool isSameType(value_type type, const type_info& typeinfo);

	template<typename T>
	bool setValue(std::string key, T value);

	template<typename T>
	bool addDefaultValue(std::string key, T value);

	template<typename T>
	T getValue(std::string key);

	bool load_config();
	bool validate_config();
	void fill_defaults();
	bool saveConfig();

public:

	ConfigFile() {}

	ConfigFile(std::filesystem::path filePath);
	bool setup();

	bool addDefaultInt(std::string key, int value);
	bool addDefaultBool(std::string key, bool value);
	bool addDefaultString(std::string key, std::string value);

	bool setInt(std::string key, int value);
	bool setBool(std::string key, bool value);
	bool setString(std::string key, std::string value);

	int getInt(std::string key);
	bool getBool(std::string key);
	std::string getString(std::string key);
};