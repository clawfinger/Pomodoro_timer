#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showTrayIcon();
    setTrayMenuActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showTrayIcon(){
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/images/tomato.ico");
    trayIcon -> setIcon(trayImage);
    //trayIcon -> setContextMenu(trayIconMenu);
    trayIcon -> show();
}

void MainWindow::trayActionExecute(){
    this->show();
}

void MainWindow::setTrayMenuActions(){
    quitAction = new QAction("Exit", this);
    restoreAction = new QAction("Restore", this);
    trayIconMenu = new QMenu(this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);
}
