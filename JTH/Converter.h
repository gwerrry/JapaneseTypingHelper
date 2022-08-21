#pragma once
#include <vector>
#include <qstring.h>


namespace Converter {
	/* Shit. Literal shit, but this is the easy way out so oh well */

	typedef struct keyboardrows {
		bool numberRow = true;
		bool topRow = true;
		bool middleRow = true;
		bool bottomRow = true;
	} KeyboardRows;
	void switchCharacterSet(bool katakana);
	QString parseQtRawKey(int b);
	bool isValidKey(int key, KeyboardRows rows);
	std::vector<QString>* getListOfKeys(KeyboardRows rows);
}