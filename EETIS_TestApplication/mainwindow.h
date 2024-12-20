#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include "modbuscomm.h"
#include "bdobus.h"
#include "bbat.h"


#define GREEN_BUTTON_STYLESHEET  "background: rgb(203, 155, 52); color: rgb(255, 255, 255);\
border-bottom-right-radius:00px;\
border-top-right-radius:00px;\
border-bottom-left-radius:10px;\
border-top-left-radius:10px;"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void storeImage();
protected:
    void defaultFooterBtnStyleSheet();
    void setFooterBtnStyleSheet(QPushButton *footerBtn, bool setReset);
private slots:

    void on_btnShutDown_clicked();

    void on_pbBBAT_clicked();



    void on_pbBDOBUS_clicked();

private:
    Ui::MainWindow *ui;

    bdobus *bdobusObj;
    BBAT *bbatObj;
    quint16 di[8];
};

#endif // MAINWINDOW_H
