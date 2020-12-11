/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Canvas2D.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionQuit;
    QAction *actionRevert;
    QAction *actionCopy3Dto2D;
    QAction *actionClear;
    QAction *actionUseOrbitingCamera;
    QWidget *centralWidget;
    QGridLayout *gridLayout_10;
    QTabWidget *tabWidget;
    QWidget *tab2D;
    QGridLayout *gridLayout_11;
    QScrollArea *scrollArea;
    Canvas2D *canvas2D;
    QWidget *tab3D;
    QGridLayout *gridLayout_12;
    QWidget *canvas3D;
    QDockWidget *marbleDock;
    QWidget *marblDockContents;
    QGroupBox *marbleType;
    QVBoxLayout *verticalLayout;
    QRadioButton *marbleTypeMetal;
    QRadioButton *marbleTypeGlass;
    QRadioButton *marbleTypeWood;
    QRadioButton *marbleTypeJelly;
    QRadioButton *marbleTypeRubber;
    QWidget *marbleGravity;
    QHBoxLayout *horizontalLayout_2;
    QLabel *marbleGravityLabel;
    QSlider *marbleGravitySlider;
    QLineEdit *marbleGravityTextbox;
    QWidget *marbleRadius;
    QHBoxLayout *horizontalLayout_3;
    QLabel *marbleRadiusLabel;
    QSlider *marbleRadiusSlider;
    QLineEdit *marbleRadiusTextbox;
    QWidget *marbleWeight;
    QHBoxLayout *horizontalLayout_4;
    QLabel *marbleWeightLabel;
    QSlider *marbleWeightSlider;
    QLineEdit *marbleWeightTextbox;
    QWidget *marbleButton;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton;
    QWidget *clearMarbles;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuToolbars;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 3112);
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks|QMainWindow::VerticalTabs);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionRevert = new QAction(MainWindow);
        actionRevert->setObjectName(QString::fromUtf8("actionRevert"));
        actionRevert->setEnabled(true);
        actionCopy3Dto2D = new QAction(MainWindow);
        actionCopy3Dto2D->setObjectName(QString::fromUtf8("actionCopy3Dto2D"));
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        actionUseOrbitingCamera = new QAction(MainWindow);
        actionUseOrbitingCamera->setObjectName(QString::fromUtf8("actionUseOrbitingCamera"));
        actionUseOrbitingCamera->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_10 = new QGridLayout(centralWidget);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tab2D = new QWidget();
        tab2D->setObjectName(QString::fromUtf8("tab2D"));
        gridLayout_11 = new QGridLayout(tab2D);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_11->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(tab2D);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setLineWidth(0);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(true);
        canvas2D = new Canvas2D();
        canvas2D->setObjectName(QString::fromUtf8("canvas2D"));
        canvas2D->setGeometry(QRect(0, 0, 316, 3061));
        scrollArea->setWidget(canvas2D);

        gridLayout_11->addWidget(scrollArea, 0, 0, 1, 1);

        tabWidget->addTab(tab2D, QString());
        tab3D = new QWidget();
        tab3D->setObjectName(QString::fromUtf8("tab3D"));
        gridLayout_12 = new QGridLayout(tab3D);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_12->setContentsMargins(0, 0, 0, 0);
        canvas3D = new QWidget(tab3D);
        canvas3D->setObjectName(QString::fromUtf8("canvas3D"));

        gridLayout_12->addWidget(canvas3D, 0, 0, 1, 1);

        tabWidget->addTab(tab3D, QString());

        gridLayout_10->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        marbleDock = new QDockWidget(MainWindow);
        marbleDock->setObjectName(QString::fromUtf8("marbleDock"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(marbleDock->sizePolicy().hasHeightForWidth());
        marbleDock->setSizePolicy(sizePolicy);
        marbleDock->setFloating(false);
        marbleDock->setAllowedAreas(Qt::AllDockWidgetAreas);
        marblDockContents = new QWidget();
        marblDockContents->setObjectName(QString::fromUtf8("marblDockContents"));
        sizePolicy.setHeightForWidth(marblDockContents->sizePolicy().hasHeightForWidth());
        marblDockContents->setSizePolicy(sizePolicy);
        marbleType = new QGroupBox(marblDockContents);
        marbleType->setObjectName(QString::fromUtf8("marbleType"));
        marbleType->setGeometry(QRect(9, 9, 121, 171));
        verticalLayout = new QVBoxLayout(marbleType);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 5, -1, 5);
        marbleTypeMetal = new QRadioButton(marbleType);
        marbleTypeMetal->setObjectName(QString::fromUtf8("marbleTypeMetal"));
        marbleTypeMetal->setChecked(true);

        verticalLayout->addWidget(marbleTypeMetal);

        marbleTypeGlass = new QRadioButton(marbleType);
        marbleTypeGlass->setObjectName(QString::fromUtf8("marbleTypeGlass"));

        verticalLayout->addWidget(marbleTypeGlass);

        marbleTypeWood = new QRadioButton(marbleType);
        marbleTypeWood->setObjectName(QString::fromUtf8("marbleTypeWood"));

        verticalLayout->addWidget(marbleTypeWood);

        marbleTypeJelly = new QRadioButton(marbleType);
        marbleTypeJelly->setObjectName(QString::fromUtf8("marbleTypeJelly"));

        verticalLayout->addWidget(marbleTypeJelly);

        marbleTypeRubber = new QRadioButton(marbleType);
        marbleTypeRubber->setObjectName(QString::fromUtf8("marbleTypeRubber"));

        verticalLayout->addWidget(marbleTypeRubber);

        marbleGravity = new QWidget(marblDockContents);
        marbleGravity->setObjectName(QString::fromUtf8("marbleGravity"));
        marbleGravity->setEnabled(true);
        marbleGravity->setGeometry(QRect(10, 190, 211, 43));
        horizontalLayout_2 = new QHBoxLayout(marbleGravity);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        marbleGravityLabel = new QLabel(marbleGravity);
        marbleGravityLabel->setObjectName(QString::fromUtf8("marbleGravityLabel"));

        horizontalLayout_2->addWidget(marbleGravityLabel);

        marbleGravitySlider = new QSlider(marbleGravity);
        marbleGravitySlider->setObjectName(QString::fromUtf8("marbleGravitySlider"));
        marbleGravitySlider->setMinimumSize(QSize(100, 0));
        marbleGravitySlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(marbleGravitySlider);

        marbleGravityTextbox = new QLineEdit(marbleGravity);
        marbleGravityTextbox->setObjectName(QString::fromUtf8("marbleGravityTextbox"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(marbleGravityTextbox->sizePolicy().hasHeightForWidth());
        marbleGravityTextbox->setSizePolicy(sizePolicy1);
        marbleGravityTextbox->setMinimumSize(QSize(40, 0));
        marbleGravityTextbox->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_2->addWidget(marbleGravityTextbox);

        marbleRadius = new QWidget(marblDockContents);
        marbleRadius->setObjectName(QString::fromUtf8("marbleRadius"));
        marbleRadius->setGeometry(QRect(10, 240, 231, 43));
        sizePolicy.setHeightForWidth(marbleRadius->sizePolicy().hasHeightForWidth());
        marbleRadius->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(marbleRadius);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        marbleRadiusLabel = new QLabel(marbleRadius);
        marbleRadiusLabel->setObjectName(QString::fromUtf8("marbleRadiusLabel"));

        horizontalLayout_3->addWidget(marbleRadiusLabel);

        marbleRadiusSlider = new QSlider(marbleRadius);
        marbleRadiusSlider->setObjectName(QString::fromUtf8("marbleRadiusSlider"));
        marbleRadiusSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(marbleRadiusSlider);

        marbleRadiusTextbox = new QLineEdit(marbleRadius);
        marbleRadiusTextbox->setObjectName(QString::fromUtf8("marbleRadiusTextbox"));
        sizePolicy1.setHeightForWidth(marbleRadiusTextbox->sizePolicy().hasHeightForWidth());
        marbleRadiusTextbox->setSizePolicy(sizePolicy1);
        marbleRadiusTextbox->setMinimumSize(QSize(40, 0));
        marbleRadiusTextbox->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_3->addWidget(marbleRadiusTextbox);

        marbleWeight = new QWidget(marblDockContents);
        marbleWeight->setObjectName(QString::fromUtf8("marbleWeight"));
        marbleWeight->setGeometry(QRect(10, 300, 231, 43));
        horizontalLayout_4 = new QHBoxLayout(marbleWeight);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        marbleWeightLabel = new QLabel(marbleWeight);
        marbleWeightLabel->setObjectName(QString::fromUtf8("marbleWeightLabel"));

        horizontalLayout_4->addWidget(marbleWeightLabel);

        marbleWeightSlider = new QSlider(marbleWeight);
        marbleWeightSlider->setObjectName(QString::fromUtf8("marbleWeightSlider"));
        marbleWeightSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(marbleWeightSlider);

        marbleWeightTextbox = new QLineEdit(marbleWeight);
        marbleWeightTextbox->setObjectName(QString::fromUtf8("marbleWeightTextbox"));
        sizePolicy1.setHeightForWidth(marbleWeightTextbox->sizePolicy().hasHeightForWidth());
        marbleWeightTextbox->setSizePolicy(sizePolicy1);
        marbleWeightTextbox->setMinimumSize(QSize(40, 0));
        marbleWeightTextbox->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_4->addWidget(marbleWeightTextbox);

        marbleButton = new QWidget(marblDockContents);
        marbleButton->setObjectName(QString::fromUtf8("marbleButton"));
        marbleButton->setGeometry(QRect(10, 350, 231, 43));
        horizontalLayout_5 = new QHBoxLayout(marbleButton);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButton = new QPushButton(marbleButton);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_5->addWidget(pushButton);

        clearMarbles = new QWidget(marblDockContents);
        clearMarbles->setObjectName(QString::fromUtf8("clearMarbles"));
        clearMarbles->setGeometry(QRect(10, 400, 251, 31));
        pushButton_2 = new QPushButton(clearMarbles);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(0, 0, 221, 32));
        marbleDock->setWidget(marblDockContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, marbleDock);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuToolbars = new QMenu(menuBar);
        menuToolbars->setObjectName(QString::fromUtf8("menuToolbars"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuToolbars->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionRevert);
        menuFile->addAction(actionClear);
        menuFile->addAction(actionCopy3Dto2D);
        menuFile->addAction(actionUseOrbitingCamera);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionSave, SIGNAL(triggered()), MainWindow, SLOT(fileSave()));
        QObject::connect(actionOpen, SIGNAL(triggered()), MainWindow, SLOT(fileOpen()));
        QObject::connect(actionNew, SIGNAL(triggered()), MainWindow, SLOT(fileNew()));
        QObject::connect(actionCopy3Dto2D, SIGNAL(triggered()), MainWindow, SLOT(fileCopy3Dto2D()));
        QObject::connect(actionClear, SIGNAL(triggered()), MainWindow, SLOT(clearImage()));
        QObject::connect(actionRevert, SIGNAL(triggered()), MainWindow, SLOT(revertImage()));

        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(dropMarble()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), MainWindow, SLOT(clearMarbles()));


        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Marbles!", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "&New", nullptr));
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("MainWindow", "&Open...", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MainWindow", "&Save...", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionQuit->setText(QCoreApplication::translate("MainWindow", "&Quit", nullptr));
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRevert->setText(QCoreApplication::translate("MainWindow", "&Revert Image", nullptr));
#if QT_CONFIG(shortcut)
        actionRevert->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopy3Dto2D->setText(QCoreApplication::translate("MainWindow", "Copy &3D tab to 2D tab", nullptr));
        actionClear->setText(QCoreApplication::translate("MainWindow", "&Clear Image", nullptr));
#if QT_CONFIG(tooltip)
        actionClear->setToolTip(QCoreApplication::translate("MainWindow", "Clear Image", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionClear->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionUseOrbitingCamera->setText(QCoreApplication::translate("MainWindow", "&Use Orbiting Camera", nullptr));
#if QT_CONFIG(shortcut)
        actionUseOrbitingCamera->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+B", nullptr));
#endif // QT_CONFIG(shortcut)
        tabWidget->setTabText(tabWidget->indexOf(tab2D), QCoreApplication::translate("MainWindow", "2D", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab3D), QCoreApplication::translate("MainWindow", "3D", nullptr));
        marbleDock->setWindowTitle(QCoreApplication::translate("MainWindow", "Br&ush", nullptr));
        marbleType->setTitle(QCoreApplication::translate("MainWindow", "Marble Type", nullptr));
        marbleTypeMetal->setText(QCoreApplication::translate("MainWindow", "Metal", nullptr));
        marbleTypeGlass->setText(QCoreApplication::translate("MainWindow", "Glass", nullptr));
        marbleTypeWood->setText(QCoreApplication::translate("MainWindow", "Wood", nullptr));
        marbleTypeJelly->setText(QCoreApplication::translate("MainWindow", "Jelly", nullptr));
        marbleTypeRubber->setText(QCoreApplication::translate("MainWindow", "Rubber", nullptr));
        marbleGravityLabel->setText(QCoreApplication::translate("MainWindow", "Gravity", nullptr));
        marbleGravityTextbox->setText(QString());
        marbleRadiusLabel->setText(QCoreApplication::translate("MainWindow", "Radius", nullptr));
        marbleRadiusTextbox->setText(QString());
        marbleWeightLabel->setText(QCoreApplication::translate("MainWindow", "Weight", nullptr));
        marbleWeightTextbox->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Drop a Marble!", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Clear Marbles", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        menuToolbars->setTitle(QCoreApplication::translate("MainWindow", "&Toolbars", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
