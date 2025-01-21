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
    connect(displayUPdata, SIGNAL(timeout()),this, SLOT(update()));
    displayUPdata->start(100);
}

rfu::~rfu()
{
    delete ui;
}

void rfu::update()
{
    rfuDidataList.clear();

    for(int i =0; i< diRfuList.count(); i++)
    {
        rfuDiResultStruct.Result = mainAppWin->modbusCommObj->getDiValue(diRfuList.at(i).diNum);
        rfuDidataList.append(rfuDiResultStruct);
    }
    //qDebug()<<"rfuDidataList.at(0).Result = "<<rfuDidataList.at(0).Result;
    //qDebug()<<"rfuDidataList.at(1).Result = "<<rfuDidataList.at(1).Result;
    //qDebug()<<"rfuDidataList.at(2).Result = "<<rfuDidataList.at(2).Result;
    processHarnessDiDO();
    processDiDo();
    if(mainAppWin->startSendData == 1 && mainAppWin->unitStatus == 4)
    {
        //processContinutyProcess();
        mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, rfuDoval);
        qDebug()<<"done";
    }
}

int rfu::checkCorrectHarness()
{
    int value1= mainAppWin->modbusCommObj->getDiValue(HARNESS_RFU_CHK_DI1);
    return (value1);
}

void rfu::processHarnessDiDO()
{
    if(checkCorrectHarness() == 1 && ui->ckHarnessContinutyError->isChecked() != 1)
    {
        setRegisterHIgh(HARNESS_RFU_CHK_DO1, 1);
        //rfuDoval[1]  = mainAppWin->modbusCommObj->setBitHigh(rfuDoval[1],(HARNESS_RFU_CHK_DO1),1);
//        qDebug()<<"rfuDoval[1] = "<<rfuDoval[1];
        ui->lblHarness->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        ui->lblHarnessLED->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
    }
    else if(checkCorrectHarness() == 1 && ui->ckHarnessContinutyError->isChecked() == 1)
    {
        setRegisterHIgh(HARNESS_RFU_CHK_DO1, 0);
        //rfuDoval[0]  = mainAppWin->modbusCommObj->setBitHigh(rfuDoval[0],(HARNESS_RFU_CHK_DO1),0);
        ui->lblHarness->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        ui->lblHarnessLED->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
    }
}

void rfu::processDiDo()
{
    for(int i = 0; i< rfuDidataList.count();i++)
    {
        if(rfuDidataList.at(i).Result == 1 && crossContinutyErrorList.at(i)->isChecked() == 1)
        {
            setRegisterHIgh(doRfuList.at(i).doNum, 1);
            doLabelList[i]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
            if(i == 0)
            {
               setRegisterHIgh(doRfuList.at(i + 1).doNum, 1);
               doLabelList[i + 1]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
               setRegisterHIgh(doRfuList.at(i + 2).doNum, 1);
               doLabelList[i + 2]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
            }
            else if(i = 1)
            {
                setRegisterHIgh(doRfuList.at(i + 2).doNum, 1);
                doLabelList[i + 2]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
                setRegisterHIgh(doRfuList.at(0).doNum, 1);
                doLabelList[0]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
            }
            else if(i == 2)
            {
                setRegisterHIgh(doRfuList.at(0).doNum, 1);
                doLabelList[0]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
                setRegisterHIgh(doRfuList.at(1).doNum, 1);
                doLabelList[1]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
            }
            diLabelList[i]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        }
        if(rfuDidataList.at(i).Result == 1 && continutyErrorList.at(i)->isChecked() == 1)
        {
            setRegisterHIgh(doRfuList.at(i).doNum, 0);
            doLabelList[i]->setStyleSheet("QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}");
            diLabelList[i]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        }
        if(rfuDidataList.at(i).Result == 1  && crossContinutyErrorList.at(i)->isChecked() != 1 && continutyErrorList.at(i)->isChecked() != 1)
        {
            setRegisterHIgh(doRfuList.at(i).doNum, 1);
            doLabelList[i]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
            diLabelList[i]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
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
    rfuDistruct.diNum = RFUDI1;
    diRfuList.append(rfuDistruct);
    rfuDistruct.diNum = RFUDI2;
    diRfuList.append(rfuDistruct);
    rfuDistruct.diNum = RFUDI3;
    diRfuList.append(rfuDistruct);
}

void rfu::addDoStructInList()
{
    doRfuList.clear();
    rfuDostruct.doNum = RFUDO1;
    doRfuList.append(rfuDostruct);
    rfuDostruct.doNum = RFUDO2;
    doRfuList.append(rfuDostruct);
    rfuDostruct.doNum = RFUDO3;
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
}

void rfu::doListappend()
{
    doLabelList.clear();
    doLabelList.append(ui->lblFireLED);
    doLabelList.append(ui->lblBreechOpeningLED);
    doLabelList.append(ui->lblBreechClosingLED);
}

void rfu::diListappend()
{
    diLabelList.clear();
    diLabelList.append(ui->lblFIre);
    diLabelList.append(ui->lblBreechOpening);
    diLabelList.append(ui->lblBreechClosing);
}

void rfu::continutyErrorListappend()
{
    continutyErrorList.clear();
    continutyErrorList.append(ui->ckContinutyFire);
    continutyErrorList.append(ui->ckContinutyBreechOpening);
    continutyErrorList.append(ui->ckContinutyBrechClosing);
}

void rfu::crossContinutyErrorListappend()
{
    crossContinutyErrorList.clear();
    crossContinutyErrorList.append(ui->ckCrossContinutyFire);
    crossContinutyErrorList.append(ui->ckCrossContinutyBreechOpening);
    crossContinutyErrorList.append(ui->ckCrossContinutyBreechClosing);
}
