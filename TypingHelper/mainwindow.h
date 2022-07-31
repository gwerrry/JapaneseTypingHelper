#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_typinghelper.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TypingHelperClass; };
QT_END_NAMESPACE

class TypingHelper : public QMainWindow {
	Q_OBJECT

public:
	TypingHelper(QWidget* parent = nullptr);
	~TypingHelper();
public slots:
	void main_menu_quit_button_clicked();
private:
	Ui::TypingHelperClass* ui;
protected:
	void keyPressEvent(QKeyEvent* event);
};
