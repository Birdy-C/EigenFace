/********************************************************************************
** Form generated from reading UI file 'CV_eigenface.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CV_EIGENFACE_H
#define UI_CV_EIGENFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CV_eigenfaceClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_6;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CV_eigenfaceClass)
    {
        if (CV_eigenfaceClass->objectName().isEmpty())
            CV_eigenfaceClass->setObjectName(QStringLiteral("CV_eigenfaceClass"));
        CV_eigenfaceClass->resize(188, 352);
        centralWidget = new QWidget(CV_eigenfaceClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 45, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        verticalLayout->addWidget(pushButton_6);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 44, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        CV_eigenfaceClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CV_eigenfaceClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 188, 23));
        CV_eigenfaceClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CV_eigenfaceClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CV_eigenfaceClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CV_eigenfaceClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CV_eigenfaceClass->setStatusBar(statusBar);

        retranslateUi(CV_eigenfaceClass);

        QMetaObject::connectSlotsByName(CV_eigenfaceClass);
    } // setupUi

    void retranslateUi(QMainWindow *CV_eigenfaceClass)
    {
        CV_eigenfaceClass->setWindowTitle(QApplication::translate("CV_eigenfaceClass", "CV_eigenface", 0));
        pushButton_3->setText(QApplication::translate("CV_eigenfaceClass", "trainfacespace", 0));
        pushButton_2->setText(QApplication::translate("CV_eigenfaceClass", "loadfacespace", 0));
        pushButton->setText(QApplication::translate("CV_eigenfaceClass", "savefacespace", 0));
        pushButton_6->setText(QApplication::translate("CV_eigenfaceClass", "reconduct", 0));
        pushButton_4->setText(QApplication::translate("CV_eigenfaceClass", "retrive", 0));
        pushButton_5->setText(QApplication::translate("CV_eigenfaceClass", "retrive_whole", 0));
    } // retranslateUi

};

namespace Ui {
    class CV_eigenfaceClass: public Ui_CV_eigenfaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CV_EIGENFACE_H
