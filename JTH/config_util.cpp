/**
 * @file config_util.cpp
 * @author gwerry
 * @brief Contains the ConfigFile class implementations.
 * @version 1.0.0
 * @date 2024/04/07
 *
 * Copyright 2024 gwerry
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "config_util.hpp"
#include "logger.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <exception>

using namespace std;
namespace fs = filesystem;
using json = nlohmann::json;

string getCurrentDir() {
	char buff[FILENAME_MAX]; //create string buffer to hold path
	if (!GetCurrentDir(buff, FILENAME_MAX)) {
		LOG(LOG_FATAL, "There was an error getting the current directory of the executable.");
		exit(-124);
	}
	string current_working_dir(buff);
	return current_working_dir;
}

ConfigFile::ConfigFile(fs::path filePath) {
	m_filePath = filePath;
}

bool ConfigFile::isSameType(ValueType type, const type_info& typeinfo) {
	switch (type) {
		case ValueType::BOOL: return typeinfo == typeid(bool); break;
		case ValueType::INT: return typeinfo == typeid(int); break;
		case ValueType::STRING: return typeinfo == typeid(string); break;
	}

	return false;
}

ConfigFile::ValueType ConfigFile::ti2vt(const type_info& typeinfo) {
	if (typeinfo == typeid(int)) return ValueType::INT;
	
	if (typeinfo == typeid(bool)) return ValueType::BOOL;
	
	if (typeinfo == typeid(std::string)) return ValueType::STRING;
	
	return ValueType::NONE;
}

template<typename T>
bool ConfigFile::setValue(std::string key, T value) {
	for (ConfigPair& pair : m_data) {
		if (pair.key == key) {
			if (ti2vt(typeid(T)) == pair.type) {
				switch (pair.type) {
					case ValueType::BOOL: {
						pair.bool_value = value;
						break;
					}
					case ValueType::INT: {
						pair.int_value = value;
						break;
					}
					default: {}
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
			if (ValueType::STRING == pair.type) {
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
		case ValueType::BOOL: newValue.bool_value = value; break;
		case ValueType::INT: newValue.int_value = value; break;
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
	m_data.push_back({ key, ValueType::STRING, 0, 0,  value });
	return true;
}

template<typename T>
T ConfigFile::getValue(string key) {
	for (ConfigPair pair : m_data) {
		if (pair.key == key && isSameType(pair.type, typeid(T))) {
			switch (pair.type) {
				case ValueType::BOOL: return pair.bool_value; break;
				case ValueType::INT: return pair.int_value; break;
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
		if (pair.key == key && pair.type == ValueType::STRING) {
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
			case ValueType::INT: {
				fileContents[pair.key] = pair.int_value;
				break;
			}
			case ValueType::BOOL: {
				fileContents[pair.key] = pair.bool_value;
				break;
			}
			case ValueType::STRING: {
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

void ConfigFile::fillDefaults() {
	json fileContents;

	for (ConfigPair def : m_data) {
		switch (def.type) {
			case ValueType::BOOL: {
				fileContents[def.key] = def.bool_value;
				break;
			}
			case ValueType::INT: {
				fileContents[def.key] = def.int_value;
				break;
			}
			case ValueType::STRING: {
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

bool ConfigFile::validateConfig() {
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
				case ValueType::BOOL: {
					if (!jsonFile[def.key].is_boolean()) {
						LOG(LOG_ERROR, "Failed to validate config. Config value at %s for key %s is not a bool", m_filePath.c_str(), def.key.c_str());
						isValid = false;
					}
					break;
				}
				case ValueType::INT: {
					if (!jsonFile[def.key].is_number_integer()) {
						LOG(LOG_ERROR, "Failed to validate config. Config value at %s for key %s is not an int", m_filePath.c_str(), def.key.c_str());
						isValid = false;
					}
					break;
				}
				case ValueType::STRING: {
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

bool ConfigFile::loadConfig() {
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
			case ValueType::BOOL: {
				def.bool_value = jsonFile[def.key];
				break;
			}
			case ValueType::INT: {
				def.int_value = jsonFile[def.key];
				break;
			}
			case ValueType::STRING: {
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
			if (fs::create_directory(dir)) LOG(LOG_INFO, "Config directory at %s created", dir.c_str());
			
			if (!fs::exists(dir)) {
				LOG(LOG_FATAL, "Failed to create directory at %s", dir.c_str());
				return false;
			}
		}
		catch (const std::exception& e) {
			LOG(LOG_FATAL, "Encountered an error when trynig to create config directory at %s: %s", dir.c_str(), e.what());
			return false;
		}
		fillDefaults();
	}
	else if (!validateConfig()) {
		LOG(LOG_FATAL, "Config file at %s was invalid. The config will be automatically reset.");
		fs::remove(m_filePath);
		fillDefaults();
	}

	return loadConfig();
}