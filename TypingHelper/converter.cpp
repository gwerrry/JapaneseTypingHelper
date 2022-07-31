#include "global.h"
#include "backend.h"

/*
Fuck this file.
I really fucking hate this stupid peice of shit,
but it works so oh well...
*/

/* Convert QT's amazing peice of shit to a wchar */

QString topNumberRow[14] = {"ろ", "ぬ", "ふ", "あ", "う", "え", "お", "や", "ゆ", "よ", "わ", "を", "ほ", "へ"};
QString topRow[13] = {"た", "て", "い", "す", "か", "ん", "な", "に", "ら", "せ", "゛", "゜", "む"};
QString middleRow[13] = {"た", "て", "い", "す", "か", "ん", "な", "に", "ら", "せ", "゛", "゜", "む"};
QString bottomRow[13] = {"た", "て", "い", "す", "か", "ん", "な", "に", "ら", "せ", "゛", "゜", "む"};

QString parseQtRawKey(int b) {
	switch(b) {
		//top number row
		case 96: return "ろ"; break;
		case 49: return "ぬ"; break;
		case 50: return "ふ"; break;
		case 51: return "あ"; break;
		case 52: return "う"; break;
		case 53: return "え"; break;
		case 54: return "お"; break;
		case 55: return "や"; break;
		case 56: return "ゆ"; break;
		case 57: return "よ"; break;
		case 48: return "わ"; break;
		case 41: return "を"; break;
		case 45: return "ほ"; break;
		case 61: return "へ"; break;


			//top qwerty row

		case 81: return "た"; break;
		case 87: return "て"; break;
		case 69: return "い"; break;
		case 82: return "す"; break;
		case 84: return "か"; break;
		case 89: return "ん"; break;
		case 85: return "な"; break;
		case 73: return "に"; break;
		case 79: return "ら"; break;
		case 80: return "せ"; break;
		case 91: return "゛"; break;
		case 93: return "゜"; break;
		case 92: return "む"; break;

			//home row
		case 65: return "ち"; break;
		case 83: return "と"; break;
		case 68: return "し"; break;
		case 70: return "は"; break;
		case 71: return "き"; break;
		case 72: return "く"; break;
		case 74: return "ま"; break;
		case 75: return "の"; break;
		case 76: return "り"; break;
		case 59: return "れ"; break;
		case 39: return "け"; break;

			//bottom row
		case 90: return "つ"; break;
		case 88: return "さ"; break;
		case 67: return "そ"; break;
		case 86: return "ひ"; break;
		case 66: return "こ"; break;
		case 78: return "み"; break;
		case 77: return "も"; break;
		case 44: return "ね"; break;
		case 46: return "る"; break;
		case 47: return "め"; break;
		default: "none";
	}
}

bool isValidKey(int key, KeyboardRows rows) {
	if(rows.numberRow) {
		switch(key) {
			//top number row
			case 96: return true; break;
			case 49: return true; break;
			case 50: return true; break;
			case 51: return true; break;
			case 52: return true; break;
			case 53: return true; break;
			case 54: return true; break;
			case 55: return true; break;
			case 56: return true; break;
			case 57: return true; break;
			case 48: return true; break;
			case 41: return true; break;
			case 45: return true; break;
			case 61: return true; break;
			default: break;
		}
	}
	if(rows.topRow) {
		switch(key) {
			//top qwerty row

			case 81: return true; break;
			case 87: return true; break;
			case 69: return true; break;
			case 82: return true; break;
			case 84: return true; break;
			case 89: return true; break;
			case 85: return true; break;
			case 73: return true; break;
			case 79: return true; break;
			case 80: return true; break;
			case 91: return true; break;
			case 93: return true; break;
			case 92: return true; break;
			default: break;
		}
	}
	if(rows.middleRow) {
		switch(key) {
			//home row
			case 65: return true; break;
			case 83: return true; break;
			case 68: return true; break;
			case 70: return true; break;
			case 71: return true; break;
			case 72: return true; break;
			case 74: return true; break;
			case 75: return true; break;
			case 76: return true; break;
			case 59: return true; break;
			case 39: return true; break;
			default: break;
		}
	}
	if(rows.bottomRow) {
		switch(key) {
			//bottom row
			case 90: return true; break;
			case 88: return true; break;
			case 67: return true; break;
			case 86: return true; break;
			case 66: return true; break;
			case 78: return true; break;
			case 77: return true; break;
			case 44: return true; break;
			case 46: return true; break;
			case 47: return true; break;
			default: break;
		}
	}
	return false;
}
