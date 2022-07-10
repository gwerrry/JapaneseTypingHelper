#include "typinghelper.h"
#include "uibackend.h"
#include "logger.h"
TypingHelper::TypingHelper(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::TypingHelperClass()) {
	ui->setupUi(this);

	connect(ui->main_quit_button, SIGNAL(clicked()), this, SLOT(main_menu_quit_button_clicked()));
}

void TypingHelper::main_menu_quit_button_clicked() {
	die_gracefully();
}

TypingHelper::~TypingHelper() {
	delete ui;
}