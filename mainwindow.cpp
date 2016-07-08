#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //timer = new QTimer(this);
    showTrayIcon();
    setTrayMenuActions();
    //connect(timer, SIGNAL(timeout()), this, SLOT(timerFinished()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(startTimer()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(hide()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showTrayIcon(){
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/images/tomato.ico");
    trayIcon -> setIcon(trayImage);
    trayIcon->setToolTip("Get back to work!");
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
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

void MainWindow::changeEvent(QEvent *event){
    if(event->type() == QEvent::WindowStateChange)
    {
        event->ignore();
        this->hide();
    }
}

void MainWindow::closeEvent(QCloseEvent *event){
    this->hide();
    event->ignore();
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason){
    if(reason == QSystemTrayIcon::DoubleClick || reason == QSystemTrayIcon::Trigger)
        trayActionExecute();
}

void MainWindow::startTimer()
{
    int time = ui->workTimeInput->value();
    QTimer::singleShot(time*1000, this, SLOT(timerFinished()));
    this->hide();

}
void MainWindow::timerFinished()
{
    trayIcon->showMessage("Timeout", "Timer is finished");
}
