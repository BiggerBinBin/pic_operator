/********************************************************************************
** Form generated from reading UI file 'viewTest.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWTEST_H
#define UI_VIEWTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_viewTestClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *openPic;
    QPushButton *savePic;
    QPushButton *emphasicPic;
    QPushButton *lowPic;
    QPushButton *blurPic;
    QPushButton *drawbutton;
    QLabel *label_x;
    QLabel *label_y;
    QLabel *label_scan;
    QSpacerItem *verticalSpacer;
    QLabel *disply_lab;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *viewTestClass)
    {
        if (viewTestClass->objectName().isEmpty())
            viewTestClass->setObjectName(QStringLiteral("viewTestClass"));
        viewTestClass->resize(753, 553);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(viewTestClass->sizePolicy().hasHeightForWidth());
        viewTestClass->setSizePolicy(sizePolicy);
        viewTestClass->setMinimumSize(QSize(753, 553));
        viewTestClass->setMaximumSize(QSize(16777215, 16777215));
        centralWidget = new QWidget(viewTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        openPic = new QPushButton(centralWidget);
        openPic->setObjectName(QStringLiteral("openPic"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(openPic->sizePolicy().hasHeightForWidth());
        openPic->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(openPic);

        savePic = new QPushButton(centralWidget);
        savePic->setObjectName(QStringLiteral("savePic"));
        sizePolicy1.setHeightForWidth(savePic->sizePolicy().hasHeightForWidth());
        savePic->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(savePic);

        emphasicPic = new QPushButton(centralWidget);
        emphasicPic->setObjectName(QStringLiteral("emphasicPic"));
        sizePolicy1.setHeightForWidth(emphasicPic->sizePolicy().hasHeightForWidth());
        emphasicPic->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(emphasicPic);

        lowPic = new QPushButton(centralWidget);
        lowPic->setObjectName(QStringLiteral("lowPic"));
        sizePolicy1.setHeightForWidth(lowPic->sizePolicy().hasHeightForWidth());
        lowPic->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(lowPic);

        blurPic = new QPushButton(centralWidget);
        blurPic->setObjectName(QStringLiteral("blurPic"));
        sizePolicy1.setHeightForWidth(blurPic->sizePolicy().hasHeightForWidth());
        blurPic->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(blurPic);

        drawbutton = new QPushButton(centralWidget);
        drawbutton->setObjectName(QStringLiteral("drawbutton"));
        sizePolicy1.setHeightForWidth(drawbutton->sizePolicy().hasHeightForWidth());
        drawbutton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(drawbutton);

        label_x = new QLabel(centralWidget);
        label_x->setObjectName(QStringLiteral("label_x"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_x->sizePolicy().hasHeightForWidth());
        label_x->setSizePolicy(sizePolicy2);
        label_x->setTextFormat(Qt::RichText);

        verticalLayout->addWidget(label_x);

        label_y = new QLabel(centralWidget);
        label_y->setObjectName(QStringLiteral("label_y"));

        verticalLayout->addWidget(label_y);

        label_scan = new QLabel(centralWidget);
        label_scan->setObjectName(QStringLiteral("label_scan"));

        verticalLayout->addWidget(label_scan);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        disply_lab = new QLabel(centralWidget);
        disply_lab->setObjectName(QStringLiteral("disply_lab"));
        sizePolicy.setHeightForWidth(disply_lab->sizePolicy().hasHeightForWidth());
        disply_lab->setSizePolicy(sizePolicy);
        disply_lab->setMinimumSize(QSize(650, 476));
        disply_lab->setMaximumSize(QSize(16777215, 16777215));
        disply_lab->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        gridLayout->addWidget(disply_lab, 0, 1, 1, 1);

        gridLayout->setColumnMinimumWidth(0, 1);
        gridLayout->setColumnMinimumWidth(1, 10);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        viewTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(viewTestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 753, 23));
        viewTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(viewTestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        viewTestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(viewTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        viewTestClass->setStatusBar(statusBar);

        retranslateUi(viewTestClass);

        QMetaObject::connectSlotsByName(viewTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *viewTestClass)
    {
        viewTestClass->setWindowTitle(QApplication::translate("viewTestClass", "viewTest", Q_NULLPTR));
        openPic->setText(QApplication::translate("viewTestClass", "\346\211\223\345\274\200\345\233\276\347\211\207", Q_NULLPTR));
        savePic->setText(QApplication::translate("viewTestClass", "\344\277\235\345\255\230\345\233\276\347\211\207", Q_NULLPTR));
        emphasicPic->setText(QApplication::translate("viewTestClass", "\351\224\220\345\214\226", Q_NULLPTR));
        lowPic->setText(QApplication::translate("viewTestClass", "\345\216\273\350\272\201", Q_NULLPTR));
        blurPic->setText(QApplication::translate("viewTestClass", "\346\250\241\347\263\212", Q_NULLPTR));
        drawbutton->setText(QApplication::translate("viewTestClass", "\347\273\230\345\233\276\346\250\241\345\274\217", Q_NULLPTR));
        label_x->setText(QApplication::translate("viewTestClass", "x:00", Q_NULLPTR));
        label_y->setText(QApplication::translate("viewTestClass", "y:00", Q_NULLPTR));
        label_scan->setText(QApplication::translate("viewTestClass", "100%", Q_NULLPTR));
        disply_lab->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class viewTestClass: public Ui_viewTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWTEST_H
