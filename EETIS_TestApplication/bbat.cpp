#include "bbat.h"
#include "mainwindow.h"
#include "ui_bbat.h"

extern MainWindow *mainAppWin;
BBAT::BBAT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BBAT)
{
    ui->setupUi(this);
    ui->dbsJ7aToJ7b->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->dbsJ7btoJ7c->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->dbsJ7aToJ7c->setButtonSymbols(QAbstractSpinBox::NoButtons);
    updateUidata = new QTimer(this);
    connect(updateUidata, SIGNAL(timeout()),this, SLOT(update()));
    updateUidata->start(100);
    uiListappend();
    addDiDoStructInList();
}

BBAT::~BBAT()
{
    delete ui;
}

void BBAT::addDoStructInList()
{
    doBBATList.clear();
    //BBATresultList.clear();
    BBATDoStruct.doNum = BBATDO1;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO2;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO3;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO4;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO5;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO6;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO7;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO8;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO9;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO10;
    doBBATList.append(BBATDoStruct);
    //BBATresultList.clear();
    BBATDoStruct.doNum = BBATDO11;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO12;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO13;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO14;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO15;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO16;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO17;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO18;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO19;
    doBBATList.append(BBATDoStruct);
    BBATDoStruct.doNum = BBATDO20;
    doBBATList.append(BBATDoStruct);

    BBATDoStruct1.doNum = BBATDO1_1;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_2;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_3;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_4;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_5;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_6;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_7;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_8;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_9;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_10;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_11;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_12;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_13;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_14;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_15;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_16;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_17;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_18;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_19;
    doBBATList1.append(BBATDoStruct1);
    BBATDoStruct1.doNum = BBATDO1_20;
    doBBATList1.append(BBATDoStruct1);

    BBATPowerOffDoStruct.doNum = BBATDI_POWEROFF21;
    doBBATPowerOffList.append(BBATPowerOffDoStruct);
    BBATPowerOffDoStruct.doNum = BBATDI_POWEROFF22;
    doBBATPowerOffList.append(BBATPowerOffDoStruct);

}

void BBAT::addDiStructInList()
{
    BBATDiStruct.diNum = POWER_ON_DI;
    diBBATList.append(BBATDiStruct);
}

void BBAT::processHarnessDiDO()
{
    //
    if(checkCorrectHarness() == 1 )
    {
        //harnesscount++;
        bbatDoval[0]  = mainAppWin->modbusCommObj->setBitHigh(bbatDoval[0],(HARNESS_BBAT_CHK_DO1),1);
        bbatDoval[0]  = mainAppWin->modbusCommObj->setBitHigh(bbatDoval[0],(HARNESS_BBAT_CHK_DO2),1);
        mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bbatDoval);
        ui->lblHarness->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        ui->lblHarnessLED->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
    }
    else
    {

    }

}

int BBAT::checkCorrectHarness()
{
    int value1= mainAppWin->modbusCommObj->getDiValue(HARNESS_BBAT_CHK_DI1);
    int value2 = mainAppWin->modbusCommObj->getDiValue(HARNESS_BBAT_CHK_DI2);
    return (value1 && value2);
}

void BBAT::processDoVals()
{
    for(int i = 0; i< doBBATList.count(); i++)
    {
        setRegisterHigh(doBBATList.at(i).doNum, 1);
        setRegisterHigh(doBBATList1.at(i).doNum, 1);
        mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bbatDoval);
        doLabelList.at(i)->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
    }
}

void BBAT::uiListappend()
{
    diListappend();
}

void BBAT::diListappend()
{
    doLabelList.clear();
    doLabelList.append(ui->ledj2atoj2d);
    doLabelList.append(ui->ledJ2btoj2e);
    doLabelList.append(ui->ledj2ctoj2f);
    doLabelList.append(ui->ledj2gtoj2k);
    doLabelList.append(ui->ledj2htoj2l);
    doLabelList.append(ui->ledj2jtoj2m);
    doLabelList.append(ui->ledj3atoj3c);
    doLabelList.append(ui->ledj3btoj3d);
    doLabelList.append(ui->lblj4atoj4b);
    doLabelList.append(ui->ledj5atoj5c);
    doLabelList.append(ui->ledj5btoj5d);
    doLabelList.append(ui->ledj5ftoj5g);
    doLabelList.append(ui->ledj5etoj5g);
    doLabelList.append(ui->ledj61toj62);
    doLabelList.append(ui->ledj7atoj7c);
    doLabelList.append(ui->ledj7btoj7d);
    doLabelList.append(ui->ledj8ctoj8d);
    doLabelList.append(ui->ledj8gtoj8h);
    doLabelList.append(ui->ledj8atoj8b);
    doLabelList.append(ui->ledj8etoj8f);
}



void BBAT::addDiDoStructInList()
{
    addDoStructInList();
    addDiStructInList();
}

void BBAT::sendAiData()
{
    bbatAoVal[BBATAO01] = (ui->dbsJ7aToJ7b->value());
    bbatAoVal[BBATAO02] = (ui->dbsJ7btoJ7c->value());
    bbatAoVal[BBATAO03] = (ui->dbsJ7aToJ7c->value());
    mainAppWin->modbusCommObj->sendDoAoData(AI_TRANS_ID,16, bbatAoVal);
}

void BBAT::update()
{
    processHarnessDiDO();
    //mainAppWin->modbusCommObj->dotransactionId = DI_TRANS_ID;
//    BBATDiResultStruct.Result = mainAppWin->modbusCommObj->getDiValue(diBBATList.at(0).diNum);
//    BBATDidataList.append(BBATDiResultStruct);
    int result1 = mainAppWin->modbusCommObj->getDiValue(POWER_ON_DI);
    if(result1 == 1)
    {
        inputCount++;
        ui->lblPowerOn->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        startSendAo = 1;
    }
    if(mainAppWin->startSendData == 1 && mainAppWin->unitStatus == 1 )
    {
        if(result1 == 1)
        {
            processDoVals();
            powerOffDO = 1;
            //modbusCommObj->sendData();
            //mainAppWin->modbusCommObj->sendDiData(bbatDoval);

        }
        else
        {
           sendAiData();
           if(powerOffDO == 1)
           {
               setRegisterHigh(doBBATPowerOffList.at(0).doNum, 1);
               setRegisterHigh(doBBATPowerOffList.at(1).doNum, 1);
           }
           //memset(&bbatDoval[0], 0 , sizeof(bbatDoval));
        }
    mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bbatDoval);
    }
//    else if(mainAppWin->startSendData == 1 && mainAppWin->unitStatus == 1 && result1 != 1 && startSendAo == 1)
//    {

//    }

}

void BBAT::setRegisterHigh(int bitPosition, bool highLow)
{
    if(bitPosition > 0 && bitPosition < 16)
    {
        bbatDoval[0] = mainAppWin->modbusCommObj->setBitHigh(bbatDoval[0],bitPosition,highLow);
    }
    else if(bitPosition  >= 16 && bitPosition  <32)
    {
        bbatDoval[1] = mainAppWin->modbusCommObj->setBitHigh(bbatDoval[1],(bitPosition - 16),highLow);
    }
    else if(bitPosition  >= 32 && bitPosition  <48)
    {
        bbatDoval[2] = mainAppWin->modbusCommObj->setBitHigh(bbatDoval[2],(bitPosition - 32),highLow);
    }
    else if(bitPosition  >= 48 && bitPosition  <64)
    {
        bbatDoval[3] = mainAppWin->modbusCommObj->setBitHigh(bbatDoval[3],(bitPosition - 48),highLow);
    }
}
