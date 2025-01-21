#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include "modbuscomm.h"
#include "bdobus.h"
#include "bbat.h"
#include "bfcmdf.h"
#include "rfu.h"
#include <QDateTime>


#define SET_BUTTON_STYLESHEET  "background: rgb(203, 155, 52); color: rgb(255, 255, 255);\
border-bottom-right-radius:00px;\
border-top-right-radius:00px;\
border-bottom-left-radius:10px;\
border-top-left-radius:10px;"


#define DEFAULT_FOOTER_BUTTON_STYLESHEET "background-color: rgb(53, 74, 131); color: rgb(255, 255, 255);\
border-bottom-right-radius:00px;\
border-top-right-radius:00px;\
border-bottom-left-radius:0px;\
border-top-left-radius:00px;"

#define BBATUNIT        1
#define BDOBUSUNIT      2
#define BFCMDFUNIT      3
#define RFUUNIT         4

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
    int unitStatus = 0;
    modbusComm *modbusCommObj;
    char startSendData = 0;
protected:
    void defaultFooterBtnStyleSheet();
    void setFooterBtnStyleSheet(QPushButton *footerBtn, bool setReset);
    void hideAllFrms();
private slots:

    void on_btnShutDown_clicked();

    void on_pbBBAT_clicked();

    void on_pbBDOBUS_clicked();

    void on_pbBfcmdf_clicked();

    void on_pbRfu_clicked();
    void updateDateTime();
    void checkIfClientIsConnected();

private:
    Ui::MainWindow *ui;

    bdobus *bdobusObj;
    BBAT *bbatObj;
    bfcmdf *bfcmdfObj;
    rfu *rfuObj;
    quint16 di[8];
    QTimer *updateDateTimeTimer;
    QTimer *commCheckTimer;

};

#endif // MAINWINDOW_H
