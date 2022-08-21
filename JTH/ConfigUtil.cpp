#include "ConfigUtil.h"
#include "logger.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <exception>

using namespace std;
namespace fs = filesystem;
using json = nlohmann::json;

string get_current_dir() {
	char buff[FILENAME_MAX]; //create string buffer to hold path
	GetCurrentDir(buff, FILENAME_MAX);
	string current_working_dir(buff);
	return current_working_dir;
}

ConfigFile::ConfigFile(fs::path filePath) {
	m_filePath = filePath;
}

bool ConfigFile::isSameType(value_type type, const type_info& typeinfo) {
	switch (type) {
	case value_type::BOOL: return typeinfo == typeid(bool); break;
	case value_type::INT: return typeinfo == typeid(int); break;
	case value_type::STRING: return typeinfo == typeid(string); break;
	}

	return false;
}

ConfigFile::value_type ConfigFile::ti2vt(const type_info& typeinfo) {
	if (typeinfo == typeid(int)) {
		return value_type::INT;
	}

	if (typeinfo == typeid(bool)) {
		return value_type::BOOL;
	}

	if (typeinfo == typeid(std::string)) {
		return value_type::STRING;
	}

	return value_type::help;
}

template<typename T>
bool ConfigFile::setValue(std::string key, T value) {
	for (ConfigPair& pair : m_data) {
		if (pair.key == key) {
			if (ti2vt(typeid(T)) == pair.type) {
				switch (pair.type) {
					case value_type::BOOL:
						{
							pair.bool_value = value;
							break;
						}
					case value_type::INT:
						{
							pair.int_value = value;
							break;
						}
				}
				LOG(LOG_INFO, "Config value %s in %s was updated", key.c_str(), m_filePath.c_str());
				saveConfig();
				return true;
			}
			else {
				LOG(LOG_ERROR, "Error trying to set a config value in %s at key %s because the types don't match...", m_filePath.c_str(), key.c_str());
				return false;
			}
		}
	}
	LOG(LOG_ERROR, "Error trying to set a config value in %s at key %s because the key doens't exist...", m_filePath.c_str(), key.c_str());
	return false;
}

bool ConfigFile::setInt(std::string key, int value) {
	return setValue<int>(key, value);
}
bool ConfigFile::setBool(std::string key, bool value) {
	return setValue<bool>(key, value);
}
bool  ConfigFile::setString(std::string key, std::string value) {
	for (ConfigPair& pair : m_data) {
		if (pair.key == key) {
			if (value_type::STRING == pair.type) {
				pair.string_value = value;

				LOG(LOG_INFO, "Config value %s in %s was updated", key.c_str(), m_filePath.c_str());
				saveConfig();
				return true;
			}
			else {
				LOG(LOG_ERROR, "Error trying to set a config value in %s at key %s because the types don't match...", m_filePath.c_str(), key.c_str());
				return false;
			}
		}
	}
	LOG(LOG_ERROR, "Error trying to set a config value in %s at key %s because the key doens't exist...", m_filePath.c_str(), key.c_str());
	return false;
}

template<typename T>
bool ConfigFile::addDefaultValue(string key, T value) {
	ConfigPair newValue = { key, ti2vt(typeid(T)), 0, 0, ""};

	switch (newValue.type) {
	case value_type::BOOL: newValue.bool_value = value; break;
	case value_type::INT: newValue.int_value = value; break;
	default: return false;
	}

	m_data.push_back(newValue);

	return true;
}

bool ConfigFile::addDefaultInt(std::string key, int value) {
	return addDefaultValue<int>(key, value);
}

bool ConfigFile::addDefaultBool(std::string key, bool value) {
	return addDefaultValue<bool>(key, value);
}

bool ConfigFile::addDefaultString(std::string key, std::string value) {
	m_data.push_back({ key, value_type::STRING, 0, 0,  value });
	return true;
}

template<typename T>
T ConfigFile::getValue(string key) {
	for (ConfigPair pair : m_data) {
		if (pair.key == key && isSameType(pair.type, typeid(T))) {
			switch (pair.type) {
			case value_type::BOOL: return pair.bool_value; break;
			case value_type::INT: return pair.int_value; break;
			}
		}
	}
	LOG(LOG_FATAL, "Config element at: %s not found. (If the type is mismatching, this error will also be thrown.", key.c_str());
	throw "Config element at: " + key + " not found. (If the type is mismatching, this error will also be thrown.";
}

int ConfigFile::getInt(string key) {
	return getValue<int>(key);
}

bool ConfigFile::getBool(string key) {
	return getValue<bool>(key);
}

