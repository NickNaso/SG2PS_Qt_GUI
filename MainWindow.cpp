// Copyright (C) 2012, Ali Baharev
// All rights reserved.
// This code is published under the GNU Lesser General Public License.
#include <QMessageBox>
#include <QDir>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QDebug>
#include "MainWindow.hpp"
#include "InputWidget.hpp"
#include "Launcher.hpp"
#include "Runner.hpp"
#include "SettingsWidget.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QString::fromWCharArray(L"SG2PS — Structural Geology to PostScript Qt Frontend"));

    set_menu();

    add_elements();

    connect_signal_slots();
}

void MainWindow::connect_signal_slots() {

    connect(inputWidget, SIGNAL(inputFileSelected(QString)), runner, SLOT(inputFileSelected(QString)));

    connect(inputWidget, SIGNAL(inputFileSelected(QString)), settingsWidget, SLOT(tryLoadSettings(QString)));
}

void MainWindow::add_elements() {

    QWidget* centralWidget = new QWidget(this);

    mainLayout = new QVBoxLayout;



    inputWidget = new InputWidget(this);

    mainLayout->addWidget(inputWidget);



    settingsWidget = new SettingsWidget(this);

    mainLayout->addWidget(settingsWidget);


    runner = new Runner(this);

    mainLayout->addWidget(runner);



    mainLayout->addStretch(1);

    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
}

void MainWindow::fixSize() {

    setFixedSize(width(), height());

    inputWidget->freezeLabelSize();

    qDebug() << "Size: " << width() << "x" << height();
}

void MainWindow::set_menu() {

    QAction *showAbout = new QAction("About", this);

    connect(showAbout, SIGNAL(triggered()), SLOT(about()));


    QAction *editSettings = new QAction("Preferences", this);

    connect(editSettings, SIGNAL(triggered()), SLOT(editGUISettings()));


    QAction *manual = new QAction("Manual", this);

    connect(manual, SIGNAL(triggered()), SLOT(showManual()));


    QAction *homepage = new QAction("Jump to the homepage", this);

    connect(homepage, SIGNAL(triggered()), SLOT(showHomepage()));


    QMenu* settingsMenu = menuBar()->addMenu("Settings");

    settingsMenu->addAction(editSettings);


    QMenu* help = menuBar()->addMenu("Help");

    help->addAction(manual);

    help->addAction(homepage);

    help->addAction(showAbout);
}

void MainWindow::about() {

    QMessageBox::about(this, "About", QString::fromWCharArray(

                       L"Built on " __DATE__ " at " __TIME__ "\n\n"

                       L"This application is just a graphical front end for the "
                       L"command line application sg2ps, written and maintened by "
                       L"Ágoston Sasvári.\n\n"

                       L"The grapical user interface is written and mainted by Ali Baharev "
                       L"based on Qt " QT_VERSION_STR ".\n\n"

                       L"The program is provided AS IS with NO WARRANTY OF ANY KIND, "
                       L"INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS "
                       L"FOR A PARTICULAR PURPOSE.")
                       );

    qDebug() << "Built on " << __DATE__ << " at " << __TIME__;
}

void MainWindow::editGUISettings() {

    // TODO Reload it automatically instead!
    QMessageBox::information(this, "Reminder", "After editing the options, don\'t forget "
                             "to restart the application!");

    QString path = QDir::currentPath();

    openInTextEditor(path+"/settings.txt");
}

MainWindow::~MainWindow()
{
    
}
