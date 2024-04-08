/**
 * @file config_util.hpp
 * @author gwerry
 * @brief Contains the ConfigFile class.
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

std::string getCurrentDir();

/**
 * @brief ConfigFile class.
 * Holds all functions for manipulating a config file.
 */
class ConfigFile {
public:
	typedef enum class ConfigValueType {
		STRING,
		INT,
		BOOL,
		NONE
	} ValueType;

private:
	/**
	 * @brief ConfigPair struct.
	 * Holds the key, value, and the type of the value in the config pair.
	 */
	typedef struct config_element {
		std::string key;
		ValueType type;
		bool bool_value;
		int int_value;
		std::string string_value;
	} ConfigPair;

	std::filesystem::path m_filePath;
	std::vector<ConfigPair> m_data;

	/**
	 * @brief Converts provided type_info to the corresponding value_type.
	 * 
	 * @param typeinfo - type_info to convert to a ValueType.
	 * @return ValueType of the type_info provided. Can return ValueType::NONE if it isn't supported.
 	 */
	ValueType ti2vt(const type_info& typeinfo);
	
	/**
	 * @brief Checks if the ValueType is the same as the type_info.
	 * 
	 * @param type - ValueType to compare.
	 * @param typeinfo - type_info to compare.
	 * @return true if they are the same. False otherwise.
	 */
	bool isSameType(ValueType type, const type_info& typeinfo);

	/**
	 * @brief Sets the value in the config.
	 * 
	 * @tparam T the type of the value.
	 * @param key - Key of the value.
	 * @param value - The value to set.
	 * @return true if it set the value. False otherwise.
	 */
	template<typename T>
	bool setValue(std::string key, T value);

	/**
	 * @brief Adds a default value to the config.
	 *
	 * @tparam T the type of the value.
	 * @param key - Key of the value.
	 * @param value - The value to set.
	 * @return true if it added the value. False otherwise.
	 */
	template<typename T>
	bool addDefaultValue(std::string key, T value);

	/**
	 * @brief Get the value in the config from the key.
	 *
	 * @tparam T the type of the value.
	 * @param key - Key of the value.
	 * @return The value.
	 */
	template<typename T>
	T getValue(std::string key);

	/**
	 * @brief Loads the config.
	 * @return true if the config was loaded. false otherwise.
	 */
	bool loadConfig();

	/**
	 * @brief Validates the config.
	 * @return true if the config is valid. false otherwise.
	 */
	bool validateConfig();

	/**
	 * @brief Fills the config with the defaults.
	 */
	void fillDefaults();

	/**
	 * @brief Saves the config.
	 * @return true if the config was saved. false otherwise.
	 */
	bool saveConfig();

public:
	/**
	 * @brief ConfigFile constructor.
	 * Sets nothing.
	 */
	ConfigFile() = default;

	/**
	 * @brief ConfigFile constructor.
	 * Sets the path of the config to the provided path.
	 * 
	 * @param filePath - Path of the config.
	 */
	ConfigFile(std::filesystem::path filePath);

	/**
	 * @brief Sets up the config file.
	 * Makes sure it is valid and exists.
	 * @return false if it could not create config file or if the config was invalid. True otherwise.
	 */
	bool setup();

	/**
	 * @brief Adds a default int value to the config file.
	 * 
	 * @param key - Key of the new default value.
	 * @param value - Value of the new default value.
	 * @return true if the value could be added. false otherwise.
	 */
	bool addDefaultInt(std::string key, int value);

	/**
	 * @brief Adds a default bool value to the config file.
	 *
	 * @param key - Key of the new default value.
	 * @param value - Value of the new default value.
	 * @return true if the value could be added. false otherwise.
	 */
	bool addDefaultBool(std::string key, bool value);

	/**
	 * @brief Adds a default string value to the config file.
	 *
	 * @param key - Key of the new default value.
	 * @param value - Value of the new default value.
	 * @return true if the value could be added. false otherwise.
	 */
	bool addDefaultString(std::string key, std::string value);

	/**
	 * @brief Sets an existing int value in the config file.
	 *
	 * @param key - Key of the value to set.
	 * @param value - New value for the key to hold.
	 * @return true if the value could be set. false otherwise.
	 */
	bool setInt(std::string key, int value);

	/**
	 * @brief Sets an existing bool value in the config file.
	 *
	 * @param key - Key of the value to set.
	 * @param value - New value for the key to hold.
	 * @return true if the value could be set. false otherwise.
	 */
	bool setBool(std::string key, bool value);

	/**
	 * @brief Sets an existing string value in the config file.
	 *
	 * @param key - Key of the value to set.
	 * @param value - New value for the key to hold.
	 * @return true if the value could be set. false otherwise.
	 */
	bool setString(std::string key, std::string value);

	/**
	 * @brief Gets the int value at the key.
	 * @return int value at the key. will throw an exception if the value does not exist or isnt the right type.
	 */
	int getInt(std::string key);

	/**
	 * @brief Gets the bool value at the key.
	 * @return bool value at the key. will throw an exception if the value does not exist or isnt the right type.
	 */
	bool getBool(std::string key);

	/**
	 * @brief Gets the string value at the key.
	 * @return string value at the key. will throw an exception if the value does not exist or isnt the right type.
	 */
	std::string getString(std::string key);
};