string ConfigFile::getString(string key) {
	for (ConfigPair pair : m_data) {
		if (pair.key == key && pair.type == value_type::STRING) {
			return pair.string_value;
		}
	}
	LOG(LOG_FATAL, "Config element at: %s not found. (If the type is mismatching, this error will also be thrown.", key.c_str());
	throw "Config element at: " + key + " not found. (If the type is mismatching, this error will also be thrown.";
}

bool ConfigFile::saveConfig() {
	json fileContents;

	for (ConfigPair pair : m_data) {
		switch (pair.type) {
		case value_type::INT:
		{
			fileContents[pair.key] = pair.int_value;
			break;
		}
		case value_type::BOOL:
		{
			fileContents[pair.key] = pair.bool_value;
			break;
		}
		case value_type::STRING:
		{
			fileContents[pair.key] = pair.string_value;
			break;
		}
		}
	}

	fs::remove(m_filePath);
	ofstream file;
	file.open(m_filePath);
	file << setw(4) << fileContents << endl;
	LOG(LOG_INFO, "Config file at %s saved.", m_filePath.c_str());
	return true;
}

void ConfigFile::fill_defaults() {
	json fileContents;

	for (ConfigPair def : m_data) {
		switch (def.type) {
			case value_type::BOOL:
			{
				fileContents[def.key] = def.bool_value;
				break;
			}
			case value_type::INT:
			{
				fileContents[def.key] = def.int_value;
				break;
			}
			case value_type::STRING:
			{
				fileContents[def.key] = def.string_value;
				break;
			}
		}
	}

	ofstream file;
	file.open(m_filePath);
	file << setw(4) << fileContents << endl;
	file.close();
}

bool ConfigFile::validate_config() {
	ifstream i(m_filePath);

	json jsonFile;
	try {
		i >> jsonFile;
	}
	catch (exception ex) {
		LOG(LOG_FATAL, "Failed to validate config at %s: %s", m_filePath.string().c_str(), ex.what());
		return false;
	}

	bool isValid = true;
	for (ConfigPair def : m_data) {
		if (jsonFile[def.key].is_null()) {
			LOG(LOG_FATAL, "Failed to validate config. Config at %s is missing key: %s", m_filePath.c_str(), def.key.c_str());
			isValid = false;
		}
		else {
			switch (def.type) {
				case value_type::BOOL:
				{
					if (!jsonFile[def.key].is_boolean()) {
						LOG(LOG_ERROR, "Failed to validate config. Config value at %s for key %s is not a bool", m_filePath.c_str(), def.key.c_str());
						isValid = false;
					}
					break;
				}
				case value_type::INT:
				{
					if (!jsonFile[def.key].is_number_integer()) {
						LOG(LOG_ERROR, "Failed to validate config. Config value at %s for key %s is not an int", m_filePath.c_str(), def.key.c_str());
						isValid = false;
					}
					break;
				}
				case value_type::STRING:
				{
					if (!jsonFile[def.key].is_string()) {
						LOG(LOG_ERROR, "Failed to validate config. Config value at %s for key %s is not a string", m_filePath.c_str(), def.key.c_str());
						isValid = false;
					}
					break;
				}
			}
		}
	}

	return isValid;
}

bool ConfigFile::load_config() {
	ifstream i(m_filePath);

	json jsonFile;
	try {
		i >> jsonFile;
	}
	catch (exception ex) {
		LOG(LOG_FATAL, "Failed to load config. Config file at %s is invalid: %s", m_filePath.c_str(), ex.what());
		return false;
	}

	for (ConfigPair& def : m_data) {
		switch (def.type) {
			case value_type::BOOL:
			{
				def.bool_value = jsonFile[def.key];
				break;
			}
			case value_type::INT:
			{
				def.int_value = jsonFile[def.key];
				break;
			}
			case value_type::STRING:
			{
				def.string_value = jsonFile[def.key];
				break;
			}
		}
	}
	return true;
}

bool ConfigFile::setup() {
	
	if (!fs::exists(m_filePath)) {
		std::string dir = m_filePath.string();
		dir = dir.substr(0, dir.find_last_of("/\\"));
		
		try {
			if (fs::create_directory(dir)) {
				LOG(LOG_INFO, "Config directory at %s created", dir.c_str());
			}
			if (!fs::exists(dir)) {
				LOG(LOG_FATAL, "Failed to create directory at %s", dir.c_str());
				return false;
			}
		}
		catch (const std::exception& e) {
			LOG(LOG_FATAL, "Encountered an error when trynig to create config directory at %s: %s", dir.c_str(), e.what());
			return false;
		}
		fill_defaults();
	}
	else {
		if (!validate_config()) {
			LOG(LOG_FATAL, "Config file at %s was invalid. The config will be automatically reset.");
			fs::remove(m_filePath);
			fill_defaults();
		}
	}

	return load_config();
}