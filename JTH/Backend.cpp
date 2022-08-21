#include "Backend.h"
#include "global.h"
#include "Converter.h"
#include <qcoreapplication.h>
#include "logger.h"
Backend::Backend(QObject* parent, QQmlContext* context) : QObject(parent) {
	lang = new Language();
	lang->setContext(context);
	
	if (!setupConfig()) {
		LOG(LOG_FATAL, "Failed to set up Config!");
		exit(-1);
	}

	musicVolume = config->getInt(CONFIG_MUSIC_VOLUME);
	sfxVolume = config->getInt(CONFIG_SFX_VOLUME);
	currentLanguage = config->getInt(CONFIG_LANGUAGE);
	katakanaOption = config->getBool(CONFIG_KATAKANA_MODE);
	Converter::switchCharacterSet(katakanaOption);
	lang->setLanguage(currentLanguage);
}

bool Backend::setupConfig() {
	std::string config_path = get_current_dir();
	config_path += "/";
	config_path += DATA_DIRECTORY;
	config_path += "/config.json";

	config = new ConfigFile(config_path);
	config->addDefaultBool(CONFIG_KATAKANA_MODE, CONFIG_KATAKANA_DEFAULT);
	config->addDefaultInt(CONFIG_LANGUAGE, CONFIG_LANGUAGE_DEFAULT);
	config->addDefaultInt(CONFIG_MUSIC_VOLUME, CONFIG_MUSIC_VOLUME_DEFAULT);
	config->addDefaultInt(CONFIG_SFX_VOLUME, CONFIG_SFX_VOLUME_DEFAULT);
	
	return config->setup();
}

void Backend::setKatakana(bool katakanaOption) {
	config->setBool(CONFIG_KATAKANA_MODE, katakanaOption);
	this->katakanaOption = katakanaOption;
	Converter::switchCharacterSet(katakanaOption);
}
void Backend::saveSettingsMenu(int musicVolume, int sfxVolume, int language) {
	config->setInt(CONFIG_MUSIC_VOLUME, musicVolume);
	config->setInt(CONFIG_SFX_VOLUME, sfxVolume);
	config->setInt(CONFIG_LANGUAGE, language);
	lang->setLanguage(language);
	this->musicVolume = musicVolume;
	this->sfxVolume = sfxVolume;
	this->currentLanguage = language;
	/*
	
	
	
	
	
	
	
	
	
	
	
	
	*/
	//update music and other volume stuff here. DO not FORGET!
}

bool Backend::usingKatakana() { return katakanaOption; }
int Backend::getMusicVolume() { return musicVolume; }
int Backend::getSfxVolume() { return sfxVolume; }
int Backend::getCurrentLanguage() { return currentLanguage; }

void Backend::quit() {
	QCoreApplication::exit(0);
}