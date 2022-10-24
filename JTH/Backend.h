#pragma once
#include "Lang.h"
#include "ConfigUtil.h"

class Backend : public QObject {
	Q_OBJECT
private:
	Language* lang;
	ConfigFile* config;
	bool katakanaOption, firstRowOption, secondRowOption, thirdRowOption, fourthRowOption;
	int musicVolume, sfxVolume, currentLanguage;
	bool setupConfig();
public:
	Backend(QObject* parent = nullptr, QQmlContext* context = nullptr);
	bool usingKatakana();
public slots:
	void setKatakana(bool mode);
	int getSfxVolume();
	int getCurrentLanguage();
	int getMusicVolume();
	void saveSettingsMenu(int musicVolume, int sfxVolume, int language);
	void saveGameSettings(bool katakanaMode, bool firstRow, bool secondRow, bool thirdRow, bool forthRow);

	void quit();
};