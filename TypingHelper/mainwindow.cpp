#include "mainwindow.h"
#include "backend.h"
#include "logger.h"
#include <qevent.h>
#include "ConfigFile.h"

TypingHelper::TypingHelper(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::TypingHelperClass()) {
	ui->setupUi(this);

	bool buf = false;
	settings->getBool(KATAKANA_OPTION, buf);
	if(buf) {
		switchCharacterSet(true);
	}

	connect(ui->main_quit_button, SIGNAL(clicked()), this, SLOT(main_menu_quit_button_clicked()));
	ui->main_menu->setCurrentIndex(3);
}

void TypingHelper::keyPressEvent(QKeyEvent* event) {
	int key = event->key();
	KeyboardRows check_all_rows = {true, true, true, true};
	if(isValidKey(key, check_all_rows)) ui->current_character_label->setText(parseQtRawKey(event->key()));
	else ui->current_character_label->setText("none");
}

void TypingHelper::main_menu_quit_button_clicked() {
	die_gracefully();
}

TypingHelper::~TypingHelper() {
	delete ui;
}