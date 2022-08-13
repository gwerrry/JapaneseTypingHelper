#include "backend.h"

Backend::Backend(QObject* parent) : QObject(parent) {
}

void die_gracefully(int exitcode) {
	LOG(LOG_INFO, "App is exiting with code %d", exitcode);
	exit(exitcode);
}