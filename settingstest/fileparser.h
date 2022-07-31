#pragma once
#include "global.h"
#include <string>
#include <vector>

namespace BreakfastParser {
	const int INVALID_FILE = -1;
	const int INVALID_LINE = -2;
	const int VALID_FILE = 1;
	const int VALID_LINE = 2;

	typedef enum rawtypes {
		CONFIG_INT,
		CONFIG_STR,
		CONFIG_BOOL,
		INVALID_CONFIG_TYPE
	} value_types;

	struct config_element {
		std::string key;
		void* value;
		rawtypes type;
		int isValid;
	};

	int validate_file(std::string path);
	std::vector<config_element>* read_config(std::string path);
	bool add_config_value(std::string path, struct config_element element);
	bool remove_config_value(std::string path, std::string key);
}