/**
 * @file logger.c
 * @author gwerrry
 * @brief Simple logger made for C in C.
 * @version 0.4
 * @date 2022-08-14
 *
 * @copyright Copyright (c) 2022
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

 /**
  * If you're getting a warning, it's probably warning 4996 because of the use of ctime() in the logger. You can disable the warning by uncommenting the line below.
  */
#pragma warning(disable:4996)

#ifdef _WIN32
#include <Windows.h>
/* DARK RED */
#define LOG_FATAL_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
/* BLUE */
#define LOG_DEBUG_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
/* DARK YELLOW */
#define LOG_WARNING_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
/* GRAY */
#define LOG_INFO_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
/* RED */
#define LOG_ERROR_COLOR SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);

#elif __linux__
#include <locale.h>
/* DARK RED */
#define LOG_FATAL_COLOR printf("\e[0;31m");
/* BLUE */
#define LOG_DEBUG_COLOR printf("\e[0;34m\e[1m");
/* DARK YELLOW */
#define LOG_WARNING_COLOR printf("\e[0;33m");
/* GRAY */
#define LOG_INFO_COLOR printf("\e[0m");
/* RED */
#define LOG_ERROR_COLOR printf("\e[0;31m\e[1m");

#endif

#define INFO_TAG "INFO"
#define DEBUG_TAG "DEBUG"
#define WARNING_TAG "WARN"
#define ERROR_TAG "ERROR"
#define FATAL_TAG "FATAL"


// Private Functions

/**
 * @brief Changes the current color of the terminal text.
 */
void log_text_color(enum LogLevel level) {
	switch (level) {
	case LOG_FATAL:
		LOG_FATAL_COLOR
			break;

	case LOG_DEBUG:
		LOG_DEBUG_COLOR /* BLUE */
			break;

	case LOG_WARNING:
		LOG_WARNING_COLOR /* DARK YELLOW */
			break;

	case LOG_INFO:
		LOG_INFO_COLOR /* RESET COLOR */
			break;

	case LOG_ERROR:
		LOG_ERROR_COLOR /* RED */
			break;

	default:
		LOG_INFO_COLOR /* GRAY */
			break;
	}
}

/**
 * @brief Resets the color of the terminal text.
 */
void log_text_reset() {
	LOG_INFO_COLOR /* RESET COLOR */
}

/**
 * @brief Returns a string determinted by the LogLevel provided.
 */
const char* get_log_level_str(enum LogLevel level) {
	switch (level) {
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

/**
 * @brief Logs the provided message with arguments. Format: "%Date/Time% [%ProvidedTag%] %message%".
 */
void log_format(const char* tag, const char* message, va_list args) {
	time_t now;
	time(&now);
	char* date = ctime(&now);
	date[strlen(date) - 1] = '\0'; /* Removes the line break */

	printf("%s [%s] ", date, tag); /* Print date and tag */
	vprintf(message, args); /* Print message */
	printf("\n");
	log_text_reset();
}

// Public Functions
/**
 * @brief Set the logger to support UTF-8. This is required for the logger to print out UTF-8 characters.
 */
void setupLogger() {
#ifdef WIN32
	SetConsoleOutputCP(CP_UTF8);
#elif __linux__
	setlocale(LC_ALL, "en_US.UTF-8");
#endif 
}

/**
 * @brief Logs the provided message to terminal with the provided LogLevel. Format: "%Date/Time% [%ProvidedTag%] %message%".
 */
void LOG(enum LogLevel level, const char* message, ...) {
	log_text_color(level);

	va_list args;
	va_start(args, message);
	log_format(get_log_level_str(level), message, args); /* Print log message */
	va_end(args);

	log_text_reset();
}

#undef INFO_TAG
#undef DEBUG_TAG
#undef WARNING_TAG
#undef ERROR_TAG
#undef FATAL_TAG
#undef LOG_INFO_COLOR
#undef LOG_DEBUG_COLOR
#undef LOG_WARNING_COLOR
#undef LOG_ERROR_COLOR
#undef LOG_FATAL_COLOR