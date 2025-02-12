#include "rfu.h"
#include "mainwindow.h"
#include "ui_rfu.h"

extern MainWindow *mainAppWin;
rfu::rfu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rfu)
{
    ui->setupUi(this);
    addDiDoStructInList();
    uiListappend();
    displayUPdata = new QTimer(this);
    connect(displayUPdata, SIGNAL(timeout()),this, SLOT(startTest()));
    //displayUPdata->start(100);
}

rfu::~rfu()
{
    delete ui;
}

void rfu::startTest()
{
    rfuDidataList.clear();

    for(int i =0; i< diRfuList.count(); i++)
    {
        rfuDiResultStruct.Result = mainAppWin->modbusCommObj->getDiValue(diRfuList.at(i).diNum);
        rfuDidataList.append(rfuDiResultStruct);
    }
    processHarnessDiDO();
    processDiDo();
    if(mainAppWin->startSendData == 1 && mainAppWin->unitStatus == 4)
    {
        //processContinutyProcess();
        mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, rfuDoval);
        //qDebug()<<"done";
    }
}

int rfu::checkCorrectHarness()
{
    int value1= mainAppWin->modbusCommObj->getDiValue(HARNESS_RFU_CHK_DI);
    return (value1);
}

void rfu::processHarnessDiDO()
{
    if(ui->cbHarness_On->isChecked() == 1)
    {
        setRegisterHIgh(HARNESS_RFU_CHK_DO, 1);
        ui->lblHarnessLED->setStyleSheet(YELLOW_DO_STYLESHEET);
    }
    else if(ui->cbHarness_Off->isChecked() == 1)
    {
        ui->lblHarnessLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
    }
    else
    {
        if(checkCorrectHarness() == 1 )
        {
            ui->lblHarness->setStyleSheet(GREEN_BUTTON_STYLESHEET);
            if(ui->ckHarnessContinutyError->isChecked() == 1)
            {
                setRegisterHIgh(HARNESS_RFU_CHK_DO, 0);
                ui->lblHarnessLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
            }
            else
            {
                setRegisterHIgh(HARNESS_RFU_CHK_DO, 1);
                ui->lblHarnessLED->setStyleSheet(DO_GREEN_STYLESHEET);
            }
        }
        else
        {
            ui->lblHarness->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
            setRegisterHIgh(HARNESS_RFU_CHK_DO, 0);
            ui->lblHarnessLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
    }
}

void rfu::processDiDo()
{
    for(int i = 0; i< rfuDidataList.count();i++)
    {
        if(forceDoOnList.at(i)->isChecked() == 1)
        {
            setRegisterHIgh(doRfuList.at(i).doNum, 1);
            doLabelList.at(i)->setStyleSheet(YELLOW_DO_STYLESHEET);
        }
        else if(forceDoOffList.at(i)->isChecked() == 1)
        {
            setRegisterHIgh(doRfuList.at(i).doNum, 0);
            doLabelList.at(i)->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
        else
        {
            if(rfuDidataList.at(i).Result == 1)
            {
                diLabelList.at(i)->setStyleSheet(GREEN_BUTTON_STYLESHEET);
                if(continutyErrorList.at(i)->isChecked() == 1)
                {
                    setRegisterHIgh(doRfuList.at(i).doNum, 0);
                    doLabelList.at(i)->setStyleSheet(DEFAULT_DO_STYLESHEET);
                }
                else
                {
                    setRegisterHIgh(doRfuList.at(i).doNum, 1);
                    doLabelList[i]->setStyleSheet(DO_GREEN_STYLESHEET);
                }
            }
            else
            {
                setRegisterHIgh(doRfuList.at(i).doNum, 0);
                doLabelList.at(i)->setStyleSheet(DEFAULT_DO_STYLESHEET);
                diLabelList.at(i)->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
            }
        }
    }
}


void rfu::setRegisterHIgh(int bitPosition, bool highLow)
{
    if(bitPosition > 0 && bitPosition < 16)
    {
        rfuDoval[0] = mainAppWin->modbusCommObj->setBitHigh(rfuDoval[0],bitPosition,highLow);
    }
    else if(bitPosition  >= 16 && bitPosition  <32)
    {
        rfuDoval[1] = mainAppWin->modbusCommObj->setBitHigh(rfuDoval[1],(bitPosition - 16),highLow);
    }
    else if(bitPosition  >= 32 && bitPosition  <48)
    {
        rfuDoval[2] = mainAppWin->modbusCommObj->setBitHigh(rfuDoval[2],(bitPosition - 32),highLow);
    }
    else if(bitPosition  >= 48 && bitPosition  <64)
    {
        rfuDoval[3] = mainAppWin->modbusCommObj->setBitHigh(rfuDoval[3],(bitPosition - 48),highLow);
    }
}

void rfu::addDiStructInList()
{
    diRfuList.clear();
    rfuDistruct.diNum = RFU_BREECHCLOSING_DI1;
    diRfuList.append(rfuDistruct);
    rfuDistruct.diNum = RFU_BREECHCLOSING_DI2;
    diRfuList.append(rfuDistruct);
    rfuDistruct.diNum = RFU_FIRE_DI1;
    diRfuList.append(rfuDistruct);
    rfuDistruct.diNum = RFU_FIRE_DI2;
    diRfuList.append(rfuDistruct);
    rfuDistruct.diNum = RFU_BREECHLOADING_DI;
    diRfuList.append(rfuDistruct);
}

void rfu::addDoStructInList()
{
    doRfuList.clear();
    rfuDostruct.doNum = RFU_BREECHCLOSING_DO1;
    doRfuList.append(rfuDostruct);
    rfuDostruct.doNum = RFU_BREECHCLOSING_DO2;
    doRfuList.append(rfuDostruct);
    rfuDostruct.doNum = RFU_FIRE_DO1;
    doRfuList.append(rfuDostruct);
    rfuDostruct.doNum = RFU_FIRE_DO2;
    doRfuList.append(rfuDostruct);
    rfuDostruct.doNum = RFU_BREECHLOADING_DO;
    doRfuList.append(rfuDostruct);
}

void rfu::addDiDoStructInList()
{
    addDiStructInList();
    addDoStructInList();
}

void rfu::uiListappend()
{
    diListappend();
    doListappend();
    continutyErrorListappend();
    crossContinutyErrorListappend();
    ckForceDoOnListAppend();
    ckForceDoOffListAppend();
}

void rfu::doListappend()
{
    doLabelList.clear();
    doLabelList.append(ui->lblBreechClosing1LED);
    doLabelList.append(ui->lblBreechClosing2LED);
    doLabelList.append(ui->lblFire1LED);
    doLabelList.append(ui->lblFire2LED);
    doLabelList.append(ui->lblBreechOpeningLED);

}

void rfu::diListappend()
{
    diLabelList.clear();
    diLabelList.append(ui->lblBreechClosing1);
    diLabelList.append(ui->lblBreechClosing2);
    diLabelList.append(ui->lblFire1);
    diLabelList.append(ui->lblFire2);
    diLabelList.append(ui->lblBreechOpening);

}

void rfu::continutyErrorListappend()
{
    continutyErrorList.clear();
    continutyErrorList.append(ui->ckContinutyBrechClosing1);
    continutyErrorList.append(ui->ckContinutyBrechClosing2);
    continutyErrorList.append(ui->ckContinutyFire1);
    continutyErrorList.append(ui->ckContinutyFire2);
    continutyErrorList.append(ui->ckContinutyBreechOpening);

}

void rfu::crossContinutyErrorListappend()
{
    crossContinutyErrorList.clear();
    crossContinutyErrorList.append(ui->ckCrossContinutyBreechClosing1);
    crossContinutyErrorList.append(ui->ckCrossContinutyBreechClosing2);
    crossContinutyErrorList.append(ui->ckCrossContinutyFire1);
    crossContinutyErrorList.append(ui->ckCrossContinutyFire2);
    crossContinutyErrorList.append(ui->ckCrossContinutyBreechOpening);

}

void rfu::ckForceDoOnListAppend()
{
    forceDoOnList.clear();
    forceDoOnList.append(ui->cbBreechClosing1_On);
    forceDoOnList.append(ui->cbBreechClosing2_On);
    forceDoOnList.append(ui->cbFire1_On);
    forceDoOnList.append(ui->cbFire2_On);
    forceDoOnList.append(ui->cbBreechLoading_On);
}

void rfu::ckForceDoOffListAppend()
{
    forceDoOffList.clear();
    forceDoOffList.append(ui->cbBreechClosing1_Off);
    forceDoOffList.append(ui->cbBreechClosing2_Off);
    forceDoOffList.append(ui->cbFire1_Off);
    forceDoOffList.append(ui->cbFire2_Off);
    forceDoOffList.append(ui->cbBreechLoading_Off);
}
