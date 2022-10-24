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
	firstRowOption = config->getBool(CONFIG_FIRST_ROW);
	secondRowOption = config->getBool(CONFIG_SECOND_ROW);
	thirdRowOption = config->getBool(CONFIG_THRID_ROW);
	fourthRowOption = config->getBool(CONFIG_FOURTH_ROW);
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
	config->addDefaultBool(CONFIG_FIRST_ROW, CONFIG_FIRST_ROW_DEFAULT);
	config->addDefaultBool(CONFIG_SECOND_ROW, CONFIG_SECOND_ROW_DEFAULT);
	config->addDefaultBool(CONFIG_THRID_ROW, CONFIG_THRID_ROW_DEFAULT);
	config->addDefaultBool(CONFIG_FOURTH_ROW, CONFIG_FOURTH_ROW_DEFAULT);
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

void Backend::setKatana(bool katana) {

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

void Backend::saveGameSettings(bool katakanaMode, bool firstRow, bool secondRow, bool thirdRow, bool forthRow) {

}

bool Backend::usingKatakana() { return katakanaOption; }
int Backend::getMusicVolume() { return musicVolume; }
int Backend::getSfxVolume() { return sfxVolume; }
int Backend::getCurrentLanguage() { return currentLanguage; }

void Backend::quit() {
	QCoreApplication::exit(0);
}