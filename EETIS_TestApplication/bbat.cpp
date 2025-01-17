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
    connect(updateUidata, SIGNAL(timeout()),this, SLOT(startTest()));
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
    do1_1List.clear();
    //BBATresultList.clear();
    stBBATDo.doNum = BBAT_DO1_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO2_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO3_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO4_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO5_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO6_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO7_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO8_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO9_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO10_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO11_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO12_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO14_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO15_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO16_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO17_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO18_1;
    do1_1List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO19_1;
    do1_1List.append(stBBATDo);

    stBBATDo.doNum = BBAT_DO1_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO2_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO3_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO4_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO5_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO6_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO7_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO8_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO9_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO10_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO11_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO12_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO13_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO14_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO15_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO16_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO17_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO18_2;
    do1_2List.append(stBBATDo);
    stBBATDo.doNum = BBAT_DO19_2;
    do1_2List.append(stBBATDo);

    stBBATTimerchkDo.doNum = BBAT_TIMERCHK_DO_1;
    timerchkDoList.append(stBBATTimerchkDo);
    stBBATTimerchkDo.doNum = BBAT_TIMERCHK_DO_2;
    timerchkDoList.append(stBBATTimerchkDo);
}

void BBAT::addDiStructInList()
{
    stBBATDi.diNum = POWER_ON_DI;
    diBBATList.append(stBBATDi);
}

void BBAT::processHarnessDiDO()
{
    checkCorrectHarness();
}

void BBAT::checkCorrectHarness()
{
    int value1= mainAppWin->modbusCommObj->getDiValue(HARNESS_BBAT_CHK_DI1);
    int value2 = mainAppWin->modbusCommObj->getDiValue(HARNESS_BBAT_CHK_DI2);

    //    qDebug()<<"value1:"<<value1<<"value2:"<<value2;

    if(value1 == 1)
    {
        //        qDebug()<<"value1:"<<value1;

        //        ui->lblCorrectHDI1->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        ui->lblCorrectHDI1->setStyleSheet(DI_RECEIVED_STYLESHEET);

        if(ui->cbHarnessDI1->isChecked())
        {
            bbatDoval[1]  = mainAppWin->modbusCommObj->setBitHigh(bbatDoval[1],((HARNESS_BBAT_CHK_DO1) - 16),0);
            ui->lblHarnessDO1->setStyleSheet("QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}");
        }
        else
        {
            bbatDoval[1]  = mainAppWin->modbusCommObj->setBitHigh(bbatDoval[1],((HARNESS_BBAT_CHK_DO1) - 16),1);
            ui->lblHarnessDO1->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
        }
    }

    if(value2 == 1)
    {
        //        qDebug()<<"value2:"<<value2;

        ui->lblCorrectHDI2->setStyleSheet(DI_RECEIVED_STYLESHEET);

        if(ui->cbHarnessDI2->isChecked())
        {
            bbatDoval[3] = mainAppWin->modbusCommObj->setBitHigh(bbatDoval[3],((HARNESS_BBAT_CHK_DO2) - 48),0);
            ui->lblHarnessDO2->setStyleSheet("QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}");
        }
        else
        {
            bbatDoval[3] = mainAppWin->modbusCommObj->setBitHigh(bbatDoval[3],((HARNESS_BBAT_CHK_DO2) - 48),1);
            ui->lblHarnessDO2->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
        }
    }
    //    qDebug()<<"bbatDoval:"<<bbatDoval;

    mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bbatDoval);
}

void BBAT::processOfPowerOffDOToDI()
{
    int poweroffDI1 = mainAppWin->modbusCommObj->getDiValue(HARNESS_BBAT_CHK_DI1);
    int poweroffDI2 = mainAppWin->modbusCommObj->getDiValue(HARNESS_BBAT_CHK_DI2);

    if(poweroffDI1 == 1)
    {
        setRegisterHigh(timerchkDoList.at(0).doNum, 1);
        ui->lblPowerOffDi1->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
    }
    if(poweroffDI2 == 1)
    {
        setRegisterHigh(timerchkDoList.at(1).doNum, 1);
        ui->lblPowerOffDi1->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
    }
}

