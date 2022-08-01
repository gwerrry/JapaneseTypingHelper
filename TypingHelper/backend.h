#include "global.h"
#include <qstring.h>

typedef struct keyboardrows {
	bool numberRow = true;
	bool topRow = true;
	bool middleRow = true;
	bool bottomRow = true;
} KeyboardRows;

void die_gracefully();
void die(int status, bool print_err, bool show_dialog, ccptr message);
QString parseQtRawKey(int b);
bool isValidKey(int key, KeyboardRows rows);