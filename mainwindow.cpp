#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_timer = new QTimer(this);
    m_timerMode = workTimer;

    showTrayIcon();
    setTrayMenuActions();

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(startTimer()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(hide()));

    connect(m_trayIcon, SIGNAL(messageClicked()), this, SLOT(trayIconMessageClicked()));

    connect(m_timer, SIGNAL(timeout()), this, SLOT(timerFinished()));

    m_notificationSound = new QSound(":/Sound/arpeggio.wav", this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showTrayIcon(){           //setting up a tray icon
    m_trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/images/tomato.ico");
    m_trayIcon -> setIcon(trayImage);
    m_trayIcon->setToolTip("Get back to work!");
    connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    m_trayIcon -> show();
}

void MainWindow::trayActionExecute(){

    this->show();
}

void MainWindow::setTrayMenuActions(){
    m_quitAction = new QAction("Exit", this);

    m_stopTimerAction = new QAction("Stop timer", this);
    m_startWorkTimer = new QAction("Start Work", this);
    m_startFunTimer = new QAction("Start Fun", this);

    m_trayIconMenu = new QMenu(this);

    m_trayIconMenu->addAction(m_startWorkTimer);
    m_trayIconMenu->addAction(m_startFunTimer);
    m_trayIconMenu->addAction(m_stopTimerAction);
    m_trayIconMenu->addAction(m_quitAction);
    m_trayIcon->setContextMenu(m_trayIconMenu);

    connect(m_quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(m_stopTimerAction, SIGNAL(triggered()), this, SLOT(stopTimer()));
    connect(m_startWorkTimer, SIGNAL(triggered()), this, SLOT(startWorkTimer()));
    connect(m_startFunTimer, SIGNAL(triggered()), this, SLOT(startFunTimer()));
}

void MainWindow::changeEvent(QEvent *event){            //minimising and closing app window hides it to tray
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

        m_stopTimerAction->setEnabled(true);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled( false );

        ui->workTimeInput->setEnabled(false);
        ui->funTimeInput->setEnabled(false);

        int workTime = ui->workTimeInput->value()*MINS_TO_MS;
        int funTime = ui->funTimeInput->value()*MINS_TO_MS;
        if(m_timerMode == workTimer)
        {
            m_timer->setInterval(workTime);
            m_timer->setSingleShot(true);
            m_timer->start();
            //QTimer::singleShot((workTime), this, SLOT(timerFinished()));
            this->hide();
            m_trayIcon->showMessage("Work timer", "Started work timer");
        }
        else if(m_timerMode == funTimer)
        {
            m_timer->setInterval(funTime);
            m_timer->setSingleShot(true);
            m_timer->start();
            //QTimer::singleShot(funTime, this, SLOT(timerFinished()));
            this->hide();
            m_trayIcon->showMessage("Fun timer", "Started fun timer");
        }


}

void MainWindow::timerFinished()
{
    m_notificationSound->play();
    if(m_timerMode == workTimer)
    {
        m_trayIconPopupMessage = "Timer is finished. Click the message to start Fun timer";
    }
    else if(m_timerMode == funTimer)
    {
        m_trayIconPopupMessage = "Timer is finished. Click the message to start Work timer";
    }
    m_trayIcon->showMessage("Timeout", m_trayIconPopupMessage);
}


 void MainWindow::trayIconMessageClicked()
 {
     if(!m_timer->isActive())
     {
         if(m_timerMode == workTimer)
         {
             m_timerMode = funTimer;
             startTimer();

         }
         else if(m_timerMode == funTimer)
         {
             m_timerMode = workTimer;
             startTimer();
         }
     }
 }

 void MainWindow::stopTimer()
 {
     m_timer->stop();
     m_stopTimerAction->setEnabled(false);
     ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled( true );
     ui->workTimeInput->setEnabled(true);
     ui->funTimeInput->setEnabled(true);
     //trayIcon->showMessage("Timer stopped", "Reset in main window");
     this->show();
 }

 void MainWindow::startWorkTimer()
 {
     if(!m_timer->isActive())
     {
         m_timerMode = workTimer;
         startTimer();
         m_trayIcon->showMessage("Work timer", "Started work timer");
     }
 }

 void MainWindow::startFunTimer()
 {
     if(!m_timer->isActive())
     {
         m_timerMode = funTimer;
         startTimer();
         m_trayIcon->showMessage("Fun timer", "Started fun timer");
     }
 }
