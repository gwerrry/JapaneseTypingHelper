#include "global.h"

#ifdef __cplusplus
extern "C" {
	#endif
	#ifndef LOGGER_H
	#define LOGGER_H

	enum LogLevel {
		LOG_FATAL,
		LOG_DEBUG,
		LOG_WARNING,
		LOG_INFO,
		LOG_ERROR
	};

	void LOG(enum LogLevel level, ccptr message, ...);

	#ifdef __cplusplus
}
#endif
#endif