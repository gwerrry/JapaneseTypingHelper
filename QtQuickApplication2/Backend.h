#pragma once
#include <qobject.h>
#include <qcoreapplication.h>
#include "Lang.h"

class Backend : public QObject {
	Q_OBJECT
private:
	bool katakana_mode;
	int master_volume;
	int sfx_volume;
public:
	explicit Backend(QObject* parent = nullptr) : QObject(parent) {}
	bool useKatakana() { return katakana_mode; }
	int getMasterVolume() { return master_volume; }
	int getSfxVolume() { return sfx_volume; }
public slots:

	void quit() {
		QCoreApplication::exit(0);
	}
};