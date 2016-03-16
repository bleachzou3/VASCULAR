/********************************************************************************
** Form generated from reading UI file 'vascuview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VASCUVIEW_H
#define UI_VASCUVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_vascuviewClass
{
public:
    QAction *actionOpenImaFile;
    QWidget *centralWidget;
    QFrame *line;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QFrame *line_2;
    QVTKWidget *qvtkWidget_master;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *vascuviewClass)
    {
        if (vascuviewClass->objectName().isEmpty())
            vascuviewClass->setObjectName(QStringLiteral("vascuviewClass"));
        vascuviewClass->resize(1628, 917);
        actionOpenImaFile = new QAction(vascuviewClass);
        actionOpenImaFile->setObjectName(QStringLiteral("actionOpenImaFile"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/picture/openfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenImaFile->setIcon(icon);
        centralWidget = new QWidget(vascuviewClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(490, 0, 20, 581));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 20, 481, 541));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 570, 1611, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        qvtkWidget_master = new QVTKWidget(centralWidget);
        qvtkWidget_master->setObjectName(QStringLiteral("qvtkWidget_master"));
        qvtkWidget_master->setGeometry(QRect(670, 0, 791, 571));
        vascuviewClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(vascuviewClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1628, 21));
        vascuviewClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(vascuviewClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        vascuviewClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(vascuviewClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        vascuviewClass->setStatusBar(statusBar);

        mainToolBar->addAction(actionOpenImaFile);

        retranslateUi(vascuviewClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(vascuviewClass);
    } // setupUi

    void retranslateUi(QMainWindow *vascuviewClass)
    {
        vascuviewClass->setWindowTitle(QApplication::translate("vascuviewClass", "vascuview", 0));
        actionOpenImaFile->setText(QApplication::translate("vascuviewClass", "openImaFile", 0));
#ifndef QT_NO_TOOLTIP
        actionOpenImaFile->setToolTip(QApplication::translate("vascuviewClass", "open a ima file sequence in a directory", 0));
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("vascuviewClass", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("vascuviewClass", "Tab 2", 0));
    } // retranslateUi

};

namespace Ui {
    class vascuviewClass: public Ui_vascuviewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VASCUVIEW_H
