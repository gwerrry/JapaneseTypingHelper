#pragma once
#include <qobject.h>
#include <qstring.h>
#include <qqmlcontext.h>

#define ENGLISH_LANG 0
#define JAPANESE_LANG 1

class Language : public QObject {
	Q_OBJECT
private:
	QQmlContext* app;
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
	
	int current_lang;
	
	void setEnglish();
	void setJapanese();

public:
	
	Language(QObject* parent = nullptr);
	void setContext(QQmlContext* c);
	void getCurrentLang();
public slots:
	void setLanguage(int language);
};