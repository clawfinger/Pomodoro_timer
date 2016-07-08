#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timerMode = workTimer;
    showTrayIcon();
    setTrayMenuActions();
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(startTimer()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(hide()));
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(trayIconMessageClicked()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timerFinished()));
    notificationSound = new QSound(":/Sound/arpeggio.wav", this);
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
    stopTimerAction = new QAction("Stop timer", this);
    trayIconMenu = new QMenu(this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(stopTimerAction, SIGNAL(triggered()), this, SLOT(stopTimer()));
    trayIconMenu->addAction(stopTimerAction);
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
    int workTime = ui->workTimeInput->value()*MINS_TO_MS;
    int funTime = ui->funTimeInput->value()*MINS_TO_MS;
    if(timerMode == workTimer)
    {
        timer->setInterval(workTime);
        timer->setSingleShot(true);
        timer->start();
        //QTimer::singleShot((workTime), this, SLOT(timerFinished()));
        this->hide();
    }
    else if(timerMode == funTimer)
    {
        timer->setInterval(funTime);
        timer->setSingleShot(true);
        timer->start();
        //QTimer::singleShot(funTime, this, SLOT(timerFinished()));
        this->hide();
    }

}

void MainWindow::timerFinished()
{
    notificationSound->play();
    if(timerMode == workTimer)
    {
        trayIconPopupMessage = "Timer is finished. Click the message to start Fun timer";
    }
    else if(timerMode == funTimer)
    {
        trayIconPopupMessage = "Timer is finished. Click the message to start Work timer";
    }
    trayIcon->showMessage("Timeout", trayIconPopupMessage);
}


 void MainWindow::trayIconMessageClicked()
 {
     if(timerMode == workTimer)
     {
         timerMode = funTimer;
         startTimer();
     }
     else if(timerMode == funTimer)
     {
         timerMode = workTimer;
         startTimer();
     }
 }

 void MainWindow::stopTimer()
 {
     timer->stop();
     trayIcon->showMessage("Timer stopped", "Reset in main window");
 }
