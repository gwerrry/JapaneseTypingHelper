#include "backend.h"

LoggerWrapper::LoggerWrapper(QObject* parent) : QObject(parent) {}
void LoggerWrapper::info(const QString str) {
	LOG(LOG_INFO, str.toStdString().c_str());
}
void LoggerWrapper::debug(const QString str) {
	LOG(LOG_DEBUG, str.toStdString().c_str());
}
void LoggerWrapper::warn(const QString str) {
	LOG(LOG_WARNING, str.toStdString().c_str());
}
void LoggerWrapper::error(const QString str) {
	LOG(LOG_ERROR, str.toStdString().c_str());
}
void LoggerWrapper::fatal(const QString str) {
	LOG(LOG_FATAL, str.toStdString().c_str());
}