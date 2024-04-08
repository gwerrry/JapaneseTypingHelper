/**
 * @file converter.cpp
 * @author gwerry
 * @brief Contains the Converter namespace implementations.
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
#include "converter.hpp"
#include <qstring.h>
#include <vector>

using namespace std;

QString topNumberRow[14] = { "ろ", "ぬ", "ふ", "あ", "う", "え", "お", "や", "ゆ", "よ", "わ", "を", "ほ", "へ" };
QString topRow[13] = { "た", "て", "い", "す", "か", "ん", "な", "に", "ら", "せ", "゛", "゜", "む" };
QString middleRow[11] = { "ち", "と", "し", "は", "き", "く", "ま", "の", "り", "れ", "け" };
QString bottomRow[10] = { "つ", "さ", "そ", "ひ", "こ", "み", "も", "ね", "る", "め" };

void Converter::switchCharacterSet(bool katakana) {
	if(katakana) {
		//Top number row
		topNumberRow[0] = "ロ";
		topNumberRow[1] = "ヌ";
		topNumberRow[2] = "フ";
		topNumberRow[3] = "ア";
		topNumberRow[4] = "ウ";
		topNumberRow[5] = "エ";
		topNumberRow[6] = "オ";
		topNumberRow[7] = "ヤ";
		topNumberRow[8] = "ユ";
		topNumberRow[9] = "ヨ";
		topNumberRow[10] = "ワ";
		topNumberRow[11] = "ヲ";
		topNumberRow[12] = "ホ";
		topNumberRow[13] = "ヘ";

		//Top row
		topRow[0] = "タ";
		topRow[1] = "テ";
		topRow[2] = "イ";
		topRow[3] = "ス";
		topRow[4] = "カ";
		topRow[5] = "ン";
		topRow[6] = "ナ";
		topRow[7] = "ニ";
		topRow[8] = "ラ";
		topRow[9] = "セ";
		topRow[10] = "゛";
		topRow[11] = "゜";
		topRow[12] = "ム";

		//Middle Row
		middleRow[0] = "チ";
		middleRow[1] = "ト";
		middleRow[2] = "シ";
		middleRow[3] = "ハ";
		middleRow[4] = "キ";
		middleRow[5] = "ク";
		middleRow[6] = "マ";
		middleRow[7] = "ノ";
		middleRow[8] = "リ";
		middleRow[9] = "レ";
		middleRow[10] = "ケ";

		//Bottom Row
		bottomRow[0] = "ツ";
		bottomRow[1] = "サ";
		bottomRow[2] = "ソ";
		bottomRow[3] = "ヒ";
		bottomRow[4] = "コ";
		bottomRow[5] = "ミ";
		bottomRow[6] = "モ";
		bottomRow[7] = "ネ";
		bottomRow[8] = "ル";
		bottomRow[9] = "メ";
	} else {
		//Top number row
		topNumberRow[0] = "ろ";
		topNumberRow[1] = "ぬ";
		topNumberRow[2] = "ふ";
		topNumberRow[3] = "あ";
		topNumberRow[4] = "う";
		topNumberRow[5] = "え";
		topNumberRow[6] = "お";
		topNumberRow[7] = "や";
		topNumberRow[8] = "ゆ";
		topNumberRow[9] = "よ";
		topNumberRow[10] = "わ";
		topNumberRow[11] = "を";
		topNumberRow[12] = "ほ";
		topNumberRow[13] = "へ";

		//Top Row
		topRow[0] = "た";
		topRow[1] = "て";
		topRow[2] = "い";
		topRow[3] = "す";
		topRow[4] = "か";
		topRow[5] = "ん";
		topRow[6] = "な";
		topRow[7] = "に";
		topRow[8] = "ら";
		topRow[9] = "せ";
		topRow[10] = "゛";
		topRow[11] = "゜";
		topRow[12] = "む";

		//Middle Row
		middleRow[0] = "ち";
		middleRow[1] = "と";
		middleRow[2] = "し";
		middleRow[3] = "は";
		middleRow[4] = "き";
		middleRow[5] = "く";
		middleRow[6] = "ま";
		middleRow[7] = "の";
		middleRow[8] = "り";
		middleRow[9] = "れ";
		middleRow[10] = "け";

		//Bottom Row
		bottomRow[0] = "つ";
		bottomRow[1] = "さ";
		bottomRow[2] = "そ";
		bottomRow[3] = "ひ";
		bottomRow[4] = "こ";
		bottomRow[5] = "み";
		bottomRow[6] = "も";
		bottomRow[7] = "ね";
		bottomRow[8] = "る";
		bottomRow[9] = "め";
	}
}

QString Converter::parseQtRawKey(int b) {
	switch(b) {
		//top number row
		case 96: return topNumberRow[0]; break;
		case 49: return topNumberRow[1]; break;
		case 50: return topNumberRow[2]; break;
		case 51: return topNumberRow[3]; break;
		case 52: return topNumberRow[4]; break;
		case 53: return topNumberRow[5]; break;
		case 54: return topNumberRow[6]; break;
		case 55: return topNumberRow[7]; break;
		case 56: return topNumberRow[8]; break;
		case 57: return topNumberRow[9]; break;
		case 48: return topNumberRow[10]; break;
		case 41: return topNumberRow[11]; break;
		case 45: return topNumberRow[12]; break;
		case 61: return topNumberRow[13]; break;

		//top qwerty row
		case 81: return topRow[0]; break;
		case 87: return topRow[1]; break;
		case 69: return topRow[2]; break;
		case 82: return topRow[3]; break;
		case 84: return topRow[4]; break;
		case 89: return topRow[5]; break;
		case 85: return topRow[6]; break;
		case 73: return topRow[7]; break;
		case 79: return topRow[8]; break;
		case 80: return topRow[9]; break;
		case 91: return topRow[10]; break;
		case 93: return topRow[11]; break;
		case 92: return topRow[12]; break;

		//home row
		case 65: return middleRow[0]; break;
		case 83: return middleRow[1]; break;
		case 68: return middleRow[2]; break;
		case 70: return middleRow[3]; break;
		case 71: return middleRow[4]; break;
		case 72: return middleRow[5]; break;
		case 74: return middleRow[6]; break;
		case 75: return middleRow[7]; break;
		case 76: return middleRow[8]; break;
		case 59: return middleRow[9]; break;
		case 39: return middleRow[10]; break;

		//bottom row
		case 90: return bottomRow[0]; break;
		case 88: return bottomRow[1]; break;
		case 67: return bottomRow[2]; break;
		case 86: return bottomRow[3]; break;
		case 66: return bottomRow[4]; break;
		case 78: return bottomRow[5]; break;
		case 77: return bottomRow[6]; break;
		case 44: return bottomRow[7]; break;
		case 46: return bottomRow[8]; break;
		case 47: return bottomRow[9]; break;
		default: return "none";
	}
}

bool Converter::isValidKey(int key, KeyboardRows rows) {
	if(rows.numberRow) {
		switch(key) {
			//top number row
			case 96:
			case 49:
			case 50:
			case 51:
			case 52:
			case 53:
			case 54:
			case 55:
			case 56:
			case 57:
			case 48:
			case 41:
			case 45:
			case 61: return true; break;
			default: break;
		}
	}
	if(rows.topRow) {
		switch(key) {
			//top qwerty row

			case 81:
			case 87:
			case 69:
			case 82:
			case 84:
			case 89:
			case 85:
			case 73:
			case 79:
			case 80:
			case 91:
			case 93:
			case 92: return true; break;
			default: break;
		}
	}
	if(rows.middleRow) {
		switch(key) {
			//home row
			case 65:
			case 83:
			case 68:
			case 70:
			case 71:
			case 72:
			case 74:
			case 75:
			case 76:
			case 59:
			case 39: return true; break;
			default: break;
		}
	}
	if(rows.bottomRow) {
		switch(key) {
			//bottom row
			case 90:
			case 88:
			case 67:
			case 86:
			case 66:
			case 78:
			case 77:
			case 44:
			case 46:
			case 47: return true; break;
			default: break;
		}
	}
	return false;
}

vector<QString>* Converter::getListOfKeys(KeyboardRows rows) {
	vector<QString>* vec = new vector<QString>();
	vec->reserve(46); // max possible size

	if (rows.numberRow) {
		for (int i = 0; i < 14; i++) {
			vec->push_back(topNumberRow[i]);
		}
	}
	if (rows.topRow) {
		for (int i = 0; i < 12; i++) {
			vec->push_back(topRow[i]);
		}
	}
	if (rows.middleRow) {
		for (int i = 0; i < 10; i++) {
			vec->push_back(middleRow[i]);
		}
	}
	if (rows.bottomRow) {
		for (int i = 0; i < 10; i++) {
			vec->push_back(bottomRow[i]);
		}
	}

	vec->shrink_to_fit();
	return vec;
}
