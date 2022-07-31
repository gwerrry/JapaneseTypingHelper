#include "fileparser.h"
#include "fileio.h"
#include <filesystem>
#include <fstream>

using namespace std;
using namespace FileIO;
using namespace BreakfastParser;
namespace fs = std::filesystem;

#pragma warning (disable:4996)

/* This is gonna be a custom file Parser because
*  we aren't storing too much so why not write our own?
*  Format:
*  # = comment
*  strings: "<name>" = "<value>"
*  ints: "<name>" = <value>
*  bools: "<name>" = <true/false>
*/
enum line_side {
	KEY,
	VALUE
};

struct parser_data {
	bool hasCompletedQuote;
	bool readValue;

	enum line_side side;
	value_types expectedType;

	int currentQuoteAmount;
	char expectedChar;
};

void cleanup_element(struct config_element* buf) {
	if(buf != NULL) {
		if(buf->value != NULL) { delete buf->value; }
	}
}

void __stdcall read_line(string line, int current_line, struct config_element& buf) {
	struct parser_data data = {false, false, KEY, INVALID_CONFIG_TYPE, 0, '\0'};
	int keyLength = 0;
	int valLength = 0;

	string val = "";

	for(int j = 0; j < line.length(); j++) {
		char current_char = line[j];
		//skip this cause it mean
		if(current_char == '\n') continue;

		if(data.side == KEY) {
			switch(current_char) {
				case '"':
					{
						data.currentQuoteAmount++;
						if(data.currentQuoteAmount == 2) {
							data.hasCompletedQuote = true;
							data.currentQuoteAmount = 0;
						}
						break;
					}
				case '=':
					{
						if(data.hasCompletedQuote) {
							data.side = VALUE;
							data.hasCompletedQuote = false;
						} else {
							printf("Line %d is invalid(1)\n", current_line);
							buf.isValid = INVALID_LINE; return;
						}
						break;
					}
				default: if(data.currentQuoteAmount != 0) buf.key += current_char;
			}
		} else if(data.side == VALUE) {
			if(current_char == '"') {
				if(data.currentQuoteAmount == 0 && buf.type != INVALID_CONFIG_TYPE) {
					printf("Line %d is invalid(2)\n", current_line);
					buf.isValid = INVALID_LINE; return;
				}
				data.currentQuoteAmount++;
				buf.type = CONFIG_STR;
				if(data.currentQuoteAmount == 2) {
					buf.isValid = VALID_LINE;
					data.readValue = true;
					data.hasCompletedQuote = true;
				}
			} else if(data.currentQuoteAmount == 1) {
				val += current_char;
			} else if(data.currentQuoteAmount == 2 && current_char != ' ' && current_char != '#') {
				printf("Line %d is invalid(16)\n", current_line);
				buf.isValid = INVALID_LINE; return;
			} else {
				if(current_char == ' ') {
					if(buf.type == CONFIG_INT) {
						buf.isValid = VALID_LINE;
						data.readValue = true;
						continue;
					} else if(buf.type == CONFIG_BOOL) {
						printf("Line %d is invalid(2)\n", current_line);
						buf.isValid = INVALID_LINE; return;
					}
				} else if(current_char == '#') {
					if(data.readValue || buf.type == CONFIG_INT) {
						buf.isValid = VALID_LINE;
						buf.type = CONFIG_INT;
						break;
					}
					if(buf.type == CONFIG_BOOL) {
						printf("Line %d is invalid(3)\n", current_line);
						buf.isValid = INVALID_LINE; return;
					}
					if(buf.type == INVALID_CONFIG_TYPE) {
						printf("Line %d is invalid(4)\n", current_line);
						buf.isValid = INVALID_LINE; return;
					}
				} else if(isdigit(current_char)) {
					if(buf.type == CONFIG_BOOL) {
						printf("Line %d is invalid(5)\n", current_line);
						buf.isValid = INVALID_LINE; return;
					}
					buf.type = CONFIG_INT;
					val += current_char;
				} else switch(current_char) {
					case 't':
						{
							if(buf.type == CONFIG_BOOL) {
								printf("Line %d is invalid(6)\n", current_line);
								buf.isValid = INVALID_LINE; return;
							} else {
								data.expectedChar = 'r';
								buf.type = CONFIG_BOOL;
								val += current_char;
							}
							break;
						}
					case 'r':
						{
							if(buf.type != CONFIG_BOOL && data.expectedChar == 'r') {
								printf("Line %d is invalid(7)\n", current_line);
								buf.isValid = INVALID_LINE; return;
							} else {
								data.expectedChar = 'u';
								val += current_char;
							}
							break;
						}
					case 'u':
						{
							if(buf.type != CONFIG_BOOL && data.expectedChar == 'u') {
								printf("Line %d is invalid(8)\n", current_line);
								buf.isValid = INVALID_LINE; return;
							} else {
								data.expectedChar = 'e';
								val += current_char;
							}
							break;
						}
					case 'f':
						{
							if(buf.type == CONFIG_BOOL) {
								printf("Line %d is invalid(9)\n", current_line);
								buf.isValid = INVALID_LINE; return;
							} else {
								data.expectedChar = 'a';
								buf.type = CONFIG_BOOL;
								val += current_char;
							}
							break;
						}
					case 'a':
						{
							if(buf.type != CONFIG_BOOL && data.expectedChar == 'a') {
								printf("Line %d is invalid(10)\n", current_line);
								buf.isValid = INVALID_LINE; return;
							} else {
								data.expectedChar = 'l';
								val += current_char;
							}
							break;
						}
					case 'l':
						{
							if(buf.type != CONFIG_BOOL && data.expectedChar == 'l') {
								printf("Line %d is invalid(11)\n", current_line);
								buf.isValid = INVALID_LINE; return;
							} else {
								data.expectedChar = 's';
								val += current_char;
							}
							break;
						}
					case 's':
						{
							if(buf.type != CONFIG_BOOL && data.expectedChar == 's') {
								printf("Line %d is invalid(12)\n", current_line);
								buf.isValid = INVALID_LINE; return;
							} else {
								data.expectedChar = 'e';
								val += current_char;
							}
							break;
						}
					case 'e':
						{
							if(buf.type != CONFIG_BOOL) {
								printf("Line %d is invalid(13)\n", current_line);
								buf.isValid = INVALID_LINE; return;
							} else {
								data.expectedChar = '#';
								data.readValue = true;
								buf.isValid = VALID_LINE;
								buf.type = CONFIG_BOOL;
								val += current_char;
							}
							break;
						}
					default:
						{
							printf("Line %c is invalid(14)\n", current_char);
							buf.isValid = INVALID_LINE; return;
						}
				}
			}
		}
	}

	if(!buf.isValid) {
		if(buf.type != CONFIG_INT) {
			printf("Line %d is invalid(15)\n", current_line);
			buf.isValid = INVALID_LINE;
			return;
		}
		buf.isValid = VALID_LINE;
	}
	switch(buf.type) {
		case CONFIG_STR:
			{
				char* str = new char[val.length() + 1];
				strcpy(str, val.c_str());
				buf.value = (void*)str;
				break;
			}
		case CONFIG_BOOL:
			{
				if(val.length() == 4) buf.value = (void*)1;
				else buf.value = (void*)0;
				break;
			}
		case CONFIG_INT:
			{
				buf.value = (void*)_atoi64(val.c_str());
				break;
			}
	}

	buf.isValid = VALID_LINE;
}

