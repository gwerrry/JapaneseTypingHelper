#include "logger.h"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>

cstr FATAL_TAG = "FATAL";
cstr DEBUG_TAG = "DEBUG";
cstr WARNING_TAG = "WARN";
cstr INFO_TAG = "INFO";
cstr ERROR_TAG = "ERROR";

#ifdef WIN32
#include <Windows.h>

/* DARK RED */
#define LOG_FATAL_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
/* BLUE */
#define LOG_DEBUG_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
/* DARK YELLOW */
#define LOG_WARNING_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
/* GRAY */
#define LOG_INFO_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
/* RED */
#define LOG_ERROR_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);

#endif // WIN32

#ifdef LINUX

/* DARK RED */
#define LOG_FATAL_COLOR printf("\x1B[0;31m");
/* BLUE */
#define LOG_DEBUG_COLOR printf("\x1B[0;34m");
/* DARK YELLOW */
#define LOG_WARNING_COLOR printf("\x1B[1;33m");
/* GRAY */
#define LOG_INFO_COLOR printf("\x1B[0;37m");
/* RED */
#define LOG_ERROR_COLOR printf("\x1B[1;31m");

#endif // LINUX

void log_text_color(enum LogLevel level) {
	switch(level) {
		case LOG_FATAL:
			LOG_FATAL_COLOR /* DARK RED */
				break;

		case LOG_DEBUG:
			LOG_DEBUG_COLOR /* BLUE */
				break;

		case LOG_WARNING:
			LOG_WARNING_COLOR /* DARK YELLOW */
				break;

		case LOG_INFO:
			LOG_INFO_COLOR /* GRAY */
				break;

		case LOG_ERROR:
			LOG_ERROR_COLOR /* RED */
				break;

		default:
			LOG_INFO_COLOR /* GRAY */
				break;
	}
}

void log_text_reset() {
	LOG_INFO_COLOR /* GRAY */
}

cstr get_log_level_str(enum LogLevel level) {
	switch(level) {
		case LOG_FATAL:
			return FATAL_TAG;
		case LOG_DEBUG:
			return DEBUG_TAG;
		case LOG_WARNING:
			return WARNING_TAG;
		case LOG_INFO:
			return INFO_TAG;
		case LOG_ERROR:
			return ERROR_TAG;
		default:
			return INFO_TAG;
	}
}

void log_format(cstr tag, cstr message, va_list args) {
	time_t now;
	time(&now);
	char* date = ctime(&now);
	date[strlen(date) - 1] = '\0'; /* Removes the line break */
	printf("%s [%s] ", date, tag); /* Print date and tag */

	//vprintf(fmt::format(message, args).c_str(), args);
	vprintf(message, args); /* Print message */

	printf("\n");
}

void LOG(enum LogLevel level, cstr message, ...) {
	log_text_color(level);

	va_list args;
	va_start(args, message);
	log_format(get_log_level_str(level), message, args); /* Print log message */
	va_end(args);

	//..log_format(get_log_level_str(level), message, fmt::make_format_args(message));
	log_text_reset();
}