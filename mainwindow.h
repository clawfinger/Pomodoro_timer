#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QTimer>
#include <QSound>
#include <QPushButton>
#define MINS_TO_MS 60000
enum timerModeEnum {workTimer, funTimer};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *m_trayIcon;
    QMenu* m_trayIconMenu;
    QAction* m_quitAction;
    QAction* m_stopTimerAction;
    QAction* m_startWorkTimer;
    QAction* m_startFunTimer;
    timerModeEnum m_timerMode;
    QString m_trayIconPopupMessage;
    QSound* m_notificationSound;
    QTimer* m_timer;
private slots:
    void trayActionExecute();
    void showTrayIcon();
    void setTrayMenuActions();
    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);
    void trayIconActivated(QSystemTrayIcon::ActivationReason);
    void startTimer();
    void timerFinished();
    void trayIconMessageClicked();
    void stopTimer();
    void startWorkTimer();
    void startFunTimer();
};

#endif // MAINWINDOW_H
