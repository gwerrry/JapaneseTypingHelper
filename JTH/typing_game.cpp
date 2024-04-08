/**
 * @file typing_game.cpp
 * @author gwerry
 * @brief Contains the TypingGame namespace implementations.
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

#include "global.hpp"
#include "typing_game.hpp"
#include "converter.hpp"
#include <qmetaobject.h>
#include <vector>
#include <random>
#include <thread>

#define UPDATE_UI QMetaObject::invokeMethod(obj, "updateGameText");
std::atomic_bool isRunning;
int correct, wrong;
size_t currentCharIndex;
QString currentChar = "さ";
Backend* backend;
QObject* obj;
std::vector<QString>* charList;

void randomizeChar() {
	if (!charList) {
		charList = Converter::getListOfKeys(backend->getRowData().rows);
	}
	if (charList->empty()) {
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
	charList = Converter::getListOfKeys(backend->getRowData().rows);
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