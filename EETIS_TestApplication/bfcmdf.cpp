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
    connect(displayUPdata, SIGNAL(timeout()),this, SLOT(startTest()));
    displayUPdata->start(100);
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

void bfcmdf::startTest()
{
    processHarnessDiDO();
    //qDebug("mainAppWin->startSendData = %d",mainAppWin->startSendData);
    //qDebug()<<"mainAppWin->unitStatus = "<<mainAppWin->unitStatus;
    if(mainAppWin->startSendData == 1 && mainAppWin->unitStatus == 3)
    {
        //processContinutyProcess();
        //mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bfcmdfDoval);
    }
}

void bfcmdf::processHarnessDiDO()
{
    if(ui->ckHarnessForceDoOn->isChecked() == 1)
    {
        mainAppWin->modbusCommObj->setRegisterHIgh(HARNESS_BFCMD_CHK_DO1, 1,bfcmdfDoval);
        qDebug()<<"bfcmdfDoval 0 : "<<bfcmdfDoval[0];
        qDebug()<<"bfcmdfDoval 1 : "<<bfcmdfDoval[1];
        qDebug()<<"bfcmdfDoval 2 : "<<bfcmdfDoval[2];
        qDebug()<<"bfcmdfDoval 3 : "<<bfcmdfDoval[3];
        ui->lblHarnessLED->setStyleSheet(YELLOW_DO_STYLESHEET);
    }
    else if(ui->ckHarnessForceDoOff->isChecked() == 1)
    {
        mainAppWin->modbusCommObj->setRegisterHIgh(HARNESS_BFCMD_CHK_DO1, 0, bfcmdfDoval);
        ui->lblHarnessLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
    }
    else
    {
        if(checkCorrectHarness() == 1 )
        {
            ui->lblHarness->setStyleSheet(GREEN_BUTTON_STYLESHEET);
            if(ui->ckHarnessContinutyError->isChecked() == 1)
            {
                mainAppWin->modbusCommObj->setRegisterHIgh(HARNESS_BFCMD_CHK_DO1, 0, bfcmdfDoval);
                ui->lblHarnessLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
            }
            else
            {
                mainAppWin->modbusCommObj->setRegisterHIgh(HARNESS_BFCMD_CHK_DO1, 1, bfcmdfDoval);
                ui->lblHarnessLED->setStyleSheet(DO_GREEN_STYLESHEET);
            }
        }
        else
        {
            qDebug()<<"else bfcmdfDoval 0 : "<<bfcmdfDoval[0];
            qDebug()<<"else bfcmdfDoval 1 : "<<bfcmdfDoval[1];
            qDebug()<<"else bfcmdfDoval 2 : "<<bfcmdfDoval[2];
            qDebug()<<"else bfcmdfDoval 3 : "<<bfcmdfDoval[3];
            ui->lblHarness->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
            mainAppWin->modbusCommObj->setRegisterHIgh(HARNESS_BFCMD_CHK_DO1, 0, bfcmdfDoval);
            ui->lblHarnessLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
    }
    mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bfcmdfDoval);

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
