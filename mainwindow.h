#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>


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
private slots:
    void trayActionExecute();
    void showTrayIcon();
    void setTrayMenuActions();
};

#endif // MAINWINDOW_H