bool is_element_valid(struct config_element* element) {
	return element != NULL && element->key != "" && element->value != NULL && element->type != INVALID_CONFIG_TYPE && element->isValid != 1;
}

string format_element(struct config_element* element) {
	/*  Check if that bitch is valid */

	if(is_element_valid(element)) { return ""; }

	/* Allocate shit and make it into a string */
	string toReturn = "\"" + element->key + "\"=";

	/* Append the rest... */
	switch(element->type) {
		case CONFIG_STR:
			{
				toReturn += "\"";
				toReturn += (cptr)element->value;
				toReturn += "\"";
			}break;
		case CONFIG_INT:
			{
				char buffer[19];
				sprintf(buffer, "%lld", (long long)element->value);
				toReturn += buffer;
			}break;
		case CONFIG_BOOL:
			{
				bool val = (bool)element->value;
				if(val) toReturn += "true";
				else toReturn += "false";
			}break;
	}

	return toReturn;
}

/*
 * Returns the index the element was found on
 */
int find_element(vector<config_element>* elements, string key) {
	for(int i = 0; i < elements->size(); i++) {
		if(elements->at(i).key == key) {
			return i;
		}
	}
	return -1;
}

/*
 * ````````````````````````Functions that are public (in the header file)````````````````````````````
 */

