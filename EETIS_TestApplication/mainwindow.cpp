#include "mainwindow.h"
#include "ui_mainwindow.h"

int showPopupIndex = 0;

#define COMM_TIMEOUT        50


unsigned char eetisConnected = 0;
int commCheckCounter = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    storeImage();
    modbusCommObj = new modbusComm(this);
    bdobusObj = new bdobus(ui->frmMain);
    bbatObj = new BBAT(ui->frmMain);
    bfcmdfObj = new bfcmdf(ui->frmMain);
    rfuObj = new rfu(ui->frmMain);
    stdpObj = new stdp(ui->frmMain);
    bdobusObj->hide();
    bbatObj->hide();
    bfcmdfObj->hide();
    rfuObj->hide();
    stdpObj->hide();

    updateDateTimeTimer = new QTimer(this);
    connect(updateDateTimeTimer, SIGNAL(timeout()), this, SLOT(updateDateTime()));
    updateDateTimeTimer->start(100);

    commCheckTimer = new QTimer(this);
    connect(commCheckTimer, SIGNAL(timeout()), this, SLOT(checkIfClientIsConnected()));
    commCheckTimer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDateTime()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    ui->lblDateTime->setText(currentDateTime.toString("dd-mm-yyyy |") + currentDateTime.toString("hh:mm:ss"));
}

void MainWindow::checkIfClientIsConnected()
{
    if (modbusCommObj->clientSocket->state() != QAbstractSocket::ConnectedState)
    {
//        qDebug() << "Socket is not connected:"<<commCheckCounter;
        commCheckCounter++;
        if(commCheckCounter > COMM_TIMEOUT)
        {
            eetisConnected = 0;
            commCheckCounter = 0;
            ui->lblCommStatus->setStyleSheet("background-color: rgb(255, 0, 0); "
                                             "color:white;"
                                             "border-bottom-right-radius:10px;"
                                             "border-top-left-radius:10px;");
        }
    }
    else
    {
        commCheckCounter= 0;
        eetisConnected = 1;
        ui->lblCommStatus->setStyleSheet("background-color: rgb(73, 202, 66); "
                                         "color:white;"
                                         "border-bottom-right-radius:10px;"
                                         "border-top-left-radius:10px;");
    }
}

void MainWindow::storeImage()
{
    QPixmap pixNext(":/images/R.png");
    ui->btnShutDown->setIcon(pixNext);
}

void MainWindow::defaultFooterBtnStyleSheet()
{
    setFooterBtnStyleSheet(ui->pbBDOBUS,0);
    setFooterBtnStyleSheet(ui->pbBBAT,0);
    setFooterBtnStyleSheet(ui->pbBfcmdf,0);
    setFooterBtnStyleSheet(ui->pbRfu,0);
}

void MainWindow::setFooterBtnStyleSheet(QPushButton *footerBtn, bool setReset)
{
    if(setReset)
    {
        footerBtn->setStyleSheet(SET_BUTTON_STYLESHEET);
    }
    else
    {
        footerBtn->setStyleSheet(DEFAULT_FOOTER_BUTTON_STYLESHEET);
    }
}

void MainWindow::hideAllFrms()
{
    bdobusObj->hide();
    bbatObj->hide();
    bfcmdfObj->hide();
    rfuObj->hide();
    stdpObj->hide();
}

void MainWindow::on_btnShutDown_clicked()
{
    this->close();
}

void MainWindow::on_pbBBAT_clicked()
{
    hideAllFrms();
    bbatObj->show();
    unitStatus = BBATUNIT;
    defaultFooterBtnStyleSheet();
    setFooterBtnStyleSheet(ui->pbBBAT,1);
}

void MainWindow::on_pbBDOBUS_clicked()
{
    hideAllFrms();
    bdobusObj->show();
    unitStatus = BDOBUSUNIT;
    defaultFooterBtnStyleSheet();
    setFooterBtnStyleSheet(ui->pbBDOBUS,1);
}

void MainWindow::on_pbBfcmdf_clicked()
{
    hideAllFrms();
    bfcmdfObj->show();
    unitStatus = BFCMDFUNIT;
    defaultFooterBtnStyleSheet();
    setFooterBtnStyleSheet(ui->pbBfcmdf,1);
}

void MainWindow::on_pbRfu_clicked()
{
    hideAllFrms();
    rfuObj->show();
    unitStatus = RFUUNIT;
    defaultFooterBtnStyleSheet();
    setFooterBtnStyleSheet(ui->pbRfu,1);
}

void MainWindow::on_pbStdp_clicked()
{
    hideAllFrms();
    stdpObj->show();
    unitStatus = RFUUNIT;
    defaultFooterBtnStyleSheet();
    setFooterBtnStyleSheet(ui->pbStdp,1);
}
