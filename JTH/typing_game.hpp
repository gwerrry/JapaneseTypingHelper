/**
 * @file typing_game.hpp
 * @author gwerry
 * @brief Contains the TypingGame namespace.
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
#include "backend.hpp"
#include <qobject.h>
#include <qstring.h>

/**
 * @brief TypingGame namespace.
 * Holds functions relavent to manipulating the game.
 */
namespace TypingGame {
	/**
	 * @brief Starts the game.
	 */
	void startGame();

	/**
	 * @brief Stops the game.
	 */
	void stopGame();

	/**
	 * @brief Resets the wrong/right counters.
	 */
	void resetStats();

	/**
	 * @brief Gets the amount of correct answers.
	 */
	int getCorrect();

	/**
	 * @brief Gets the amount of wrong answers.
	 */
	int getWrong(); // todo what is this name? do comments better.

	/**
	 * @brief Processes key to see if it was a right or wrong answer.
	 * @param key - Key to process.
	 */
	void processKey(int key);

	/**
	 * @brief Gets the current displayed character to type.
	 * @return QString of the current character to type.
	 */
	QString getCurrentChar();

	/**
	 * @brief Sets the QObject object to use for the game.
	 * @param obj - Pointer to QObject object to use for the game.
	 */
	void setObj(QObject* obj);
	
	/**
	 * @brief Sets the Background object to use for the game.
	 * @param obj - Pointer to Background object to use for the game.
	 */
	void setBackend(Backend* backend);
}