void BBAT::processDoVals()
{
    //    qDebug()<<"processDoVals";

    //    memset(&bbatDoval[0], 0 , sizeof(bbatDoval));
    resetAllDisAndDos();
    qDebug()<<"do1_1List.count:"<<do1_1List.count();

    for (int i = 0; i < do1_1List.count(); i++)
    {
        if(continuityErrListForDO1.at(i)->isChecked() == 1)
        {
            qDebug()<<"continuityErrorList1=1:"<<i;
            setRegisterHigh(do1_1List.at(i).doNum, 0);
            do1_1LabelList[i]->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
        }
        else if (continuityErrListForDO1.at(i)->isChecked() != 1)
        {
            qDebug()<<"continuityErrorList1=0:"<<i;
            setRegisterHigh(do1_1List.at(i).doNum, 1);
            do1_1LabelList[i]->setStyleSheet(GREEN_BUTTON_STYLESHEET);
        }
        mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bbatDoval);
        //        qDebug()<<"bbatDoval = "<<bbatDoval;
    }

    for(int i = 0; i< do1_2List.count(); i++)
    {
        if(continuityErrListForDO2.at(i)->isChecked() == 1)
        {
            qDebug()<<"continuityErrorList2 = 1";
            setRegisterHigh(do1_2List.at(i).doNum, 0);
            do1_2LabelList[i]->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
        }
        else if (continuityErrListForDO2.at(i)->isChecked() != 1)
        {
            qDebug()<<"continuityErrorList2 = 0";
            setRegisterHigh(do1_2List.at(i).doNum, 1);
            do1_2LabelList[i]->setStyleSheet(GREEN_BUTTON_STYLESHEET);
        }
        mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bbatDoval);
        //        qDebug()<<"bbatDoval = "<<bbatDoval;
    }

#if 0
    for(int i = 0; i< doBBATList.count(); i++)
    {
        setRegisterHigh(doBBATList.at(i).doNum, 1);
        setRegisterHigh(doBBATList1.at(i).doNum, 1);
        mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bbatDoval);
        doLabelList.at(i)->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
    }
#endif
}

void BBAT::resetAllDisAndDos()
{
    for(int i = 0; i< do1_1LabelList.count(); i++)
    {
        do1_1LabelList.at(i)->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
    }

    for(int i = 0; i< do1_2LabelList.count(); i++)
    {
        do1_2LabelList.at(i)->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
    }
}

void BBAT::uiListappend()
{
    addDo1LabelsInList();
    addDo2LabelsInList();
    addContErrForDo1InList();
    addContErrForDo2InList();
}

void BBAT::addDo2LabelsInList()
{
    do1_2LabelList.clear();
    do1_2LabelList.append(ui->lblJ2A_DO);
    do1_2LabelList.append(ui->lblJ2B_DO);
    do1_2LabelList.append(ui->lblJ2C_DO);
    do1_2LabelList.append(ui->lblJ2G_DO);
    do1_2LabelList.append(ui->lblJ2H_DO);
    do1_2LabelList.append(ui->lblJ2J_DO);
    do1_2LabelList.append(ui->lblJ3A_DO);
    do1_2LabelList.append(ui->lblJ3B_DO);
    do1_2LabelList.append(ui->lblJ4A_DO);
    do1_2LabelList.append(ui->lblJ5A_DO);
    do1_2LabelList.append(ui->lblJ5B_DO);
    do1_2LabelList.append(ui->lblJ5E_DO);
    do1_2LabelList.append(ui->lblJ5F_DO);
    do1_2LabelList.append(ui->lblJ61_DO);
    do1_2LabelList.append(ui->lblJ7A_DO);
    do1_2LabelList.append(ui->lblJ7B_DO);
    do1_2LabelList.append(ui->lblJ8A_DO);
    do1_2LabelList.append(ui->lblJ8C_DO);
    do1_2LabelList.append(ui->lblJ8E_DO);
}

