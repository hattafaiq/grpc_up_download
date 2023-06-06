/********************************************************************************
** Form generated from reading UI file 'tampilserver.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAMPILSERVER_H
#define UI_TAMPILSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TampilServer
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TampilServer)
    {
        if (TampilServer->objectName().isEmpty())
            TampilServer->setObjectName(QString::fromUtf8("TampilServer"));
        TampilServer->resize(800, 600);
        menubar = new QMenuBar(TampilServer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        TampilServer->setMenuBar(menubar);
        centralwidget = new QWidget(TampilServer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        TampilServer->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(TampilServer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        TampilServer->setStatusBar(statusbar);

        retranslateUi(TampilServer);

        QMetaObject::connectSlotsByName(TampilServer);
    } // setupUi

    void retranslateUi(QMainWindow *TampilServer)
    {
        TampilServer->setWindowTitle(QApplication::translate("TampilServer", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TampilServer: public Ui_TampilServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAMPILSERVER_H
