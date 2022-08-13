#pragma once
#include <vector>
#include <qstring.h>

typedef struct keyboardrows {
	bool numberRow = true;
	bool topRow = true;
	bool middleRow = true;
	bool bottomRow = true;
} KeyboardRows;

namespace Converter {
	void switchCharacterSet(bool katakana);
	QString parseQtRawKey(int b);
	bool isValidKey(int key, KeyboardRows rows);
	std::vector<QString>* getListOfKeys(KeyboardRows rows);
}