/********************************************************************************
** Form generated from reading UI file 'sudokuGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUDOKUGUI_H
#define UI_SUDOKUGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sudokuGUIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *sudokuGUIClass)
    {
        if (sudokuGUIClass->objectName().isEmpty())
            sudokuGUIClass->setObjectName(QStringLiteral("sudokuGUIClass"));
        sudokuGUIClass->resize(600, 400);
        menuBar = new QMenuBar(sudokuGUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        sudokuGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(sudokuGUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        sudokuGUIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(sudokuGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sudokuGUIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(sudokuGUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        sudokuGUIClass->setStatusBar(statusBar);

        retranslateUi(sudokuGUIClass);

        QMetaObject::connectSlotsByName(sudokuGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *sudokuGUIClass)
    {
        sudokuGUIClass->setWindowTitle(QApplication::translate("sudokuGUIClass", "sudokuGUI", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sudokuGUIClass: public Ui_sudokuGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUDOKUGUI_H
