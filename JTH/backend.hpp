/**
 * @file backend.hpp
 * @author gwerry
 * @brief Contains the Backend class.
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
#include "lang.hpp"
#include "config_util.hpp"
#include "converter.hpp"

/**
 * @brief RowData struct.
 * Holds the katakana option and info about the selected rows.
 */
typedef struct row_data {
	bool katakanaOption;
	Converter::KeyboardRows rows;
} RowData;

/**
 * @brief Backend class.
 * Holds all functions for the backend and is used mainly to foward all functions to QML so
 * everything is in one place.
 */
class Backend : public QObject {
	Q_OBJECT
private:
	Language* lang;
	ConfigFile* config;
	RowData gameConfig;
	int musicVolume, sfxVolume, currentLanguage;
	/**
	 * @brief Sets up the config.
	 * @return false if the config failed to set up. true otherwise.
	 */
	bool setupConfig();

public:
	/**
	 * @brief Backend constructor.
	 * @param parent - QObject parent of backend. Default nullptr.
	 * @param context - QQmlContext of the backend. Default nullptr.
	 */
	Backend(QObject* parent = nullptr, QQmlContext* context = nullptr);

	/**
	 * @brief Gets the game config data.
	 * 
	 * @return RowData game config.
	 */
	RowData getRowData();

	/**
	 * @brief Sets the QObject for the backend.
	 * @param object - Pointer to the QObject for the backend.
	 */
	void setObj(QObject* object);

public slots:

	/**
	 * @brief Gets if the game is using katakana.
     * @return True if game is using katakana. False otherwise.
	 */
	bool usingKatakana();

	/**
	 * @brief Gets if the game is using the first row.
	 * First row meaning the `1234567890-= row.
	 * 
	 * @return True if game is using first row. False otherwise.
	 */
	bool usingFirstRow();

	/**
	 * @brief Gets if the game is using the second row.
	 * Second row meaning the qwertyuiop[]\ row.
	 *
	 * @return True if game is using second row. False otherwise.
	 */
	bool usingSecondRow();

	/**
	 * @brief Gets if the game is using the third row.
	 * Third row meaning the asdfghjkl;' row.
	 *
	 * @return True if game is using third row. False otherwise.
	 */
	bool usingThirdRow();

	/**
	 * @brief Gets if the game is using the fourth row.
	 * Fourth row meaning the zxcvbnm,./ row.
	 *
	 * @return True if game is using fourth row. False otherwise.
	 */
	bool usingFourthRow();

	/**
	 * @brief Gets the amount of correct guesses as a QString.
	 * 
	 * @return QString of the amount of correct guesses.
	 */
	QString getCorrectText();

	/**
	 * @brief Gets the amount of incorrect guesses as a QString.
	 * 
	 * @return QString of the amount of incorrect guesses.
	 */
	QString getWrongText();

	/**
	 * @brief Gets the current charcter to type.
	 * 
	 * @return QString of the current character to type.
	 */
	QString getCurrentChar();

	/**
	 * @brief Gets the sound effects volume.
	 * 
	 * @return int of the current sound effect volume.
	 */
	int getSfxVolume();

	/**
	 * @brief Gets the current language.
	 * 
	 * @return int of the current language.
	 */
	int getCurrentLanguage();

	/**
	 * @brief Gets the current music volume.
	 * 
	 * @return int of the current music volume.
	 */
	int getMusicVolume();

	/**
	 * @brief Sets the katakana mode for the game. Also updates the config.
	 * 
	 * @param mode - True if katakana should be used, false if hiragana should be used.
	 */
	void setKatakana(bool mode);

	/**
	 * @brief Stops the game.
	 */
	void stopGame();

	/**
	 * @brief Starts the game.
	 */
	void startGame();

	/**
	 * @brief Resets the stats for the game.
	 */
	void resetStats();

	/**
	 * @brief Processes a pressed key from QML.
	 * 
	 * @param key - Key to process.
	 */
	void processKey(int key);

	/**
	 * @brief Saves the settings found in the settings menu.
	 * 
	 * @param musicVolume - Music volume to save.
	 * @param sfxVolume - SFX volume to save.
	 * @param language - Language to save.
	 */
	void saveSettingsMenu(int musicVolume, int sfxVolume, int language);

	/**
	 * @brief Saves the game settings.
	 * 
	 * @param katakanaMode - True if use katakana. False if use hiragana.
	 * @param numberRow - Set if the number row should be included in the random characters.
	 * @param topRow - Set if the top row should be included in the random characters.
	 * @param middleRow - Set if the middle row should be included in the random characters.
	 * @param numberRow - Set if the bottom row should be included in the random characters.
	 */
	void saveGameSettings(bool katakanaMode, bool numberRow, bool topRow, bool middleRow, bool bottomRow);

	/**
	 * @brief Exists the app.
	 */
	void quit();
};