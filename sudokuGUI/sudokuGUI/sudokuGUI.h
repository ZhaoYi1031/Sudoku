#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sudokuGUI.h"

class sudokuGUI : public QMainWindow
{
	Q_OBJECT

public:
	sudokuGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::sudokuGUIClass ui;
};
