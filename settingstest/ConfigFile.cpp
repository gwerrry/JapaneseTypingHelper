#include "ConfigFile.h"
#include "fileio.h"
#include <typeinfo>
#include <filesystem>

using namespace std;
using namespace FileIO;
using namespace BreakfastParser;
namespace fs = filesystem;

value_types ti2e(const type_info& info) {
	if(info == typeid(int)) return CONFIG_INT;
	if(info == typeid(ccptr)) return CONFIG_STR;
	if(info == typeid(bool)) return CONFIG_BOOL;
	else return INVALID_CONFIG_TYPE;
}

ConfigFile::ConfigFile(string filePath) {
	m_filePath = filePath;
	setup();
	load();
}

bool ConfigFile::load() {
	if(!file_exists(m_filePath)) {
		//print error message
		return false;
	}

	if(!validate_file(m_filePath)) {
		//print error
		return false;
	}

	vector<config_element>* elements = read_config(m_filePath);

	for(int i = 0; i < elements->size(); i++) {
		m_data.push_back(elements->at(i));
	}

	delete elements;
	return true;
}

bool ConfigFile::setup() {
	std::string path = extract_path(m_filePath);

	create_directory(path);

	create_file(m_filePath);

	if(!file_exists(m_filePath)) {
		//print error message
		return false;
	}

	return true;
}

template<typename T>
bool ConfigFile::setValue(string key, T value) {
	removeValue(key);
	return addValue<T>(key, value);
}

bool ConfigFile::setInt(string key, int value) {
	return setValue<int>(key, value);
}
bool ConfigFile::setBool(string key, bool value) {
	return setValue<bool>(key, value);
}
bool ConfigFile::setString(string key, ccptr value) {
	return setValue<ccptr>(key, value);
}

template<typename T>
bool ConfigFile::addValue(string key, T value) {
	if(!file_exists(m_filePath)) {
		//print some error message
		return false;
	}
	if(valueExists(key)) {
		//print a debug saying that the value already exists
		return false;
	}
	config_element element = {};
	element.key = key;
	element.value = (void*)&value;
	element.type = ti2e(typeid(T));
	element.isValid = true;
	m_data.push_back(element);

	return add_config_value(m_filePath, element);
}

bool ConfigFile::addInt(string key, int value) {
	return addValue<int>(key, value);
}

bool ConfigFile::addBool(string key, bool value) {
	return addValue<bool>(key, value);
}

bool ConfigFile::addString(string key, ccptr value) {
	return addValue<ccptr>(key, value);
}

bool ConfigFile::removeValue(string key) {
	if(key == "") {
		return false;
	}
	vector<config_element>::iterator it;

	for(it = m_data.begin(); it != m_data.end(); it++) {
		if(it->key == key) {
			m_data.erase(it);
			break;
		}
	}

	return remove_config_value(m_filePath, key);
}

bool ConfigFile::valueExists(string key) {
	for(config_element current : m_data) {
		if(current.key == key) {
			return true;
		}
	}
	return false;
}

template<typename T>
bool ConfigFile::getValue(string key, T& buffer) {
	for(config_element current : m_data) {
		if(current.key == key) {
			if(current.type == ti2e(typeid(T))) {
				buffer = (T)current.value;
				return true;
			}
		}
	}
	return false;
}

bool ConfigFile::getValue(string key, void* buffer) {
	return getValue<void*>(key, buffer);
}

bool ConfigFile::getInt(string key, int& buffer) {
	return getValue<int>(key, buffer);
}

bool ConfigFile::getBool(string key, bool& buffer) {
	return getValue<bool>(key, buffer);
}

string ConfigFile::getString(string key) {
	for(config_element current : m_data) {
		if(current.key == key) {
			if(current.type == CONFIG_STR) {
				return string((ccptr)current.value);
			}
			break;
		}
	}
	return "";
}