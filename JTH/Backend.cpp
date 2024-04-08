/**
 * @file backend.cpp
 * @author gwerry
 * @brief Contains the Backend class implementations.
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

#include "backend.hpp"
#include "converter.hpp"
#include "global.hpp"
#include "logger.h"
#include "typing_game.hpp"
#include <qcoreapplication.h>

Backend::Backend(QObject* parent, QQmlContext* context) : QObject(parent) {
	lang = new Language();
	lang->setContext(context);
	gameConfig = { false, {false, false, false, false} };
	if (!setupConfig()) {
		LOG(LOG_FATAL, "Failed to set up Config!");
		exit(-1);
	}

	musicVolume = config->getInt(CONFIG_MUSIC_VOLUME);
	sfxVolume = config->getInt(CONFIG_SFX_VOLUME);
	currentLanguage = config->getInt(CONFIG_LANGUAGE);

	this->gameConfig.katakanaOption = config->getBool(CONFIG_KATAKANA_MODE);
	gameConfig.rows = { config->getBool(CONFIG_FIRST_ROW), config->getBool(CONFIG_SECOND_ROW), config->getBool(CONFIG_THRID_ROW), config->getBool(CONFIG_FOURTH_ROW) };
	Converter::switchCharacterSet(gameConfig.katakanaOption);
	lang->setLanguage(currentLanguage);
}

bool Backend::setupConfig() {
	std::string config_path = getCurrentDir();
	config_path += "/";
	config_path += DATA_DIRECTORY;
	config_path += "/config.json";

	config = new ConfigFile(config_path);
	config->addDefaultBool(CONFIG_KATAKANA_MODE, CONFIG_KATAKANA_DEFAULT);
	config->addDefaultBool(CONFIG_FIRST_ROW, CONFIG_FIRST_ROW_DEFAULT);
	config->addDefaultBool(CONFIG_SECOND_ROW, CONFIG_SECOND_ROW_DEFAULT);
	config->addDefaultBool(CONFIG_THRID_ROW, CONFIG_THRID_ROW_DEFAULT);
	config->addDefaultBool(CONFIG_FOURTH_ROW, CONFIG_FOURTH_ROW_DEFAULT);
	config->addDefaultInt(CONFIG_LANGUAGE, CONFIG_LANGUAGE_DEFAULT);
	config->addDefaultInt(CONFIG_MUSIC_VOLUME, CONFIG_MUSIC_VOLUME_DEFAULT);
	config->addDefaultInt(CONFIG_SFX_VOLUME, CONFIG_SFX_VOLUME_DEFAULT);

	return config->setup();
}

void Backend::setKatakana(bool katakanaOption) {
	config->setBool(CONFIG_KATAKANA_MODE, katakanaOption);
	this->gameConfig.katakanaOption = katakanaOption;
	Converter::switchCharacterSet(katakanaOption);
}

void Backend::saveSettingsMenu(int musicVolume, int sfxVolume, int language) {
	config->setInt(CONFIG_MUSIC_VOLUME, musicVolume);
	config->setInt(CONFIG_SFX_VOLUME, sfxVolume);
	config->setInt(CONFIG_LANGUAGE, language);
	lang->setLanguage(language);
	this->musicVolume = musicVolume;
	this->sfxVolume = sfxVolume;
	this->currentLanguage = language;
	/*
	
	
	
	
	
	
	
	
	
	
	
	
	*/
	//update music and other volume stuff here if want to add that.
}

void Backend::processKey(int key) {
	TypingGame::processKey(key);
}

void Backend::stopGame() {
	TypingGame::stopGame();
}

void Backend::startGame() {
	TypingGame::startGame();
}

void Backend::resetStats() {
	TypingGame::resetStats();
}

void Backend::saveGameSettings(bool katakanaMode, bool numberRow, bool topRow, bool middleRow, bool bottomRow) {
	TypingGame::stopGame();

	setKatakana(katakanaMode);
	config->setBool(CONFIG_FIRST_ROW, numberRow);
	config->setBool(CONFIG_SECOND_ROW, topRow);
	config->setBool(CONFIG_THRID_ROW, middleRow);
	config->setBool(CONFIG_FOURTH_ROW, bottomRow);

	gameConfig.rows = { numberRow , topRow, middleRow, bottomRow };
	TypingGame::startGame();
}

bool Backend::usingKatakana() { return gameConfig.katakanaOption; }
bool Backend::usingFirstRow() { return gameConfig.rows.numberRow; }
bool Backend::usingSecondRow() { return gameConfig.rows.topRow; }
bool Backend::usingThirdRow() { return gameConfig.rows.middleRow; }
bool Backend::usingFourthRow() { return gameConfig.rows.bottomRow; }
void Backend::setObj(QObject* object) {
	TypingGame::setObj(object);
	TypingGame::setBackend(this);
}
int Backend::getMusicVolume() { return musicVolume; }
int Backend::getSfxVolume() { return sfxVolume; }
int Backend::getCurrentLanguage() { return currentLanguage; }
QString Backend::getCorrectText() { return QString::number(TypingGame::getCorrect()); }
QString Backend::getWrongText() { return QString::number(TypingGame::getWrong()); }
QString Backend::getCurrentChar() { return TypingGame::getCurrentChar(); }
RowData Backend::getRowData() { return gameConfig; }

void Backend::quit() {
	QCoreApplication::exit(0);
}