void BBAT::addDo1LabelsInList()
{
    do1_1LabelList.clear();
    do1_1LabelList.append(ui->lblJ2D_DO);
    do1_1LabelList.append(ui->lblJ2E_DO);
    do1_1LabelList.append(ui->lblJ2F_DO);
    do1_1LabelList.append(ui->lblJ2K_DO);
    do1_1LabelList.append(ui->lblJ2L_DO);
    do1_1LabelList.append(ui->lblJ2M_DO);
    do1_1LabelList.append(ui->lblJ3C_DO);
    do1_1LabelList.append(ui->lblJ3D_DO);
    do1_1LabelList.append(ui->lblJ4B_DO);
    do1_1LabelList.append(ui->lblJ5C_DO);
    do1_1LabelList.append(ui->lblJ5D_DO);
    do1_1LabelList.append(ui->lblJ5G_DO);
    do1_1LabelList.append(ui->lblJ62_DO);
    do1_1LabelList.append(ui->lblJ7C_DO);
    do1_1LabelList.append(ui->lblJ7D_DO);
    do1_1LabelList.append(ui->lblJ8D_DO);
    do1_1LabelList.append(ui->lblJ8B_DO);
    do1_1LabelList.append(ui->lblJ8F_DO);
}

void BBAT::addContErrForDo2InList()
{
    continuityErrListForDO2.clear();
    continuityErrListForDO2.append(ui->cbBBATJ2A);
    continuityErrListForDO2.append(ui->cbBBATJ2B);
    continuityErrListForDO2.append(ui->cbBBATJ2C);
    continuityErrListForDO2.append(ui->cbBBATJ2G);
    continuityErrListForDO2.append(ui->cbBBATJ2H);
    continuityErrListForDO2.append(ui->cbBBATJ2J);
    continuityErrListForDO2.append(ui->cbBBATJ3A);
    continuityErrListForDO2.append(ui->cbBBATJ3B);
    continuityErrListForDO2.append(ui->cbBBATJ4A);
    continuityErrListForDO2.append(ui->cbBBATJ5A);
    continuityErrListForDO2.append(ui->cbBBATJ5B);
    continuityErrListForDO2.append(ui->cbBBATJ5E);
    continuityErrListForDO2.append(ui->cbBBATJ5F);
    continuityErrListForDO2.append(ui->cbBBATJ61);
    continuityErrListForDO2.append(ui->cbBBATJ7A);
    continuityErrListForDO2.append(ui->cbBBATJ7B);
    continuityErrListForDO2.append(ui->cbBBATJ8A);
    continuityErrListForDO2.append(ui->cbBBATJ8C);
    continuityErrListForDO2.append(ui->cbBBATJ8E);
}

void BBAT::addContErrForDo1InList()
{
    continuityErrListForDO1.clear();
    continuityErrListForDO1.append(ui->cbBBATJ2D);
    continuityErrListForDO1.append(ui->cbBBATJ2E);
    continuityErrListForDO1.append(ui->cbBBATJ2F);
    continuityErrListForDO1.append(ui->cbBBATJ2K);
    continuityErrListForDO1.append(ui->cbBBATJ2L);
    continuityErrListForDO1.append(ui->cbBBATJ2M);
    continuityErrListForDO1.append(ui->cbBBATJ3C);
    continuityErrListForDO1.append(ui->cbBBATJ3D);
    continuityErrListForDO1.append(ui->cbBBATJ4B);
    continuityErrListForDO1.append(ui->cbBBATJ5C);
    continuityErrListForDO1.append(ui->cbBBATJ5D);
    continuityErrListForDO1.append(ui->cbBBATJ5G);
    continuityErrListForDO1.append(ui->cbBBATJ62);
    continuityErrListForDO1.append(ui->cbBBATJ7C);
    continuityErrListForDO1.append(ui->cbBBATJ7D);
    continuityErrListForDO1.append(ui->cbBBATJ8D);
    continuityErrListForDO1.append(ui->cbBBATJ8B);
    continuityErrListForDO1.append(ui->cbBBATJ8F);
}

