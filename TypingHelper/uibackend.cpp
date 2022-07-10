#include "uibackend.h"
#include "logger.h"

#include <qmessagebox.h>
#include <qmainwindow.h>
#include <stdlib.h>

void die_gracefully() {
	LOG(LOG_INFO, "App is exiting with code 0");
	exit(0);
}

void die(int status, bool print_err, bool show_dialog, cstr err) {

	if(print_err) {
		LOG(LOG_FATAL, err);
	}

	if(show_dialog) {
		QMessageBox msgBox;
		msgBox.setText(err);
		msgBox.exec();
	}

	LOG(LOG_INFO, "App is exiting with code %d", status);
	abort();
}
