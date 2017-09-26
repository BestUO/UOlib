/********************************************************************************
** Form generated from reading UI file 'UOlib_qt.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UOLIB_QT_H
#define UI_UOLIB_QT_H

#include <MyGraphicsView.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UOlib_QTClass
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_4;
    MyGraphicsView *graphicsView;

    void setupUi(QWidget *UOlib_QTClass)
    {
        if (UOlib_QTClass->objectName().isEmpty())
            UOlib_QTClass->setObjectName(QStringLiteral("UOlib_QTClass"));
        UOlib_QTClass->resize(977, 611);
        verticalLayout = new QVBoxLayout(UOlib_QTClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_2 = new QPushButton(UOlib_QTClass);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        widget = new QWidget(UOlib_QTClass);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        radioButton_3 = new QRadioButton(widget);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        gridLayout->addWidget(radioButton_3, 0, 2, 1, 1);

        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        gridLayout->addWidget(radioButton_2, 0, 1, 1, 1);

        radioButton = new QRadioButton(widget);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        gridLayout->addWidget(radioButton, 0, 0, 1, 1);

        radioButton_4 = new QRadioButton(widget);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));

        gridLayout->addWidget(radioButton_4, 1, 0, 1, 1);


        verticalLayout->addWidget(widget);

        graphicsView = new MyGraphicsView(UOlib_QTClass);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(graphicsView);


        retranslateUi(UOlib_QTClass);

        QMetaObject::connectSlotsByName(UOlib_QTClass);
    } // setupUi

    void retranslateUi(QWidget *UOlib_QTClass)
    {
        UOlib_QTClass->setWindowTitle(QApplication::translate("UOlib_QTClass", "UOlib_QT", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("UOlib_QTClass", "PushButton", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("UOlib_QTClass", "RadioButton", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("UOlib_QTClass", "RadioButton", Q_NULLPTR));
        radioButton->setText(QApplication::translate("UOlib_QTClass", "RadioButton", Q_NULLPTR));
        radioButton_4->setText(QApplication::translate("UOlib_QTClass", "RadioButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UOlib_QTClass: public Ui_UOlib_QTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UOLIB_QT_H
