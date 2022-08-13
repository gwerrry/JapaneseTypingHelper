#include "ConfigFile.h"
#include "logger.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
namespace fs = filesystem;
using json = nlohmann::json;

ConfigFile::ConfigFile(fs::path filePath) {
	m_filePath = filePath;
}

bool ConfigFile::isSameType(value_type type, const type_info& typeinfo) {
	switch(type) {
		case value_type::BOOL: return typeinfo == typeid(bool); break;
		case value_type::INT: return typeinfo == typeid(int); break;
		case value_type::STRING: return typeinfo == typeid(string); break;
	}

	return false;
}

ConfigFile::value_type ConfigFile::ti2vt(const type_info& typeinfo) {
	if(typeinfo == typeid(int)) {
		return value_type::INT;
	}

	if(typeinfo == typeid(bool)) {
		return value_type::BOOL;
	}

	if(typeinfo == typeid(std::string)) {
		return value_type::STRING;
	}

	return value_type::help;
}

template<typename T>
bool ConfigFile::setValue(std::string key, T value) {
	for(ConfigPair pair : m_data) {
		if(pair.key == key) {
			if(ti2vt(typeid(T)) == pair.type) {
				switch(pair.type) {
					case value_type::BOOL:
						{
							if(pair.bool_value) delete pair.bool_value;
							pair.bool_value = new bool(value);
							break;
						}
					case value_type::INT:
						{
							if(pair.int_value) delete pair.int_value;
							pair.int_value = new int(value);
							break;
						}
				}
				LOG(LOG_INFO, "Config value %s in %s was updated", key.c_str(), m_filePath.c_str());
				saveConfig();
				return true;
			} else {
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
	for(ConfigPair pair : m_data) {
		if(pair.key == key) {
			if(value_type::STRING == pair.type) {
				if(pair.string_value) delete pair.string_value;
				pair.string_value = new string(value);

				LOG(LOG_INFO, "Config value %s in %s was updated", key.c_str(), m_filePath.c_str());
				saveConfig();
				return true;
			} else {
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
	ConfigPair newValue = {key, ti2vt(typeid(T)), NULL, NULL, NULL};

	switch(newValue.type) {
		case value_type::BOOL: newValue.bool_value = new bool(value); break;
		case value_type::INT: newValue.int_value = new int(value); break;
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
	m_data.push_back({key, value_type::STRING, NULL, NULL,  new string(value)});
	return true;
}

template<typename T>
bool ConfigFile::getValue(string key, T& buffer) {
	for(ConfigPair pair : m_data) {
		if(pair.key == key && isSameType(pair.type, typeid(T))) {
			switch(pair.type) {
				case value_type::BOOL: buffer = *pair.bool_value; return true; break;
				case value_type::INT: buffer = *pair.int_value; return true;  break;
			}
		}
	}
	return false;
}

bool ConfigFile::getInt(string key, int& buffer) {
	return getValue<int>(key, buffer);
}

bool ConfigFile::getBool(string key, bool& buffer) {
	return getValue<bool>(key, buffer);
}

bool ConfigFile::getString(string key, string& buffer) {
	for(ConfigPair pair : m_data) {
		if(pair.key == key && pair.type == value_type::STRING) {
			buffer = *pair.string_value;
			return true;
		}
	}
	return false;
}

bool ConfigFile::saveConfig() {
	ifstream i(m_filePath);

	json jsonFile;
	try {
		i >> jsonFile;
	} catch(exception ex) {
		LOG(LOG_FATAL, "Failed to save config. Config file at %s is invalid: %s", m_filePath.c_str(), ex.what());
		return false;
	}

	for(ConfigPair pair : m_data) {
		switch(pair.type) {
			case value_type::INT:
				{
					jsonFile[pair.key] = *pair.int_value;
					break;
				}
			case value_type::BOOL:
				{
					jsonFile[pair.key] = *pair.bool_value;
					break;
				}
			case value_type::STRING:
				{
					jsonFile[pair.key] = *pair.string_value;
					break;
				}
		}
	}

	ofstream file;
	file.open(m_filePath);
	file << setw(4) << jsonFile << endl;
	LOG(LOG_INFO, "Config file at %s saved.", m_filePath.c_str());
	return true;
}

void ConfigFile::fill_defaults() {
	json fileContents;

	for(ConfigPair def : m_data) {
		switch(def.type) {
			case value_type::BOOL:
				{
					fileContents[def.key] = *def.bool_value;
					break;
				}
			case value_type::INT:
				{
					fileContents[def.key] = *def.int_value;
					break;
				}
			case value_type::STRING:
				{
					fileContents[def.key] = *def.string_value;
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
	} catch(exception ex) {
		LOG(LOG_FATAL, "Failed to validate config at . Config file at %s is invalid: %s", m_filePath.c_str(), ex.what());
		return false;
	}

	bool isValid = true;
	for(ConfigPair def : m_data) {
		if(jsonFile[def.key].is_null()) {
			LOG(LOG_FATAL, "Config at %s is missing key: %s", m_filePath.c_str(), def.key.c_str());
			isValid = false;
		} else {
			switch(def.type) {
				case value_type::BOOL:
					{
						if(!jsonFile[def.key].is_boolean()) {
							LOG(LOG_ERROR, "Config value at %s for key %s is not a bool", m_filePath.c_str(), def.key.c_str());
							isValid = false;
						}
						break;
					}
				case value_type::INT:
					{
						if(!jsonFile[def.key].is_number_integer()) {
							LOG(LOG_ERROR, "Config value at %s for key %s is not an int", m_filePath.c_str(), def.key.c_str());
							isValid = false;
						}
						break;
					}
				case value_type::STRING:
					{
						if(!jsonFile[def.key].is_string()) {
							LOG(LOG_ERROR, "Config value at %s for key %s is not a string", m_filePath.c_str(), def.key.c_str());
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
	} catch(exception ex) {
		LOG(LOG_FATAL, "Config file at %s is invalid: %s", m_filePath.c_str(), ex.what());
		return false;
	}

	for(ConfigPair def : m_data) {
		switch(def.type) {
			case value_type::BOOL:
				{
					if(def.bool_value) delete def.bool_value;
					def.bool_value = new bool(jsonFile[def.key]);
					break;
				}
			case value_type::INT:
				{
					if(def.int_value) delete def.int_value;
					def.int_value = new int(jsonFile[def.key]);
					break;
				}
			case value_type::STRING:
				{
					if(def.string_value) delete def.string_value;
					def.string_value = new string(jsonFile[def.key]);
					break;
				}
		}
	}
	return true;
}

bool ConfigFile::setup() {
	if(!fs::exists(m_filePath)) {
		fs::create_directories(m_filePath.parent_path());
		fstream file;
		file.open(m_filePath.string());
		file.close();
		fill_defaults();
	} else {
		if(!validate_config()) {
			LOG(LOG_FATAL, "Config file at %s was invalid. The config will be automatically reset.");
			fs::remove(m_filePath);
			fill_defaults();
		}
	}

	return load_config();
}