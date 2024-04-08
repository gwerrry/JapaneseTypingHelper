/**
 * @file lang.hpp
 * @author gwerry
 * @brief Contains the Language class.
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
#include <qobject.h>
#include <qstring.h>
#include <qqmlcontext.h>

// Languages
#define ENGLISH_LANG 0
#define JAPANESE_LANG 1

/**
 * @brief Language class.
 * Holds all of the text for the game.
 * Also manages the currently language being displayed.
 */
class Language {
private:
	QQmlContext* app;
	int current_lang;

	const char* backToMainMenuText = "backToMainMenuText";

	const char* mainMenuSplashText = "mainMenuSplashText";
	const char* mainMenuPlayText = "mainMenuPlayText";
	const char* mainMenuOptionsText = "mainMenuOptionsText";
	const char* mainMenuExitText = "mainMenuExitText";

	const char* settingsMenuSplashText = "settingsMenuSplashText";
	const char* settingsMenuMusicVolumeText = "settingsMenuMusicVolumeText";
	const char* settingsMenuSfxVolumeText = "settingsMenuSfxVolumeText";
	const char* settingsMenuLanguageText = "settingsMenuLanguageText";
	const char* settingsMenuSaveText = "settingsMenuSaveText";

	const char* gameMenuKatakanaSwitcherText = "gameMenuKatakanaSwitcherText";
	const char* gameMenuOptionsText = "gameMenuOptionsText";
	const char* gameMenuNumberRowText = "gameMenuNumberRowText";
	const char* gameMenuTopRowText = "gameMenuTopRowText";
	const char* gameMenuMiddleRowText = "gameMenuMiddleRowText";
	const char* gameMenuBottomRowText = "gameMenuBottomRowText";
	const char* gameMenuEnabledRowsText = "gameMenuEnabledRowsText";
	const char* gameMenuCorrectText = "gameMenuCorrectText";
	const char* gameMenuWrongText = "gameMenuWrongText";
	const char* gameMenuResetText = "gameMenuResetText";
	const char* gameMenuSplashText = "gameMenuSplashText";
	
	/**
	 * @brief Sets the current language to English.
	 */
	void setEnglish();

	/**
	 * @brief Sets the current language to Japanese.
	 */
	void setJapanese();

public:
	/**
	 * @brief Language constructor.
	 * Sets default language to english and app to nullptr.
	 */
	Language();

	/**
	 * @brief Sets QML context for the language to change in.
	 * @param c - Pointer to QML context for the language to change in.
	 */
	void setContext(QQmlContext* c);
	
	/**
	 * @brief Sets the language of the app in relation to the current QML context.
	 * @param lanugage - Language to set the app to. The defines for the languages can be found at the top of this file.
	 */
	void setLanguage(int language);

	/**
	 * @brief Returns an integer representing the current language.
	 * @return int of the current language. The defines for the languages can be found at the top of this file.
	 */
	int getCurrentLang();
};