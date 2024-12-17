#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    storeImage();
    bdobusObj = new bdobus(ui->frmMain);
    bbatObj = new BBAT(ui->frmMain);
    bdobusObj->hide();
    bbatObj->hide();





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::storeImage()
{
    QPixmap pixNext(":/images/R.png");
    ui->btnShutDown->setIcon(pixNext);
}

void MainWindow::defaultFooterBtnStyleSheet()
{
    setFooterBtnStyleSheet(ui->pbBDOBUS,0);
    setFooterBtnStyleSheet(ui->pbBDOBUS,0);
}

void MainWindow::setFooterBtnStyleSheet(QPushButton *footerBtn, bool setReset)
{
    if(setReset)
    {
        footerBtn->setStyleSheet(GREEN_BUTTON_STYLESHEET);
    }
    else
    {
        footerBtn->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
    }
}












void MainWindow::on_btnShutDown_clicked()
{
    this->close();
}

void MainWindow::on_pbBBAT_clicked()
{
    bdobusObj->hide();
    bbatObj->show();
    defaultFooterBtnStyleSheet();
    setFooterBtnStyleSheet(ui->pbBBAT,1);
}



void MainWindow::on_pbBDOBUS_clicked()
{
    bdobusObj->show();
    bbatObj->hide();
    defaultFooterBtnStyleSheet();
    setFooterBtnStyleSheet(ui->pbBDOBUS,1);
}
