#include "bfcmdf.h"
#include "ui_bfcmdf.h"
#include "mainwindow.h"

extern MainWindow *mainAppWin;
bfcmdf::bfcmdf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bfcmdf)
{
    ui->setupUi(this);
    displayUPdata = new QTimer(this);
    connect(displayUPdata, SIGNAL(timeout()),this, SLOT(update()));
    //displayUPdata->start(100);
}

bfcmdf::~bfcmdf()
{
    delete ui;
}

int bfcmdf::checkCorrectHarness()
{
    int value1= mainAppWin->modbusCommObj->getDiValue(HARNESS_BFCMD_CHK_DI1);
    //qDebug("value1 = %d",value1);

    // plcCommObj->setDoValue(HARNESS_BDOBUS_CHK_DO1,LOW);
    return (value1);
}

void bfcmdf::update()
{
    processHarnessDiDO();
    //qDebug("mainAppWin->startSendData = %d",mainAppWin->startSendData);
    //qDebug()<<"mainAppWin->unitStatus = "<<mainAppWin->unitStatus;
    if(mainAppWin->startSendData == 1 && mainAppWin->unitStatus == 3)
    {
        processContinutyProcess();
        mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bfcmdfDoval);
    }
}

void bfcmdf::processHarnessDiDO()
{
    if(checkCorrectHarness() == 1 && ui->ckHarnessContinutyError->isChecked() != 1)
    {
        // memset(&modbusCommObj->dival[0], 0 , sizeof(modbusCommObj->dival));
        bfcmdfDoval[0]  = mainAppWin->modbusCommObj->setBitHigh(bfcmdfDoval[0],(HARNESS_BFCMD_CHK_DO1),1);
        //qDebug("bfcmdfDoval[0] = %d",bfcmdfDoval[0]);
        ui->lblHarness->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        ui->lblHarnessLED->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
    }
    else if(checkCorrectHarness() == 1 && ui->ckHarnessContinutyError->isChecked() == 1)
    {
        //memset(&modbusCommObj->dival[0], 0 , sizeof(modbusCommObj->dival));
        bfcmdfDoval[0]  = mainAppWin->modbusCommObj->setBitHigh(bfcmdfDoval[0],(HARNESS_BFCMD_CHK_DO1),0);
        ui->lblHarness->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        ui->lblHarnessLED->setStyleSheet("QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}");
    }

}

void bfcmdf::processContinutyProcess()
{
    if(ui->ckContinutyJ1_11toJ1_12->isChecked() != 1)
    {
        bfcmdfDoval[0]  = mainAppWin->modbusCommObj->setBitHigh(bfcmdfDoval[0],(BFCMDFDO1),1);
        ui->lblJ1_11TOj1_12LED->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
    }
    else if(ui->ckContinutyJ1_11toJ1_12->isChecked() == 1)
    {
        bfcmdfDoval[0]  = mainAppWin->modbusCommObj->setBitHigh(bfcmdfDoval[0],(BFCMDFDO1),0);
        ui->lblJ1_11TOj1_12LED->setStyleSheet("QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}");
    }

}
