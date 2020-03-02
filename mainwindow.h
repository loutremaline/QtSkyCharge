#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "chargeslot.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void initTimer_timeout();

private:
    Ui::MainWindow *ui;
    ChargeSlot *slot1, *slot2;
    QTimer initTimer;

};
#endif // MAINWINDOW_H
