#pragma once
#include "Backend.h"
#include <qobject.h>
#include <qstring.h>
#include <thread>

namespace TypingGame {

	void startGame();

	void stopGame();

	void resetStats();

	int getCorrect();

	int getWrong();

	void processKey(int key);

	QString getCurrentChar();

	void setObj(QObject* obj);
	
	void setBackend(Backend* backend);
}
