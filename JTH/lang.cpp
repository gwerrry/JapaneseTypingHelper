﻿/**
 * @file lang.cpp
 * @author gwerry
 * @brief Contains the Language class implementations.
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

#include "lang.hpp"

void Language::setEnglish() {
	/* Global Variables  */
	app->setContextProperty(backToMainMenuText, "MAIN MENU");

	/* Main Menu Text */
	app->setContextProperty(mainMenuSplashText, "日本語タイピング");
	app->setContextProperty(mainMenuPlayText, "Play");
	app->setContextProperty(mainMenuOptionsText, "Options");
	app->setContextProperty(mainMenuExitText, "Exit");

	/* Settings Menu Text */
	app->setContextProperty(settingsMenuSplashText, "Settings");
	app->setContextProperty(settingsMenuMusicVolumeText, "Music Volume:");
	app->setContextProperty(settingsMenuSfxVolumeText, "SFX Volume:");
	app->setContextProperty(settingsMenuLanguageText, "Language:");
	app->setContextProperty(settingsMenuSaveText, "SAVE");

	/* Game Menu Text */
	app->setContextProperty(gameMenuKatakanaSwitcherText, "カタカナ Mode");
	app->setContextProperty(gameMenuOptionsText, "Options");
	app->setContextProperty(gameMenuNumberRowText, "ろ　ぬ　ふ. . .");
	app->setContextProperty(gameMenuTopRowText, "た　て　い. . .");
	app->setContextProperty(gameMenuMiddleRowText, "ち　と　し. . .");
	app->setContextProperty(gameMenuBottomRowText, "つ　さ　そ. . .");
	app->setContextProperty(gameMenuEnabledRowsText, "Enabled Rows");
	app->setContextProperty(gameMenuCorrectText, "CORRECT");
	app->setContextProperty(gameMenuWrongText, "WRONG");
	app->setContextProperty(gameMenuResetText, "RESET");
	app->setContextProperty(gameMenuSplashText, "Please Press...");
}

void Language::setJapanese() {
	/* Global Variables  */
	app->setContextProperty(backToMainMenuText, "前のメニュー");

	/* Main Menu Text */
	app->setContextProperty(mainMenuSplashText, "日本語タイピング");
	app->setContextProperty(mainMenuPlayText, "スタート");
	app->setContextProperty(mainMenuOptionsText, "設定");
	app->setContextProperty(mainMenuExitText, "出口");

	/* Settings Menu Text */
	app->setContextProperty(settingsMenuSplashText, "設定");
	app->setContextProperty(settingsMenuMusicVolumeText, "音楽の音量:");
	app->setContextProperty(settingsMenuSfxVolumeText, "効果音の音量:");
	app->setContextProperty(settingsMenuLanguageText, "言語:");
	app->setContextProperty(settingsMenuSaveText, "設定を保存します");

	/* Game Menu Text */
	app->setContextProperty(gameMenuKatakanaSwitcherText, "カタカナ表示");
	app->setContextProperty(gameMenuOptionsText, "オプション");
	app->setContextProperty(gameMenuNumberRowText, "ろ　ぬ　ふ. . .");
	app->setContextProperty(gameMenuTopRowText, "た　て　い. . .");
	app->setContextProperty(gameMenuMiddleRowText, "ち　と　し. . .");
	app->setContextProperty(gameMenuBottomRowText, "つ　さ　そ. . .");
	app->setContextProperty(gameMenuEnabledRowsText, "キーボード行");
	app->setContextProperty(gameMenuCorrectText, "正解");
	app->setContextProperty(gameMenuWrongText, "正しくない");
	app->setContextProperty(gameMenuResetText, "リセット");
	app->setContextProperty(gameMenuSplashText, "キーを押してください...");
}

Language::Language(){ app = nullptr; current_lang = ENGLISH_LANG; }

void Language::setContext(QQmlContext* c) {
	app = c;
}

int Language::getCurrentLang() {
	return current_lang;
}

void Language::setLanguage(int language) {
	switch(language) {
		case ENGLISH_LANG:
			setEnglish();
			break;
		case JAPANESE_LANG:

			setJapanese();
			break;
		default:
			setEnglish();
			language = ENGLISH_LANG;
	}
	current_lang = language;
}