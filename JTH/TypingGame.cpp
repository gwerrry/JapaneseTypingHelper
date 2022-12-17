#include "global.h"
#include "TypingGame.h"
#include <qmetaobject.h>
#include <vector>
#include <random>
#include "Converter.h"

#define UPDATE_UI QMetaObject::invokeMethod(obj, "updateGameText");
std::atomic_bool isRunning;
int correct;
int wrong;
size_t currentCharIndex;
QString currentChar = "さ";
Backend* backend;
QObject* obj;

std::vector<QString>* charList;

Converter::keyboardrows gd2rd(RowData rd) {
	return { rd.firstRowOption, rd.secondRowOption, rd.thirdRowOption, rd.fourthRowOption };
}
void randomizeChar() {
	if (!charList) {
		charList = Converter::getListOfKeys(gd2rd(backend->getRowData()));
	}
	if (charList->size() <= 0) {
		currentCharIndex = 0;
		currentChar = QString("あ");
		return;
	}
	std::random_device r;
	std::mt19937 gen(r());
	std::uniform_int_distribution<> distr(0, charList->size() - 1);

	uint8_t random_number = distr(gen);

	if (random_number == currentCharIndex) {
		if (random_number == 0) random_number++;
		else random_number--;		
	}

	currentCharIndex = random_number;
	currentChar = charList->at(random_number);
}

void TypingGame::processKey(int key) {
	if (isRunning) {
		QString keyPressed = Converter::parseQtRawKey(key);
		if (keyPressed == currentChar) {
			correct++;
			//might add sound effect here
		} else {
			wrong += 1;
			//might add sound effect here
		}
		randomizeChar();
		UPDATE_UI
	}
}

void TypingGame::startGame() {
	if (charList) delete charList;
	charList = Converter::getListOfKeys(gd2rd(backend->getRowData()));
	randomizeChar();
	isRunning = true;
	UPDATE_UI
}

void TypingGame::stopGame() {
	isRunning = false;
}



void TypingGame::resetStats() {
	isRunning = false;
	wrong = 0;
	correct = 0;

	randomizeChar();

	UPDATE_UI
	isRunning = true;
}

int TypingGame::getCorrect() {
	return correct;
}

int TypingGame::getWrong() {
	return wrong;
}

QString TypingGame::getCurrentChar() {
	return currentChar;
}


void TypingGame::setBackend(Backend* backendd) {
	backend = backendd;
	isRunning = false;
}
void TypingGame::setObj(QObject* backendd) {
	obj = backendd;
}

#undef UPDATEUI