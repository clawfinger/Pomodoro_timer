#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showTrayIcon();
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