void BBAT::addDiDoStructInList()
{
    addDoStructInList();
    addDiStructInList();
}

void BBAT::sendAiData()
{
    bbatAoVal[BBAT_AO_1] = (ui->dbsJ7aToJ7b->value());
    bbatAoVal[BBAT_AO_2] = (ui->dbsJ7btoJ7c->value());
    bbatAoVal[BBAT_AO_3] = (ui->dbsJ7aToJ7c->value());
    mainAppWin->modbusCommObj->sendDoAoData(AI_TRANS_ID,16, bbatAoVal);
}

void BBAT::startTest()
{
    int timerValue = 0;

    if(startTimerCount)
    {
        timerChkCount++;
    }

    //Check if correct harness is connected
    processHarnessDiDO();
    //    int poweroffDI1 = mainAppWin->modbusCommObj->getDiValue(HARNESS_BBAT_CHK_DI1);
    //    int poweroffDI2 = mainAppWin->modbusCommObj->getDiValue(HARNESS_BBAT_CHK_DI2);
    //    qDebug()<<"poweroffDI1 = "<<poweroffDI1;
    //    qDebug()<<"poweroffDI2 = "<<poweroffDI2;

    int result1 = mainAppWin->modbusCommObj->getDiValue(POWER_ON_DI);
    //    qDebug()<<"result1 = "<<result1;

    if(result1 == 1)
    {
        ui->lblPowerOn->setStyleSheet(DI_RECEIVED_STYLESHEET);
        startSendAo = 1;
        timerChkDO1 = 1;
        timerChkDI1 = mainAppWin->modbusCommObj->getDiValue(BBAT_TIMERCHK_DI_1);
        timerChkDI2 = mainAppWin->modbusCommObj->getDiValue(BBAT_TIMERCHK_DI_2);
        startTimerCount = true;
        //        qDebug()<<"poweroffDI1 = "<<timerChkDI1;
        //        qDebug()<<"poweroffDI2 = "<<timerChkDI2;
    }
    else
    {
        ui->lblPowerOn->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
    }

    if(mainAppWin->startSendData == 1 && mainAppWin->unitStatus == 1 )
    {
        //qDebug()<<"result1 = "<<result1;
        if(timerChkDO1 == 1)
        {
            timerValue = (ui->dsTimerVal->value()) * MS_TO_SEC;

            if(timerChkCount >= timerValue)
            {
                //                qDebug()<<"poweroffDI1 = "<<timerChkDI1;
                //                qDebug()<<"poweroffDI2 = "<<timerChkDI2;
                //                if(timerChkCount % 100 == 0)
                //                {
                //                    qDebug()<<"powerOffSysCount = "<<timerChkCount;
                //                }
                if(timerChkDI1 == 1)
                {
                    setRegisterHigh(timerchkDoList.at(0).doNum, 1);
                    ui->lblPowerOff1LED->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
                    ui->lblPowerOffDi1->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
                }
                if(timerChkDI2 == 1)
                {
                    setRegisterHigh(timerchkDoList.at(1).doNum, 1);
                    ui->lblPowerOff2LED->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
                    ui->lblPowerOffDi2->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
                }
            }
        }
        if(result1 == 1)
        {
            //modbusCommObj->sendData();
            //mainAppWin->modbusCommObj->sendDiData(bbatDoval);
            processDoVals();
        }
        else
        {
            sendAiData();
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
