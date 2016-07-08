#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QTimer>


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
    QSystemTrayIcon *trayIcon;
    QMenu* trayIconMenu;
    QAction* quitAction;
    QAction* restoreAction;
    //QTimer* timer;
private slots:
    void trayActionExecute();
    void showTrayIcon();
    void setTrayMenuActions();
    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);
    void trayIconActivated(QSystemTrayIcon::ActivationReason);
    void startTimer();
    void timerFinished();
};

#endif // MAINWINDOW_H
