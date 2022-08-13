#include "global.h"
#include <qstring.h>
#include <qobject.h>
#include <qcolor.h>
#include "logger.h"

typedef struct keyboardrows {
	bool numberRow = true;
	bool topRow = true;
	bool middleRow = true;
	bool bottomRow = true;
} KeyboardRows;

void die(int status, bool print_err, bool show_dialog, ccptr message);
QString parseQtRawKey(int b);
void switchCharacterSet(bool katakana);
bool isValidKey(int key, KeyboardRows rows);

class LoggerWrapper : public QObject {
	Q_OBJECT
public:
	explicit LoggerWrapper(QObject* parent = nullptr);
public slots:
	void info(const QString str);
	void debug(const QString str);
	void warn(const QString str);
	void error(const QString str);
	void fatal(const QString str);
};

class Constants : public QObject {
	Q_OBJECT
public:
	explicit Constants(QObject* parent = nullptr) {}
	const int width = 800;
	const int height = 600;

	const QColor backgroundColor = QColor("#E3E3E3");
	const QColor lightBackgroundColor = QColor("#7A7A7A");

	/* Button Style stuff */
	const QColor buttonBackgroundColor = QColor("#FFFFFF");
	const QColor buttonHoverColor = QColor("#D3D3D3");
	const QColor buttonPopHoverColor = QColor("#FF5E5E");
	const QColor buttonClickColor = QColor("#bbbbbb");
	const int buttonRadius = 7;

	/* Global Text */
	QString backToMainMenuText = "";

	/* Main Menu Text */
	QString mainMenuSplashText = "";
	QString mainMenuPlayText = "";
	QString mainMenuOptionsText = "";
	QString mainMenuExitText = "";

	/* Settings Menu Text */
	QString settingsMenuSplashText = "";
	QString settingsMenuMusicVolumeText = "";
	QString settingsMenuSfxVolumeText = "";
	QString settingsMenuLanguageText = "";
	QString settingsMenuSaveText = "";

	/* Game Menu Text */
	QString gameMenuKatakanaSwitcherText = "";
	QString gameMenuOptionsText = "";
	QString gameMenuNumberRowText = "";
	QString gameMenuTopRowText = "";
	QString gameMenuMiddleRowText = "";
	QString gameMenuBottomRowText = "";
	QString gameMenuEnabledRowsText = "";
	QString gameMenuCorrectText = "";
	QString gameMenuWrongText = "";
	QString gameMenuResetText = "";
	QString gameMenuSplashText = "";
};

class Backend : public QObject {
	Q_OBJECT
private:
	Constants* constants;
	void setEnglish();
	void setJapanese();

public:
	explicit Backend(QObject* parent = nullptr);
	void linkConstants(Constants* constants) {
		this->constants = constants;
	}
public slots:
	void setLang(int lang);
};