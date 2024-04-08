/**
 * @file converter.hpp
 * @author gwerry
 * @brief Contains the Converter namespace.
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
#include <vector>
#include <qstring.h>

/**
 * @brief Converter namespace.
 * Holds functions relavent to the converter.
 * The converter functions can switch the current character set,
 * parse raw key codes into their corresponding character, check if a key is valid,
 * and build a list of keys to pick from.
 */
namespace Converter {
	/**
	 * @brief KeyboardRows struct.
	 * Holds information about the enabled/disabled rows.
	 */
	typedef struct keyboardrows {
		bool numberRow = true;
		bool topRow = true;
		bool middleRow = true;
		bool bottomRow = true;
	} KeyboardRows;

	/**
     * @brief Switches the character set between katakana and hiragana.
	 * @param katakana - Sets the character set to katakana if true. Hiragana if false.
	 */
	void switchCharacterSet(bool katakana);

	/**
	 * @brief Parses the QT raw key code to the corresponding kana.
	 * @param b - Keycode to parse.
	 * @return QString of the current key.
	 * Can return "none" if it is not a relevant key (not a key with a kana on it).
	 */
	QString parseQtRawKey(int b);

	/**
	 * @brief Checks if the pressed key is a valid key in the selected rows.
	 * @param key - Key to check.
	 * @param rows - Rows to check. In the struct, true means the row will be checked. False means it wont.
	 * @return true if the key is in one of the selected rows. False otherwise.
	 */
	bool isValidKey(int key, KeyboardRows rows);

	/**
	 * @brief Builds a list of keys from the selected rows.
	 * A row is "selected" if it is set to true.
	 * 
	 * @param rows - Rows to build list of keys from.
	 * @return pointer to std::vector of QString. Must be deleted when you are done with it.
	 */
	std::vector<QString>* getListOfKeys(KeyboardRows rows);
}