int BreakfastParser::validate_file(string path) {
	if(!file_exists(path)) {
		printf("File does not exist at %s\n", path);
		return INVALID_FILE;
	}
	vector<string> lines = read_file(path);

	int isValid = VALID_FILE;

	for(int i = 0; i < lines.size(); i++) {
		if(lines[i].length() == 0 || lines[i][0] == '#') {
			continue;
		}
		if(lines[i][0] == '"') {
			struct config_element buf = {"", NULL, INVALID_CONFIG_TYPE, VALID_LINE};
			read_line(lines[i], i, buf);
			if(buf.isValid == INVALID_LINE) {
				isValid = INVALID_FILE;
			}
			cleanup_element(&buf);
		}
	}

	return isValid;
}

/*
 * Reads the config and returns a vector that contains all the config elements.
 */
vector<config_element>* BreakfastParser::read_config(string path) {
	if(!file_exists(path)) {
		printf("File does not exist at %s\n", path);
		return NULL;
	}

	vector<string> lines = read_file(path.c_str());
	vector<config_element>* toReturn = new vector<config_element>();

	for(string line : lines) {
		if(line.length() == 0 || line[0] == '#') {
			continue;
		}
		if(line[0] == '"') {
			struct config_element buf = {"", NULL, INVALID_CONFIG_TYPE, VALID_LINE};
			read_line(line, -1, buf);
			if(buf.isValid == INVALID_LINE) {
				delete toReturn;
				return NULL;
			}
			toReturn->push_back(buf);
		}
	}

	return toReturn;
}

/*
 * Appends the specified config element to the config file at the specified path.
 */
bool BreakfastParser::add_config_value(string path, struct config_element element) {
	if(!file_exists(path)) {
		printf("File does not exist at %s\n", path);
		return false;
	}

	string dataToAppend = format_element(&element);

	if(dataToAppend == "") {
		printf("Something really bad happened while trying to format a value that was about to be added to the config at %s\n", path.c_str());
		return false;
	}

	ofstream outfile;
	outfile.open(path, std::ios::app);
	outfile << dataToAppend << endl;
	return true;
}

/*
 * Removes the specified config element to the config file at the specified path.
 */

bool BreakfastParser::remove_config_value(std::string path, std::string key) {
	if(!file_exists(path)) {
		printf("File does not exist at %s\n", path);
		return false;
	}

	vector<config_element>* elements = read_config(path);

	if(!create_file("tmp.txt")) {
		printf("Could not create temporary file tmp.txt\n");
		delete elements;
		return false;
	}

	int toErase = find_element(elements, key);
	if(toErase == -1) {
		delete elements;
		return false;
	}

	/* Open file for appending */

	ofstream outfile;
	outfile.open("tmp.txt", std::ios::app);

	for(int i = 0; i < elements->size(); i++) {
		if(i != toErase) {
			outfile << format_element(&elements->at(i)) << endl;
		}
	}

	replace_file(path, "tmp.txt");
	delete elements;

	return true;
}