#include "ConfigFile.h"
#include <filesystem>
#include <nlohmann/json.hpp>

using namespace std;
namespace fs = filesystem;
using json = nlohmann::json;

ConfigFile::ConfigFile(fs::path filePath) {
	m_filePath = filePath;
	setup();
	load();
}