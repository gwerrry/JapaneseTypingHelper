#pragma once
#include "Lang.h"
#include "ConfigUtil.h"

typedef struct row_data {
	bool katakanaOption, firstRowOption, secondRowOption, thirdRowOption, fourthRowOption;
} RowData;

class Backend : public QObject {
	Q_OBJECT
private:
	Language* lang;
	ConfigFile* config;
	RowData gameConfig;
	int musicVolume, sfxVolume, currentLanguage;
	bool setupConfig();
public:
	Backend(QObject* parent = nullptr, QQmlContext* context = nullptr);
	
	RowData getRowData();
	void setObj(QObject* object);
public slots:
	void setKatakana(bool mode);
	bool usingKatakana();
	bool usingFirstRow();
	bool usingSecondRow();
	bool usingThirdRow();
	bool usingFourthRow();
	void stopGame();
	void startGame();
	void resetStats();
	void processKey(int key);
	QString getCorrectText();
	QString getWrongText();
	QString getCurrentChar();
	int getSfxVolume();
	int getCurrentLanguage();
	int getMusicVolume();
	void saveSettingsMenu(int musicVolume, int sfxVolume, int language);
	void saveGameSettings(bool katakanaMode, bool firstRow, bool secondRow, bool thirdRow, bool forthRow);

	void quit();
};