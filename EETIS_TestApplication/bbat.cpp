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

void BBAT::uiListappend()
{
    addDo1LabelsInList();
    addDo2LabelsInList();
    addContErrForDo1InList();
    addContErrForDo2InList();
    addDo1OnOffCbInList();
    addDo2OnOffCbInList();
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
    do1_2ContinuityErrList.clear();
    do1_2ContinuityErrList.append(ui->cbBBATJ2A);
    do1_2ContinuityErrList.append(ui->cbBBATJ2B);
    do1_2ContinuityErrList.append(ui->cbBBATJ2C);
    do1_2ContinuityErrList.append(ui->cbBBATJ2G);
    do1_2ContinuityErrList.append(ui->cbBBATJ2H);
    do1_2ContinuityErrList.append(ui->cbBBATJ2J);
    do1_2ContinuityErrList.append(ui->cbBBATJ3A);
    do1_2ContinuityErrList.append(ui->cbBBATJ3B);
    do1_2ContinuityErrList.append(ui->cbBBATJ4A);
    do1_2ContinuityErrList.append(ui->cbBBATJ5A);
    do1_2ContinuityErrList.append(ui->cbBBATJ5B);
    do1_2ContinuityErrList.append(ui->cbBBATJ5E);
    do1_2ContinuityErrList.append(ui->cbBBATJ5F);
    do1_2ContinuityErrList.append(ui->cbBBATJ61);
    do1_2ContinuityErrList.append(ui->cbBBATJ7A);
    do1_2ContinuityErrList.append(ui->cbBBATJ7B);
    do1_2ContinuityErrList.append(ui->cbBBATJ8A);
    do1_2ContinuityErrList.append(ui->cbBBATJ8C);
    do1_2ContinuityErrList.append(ui->cbBBATJ8E);
}

void BBAT::addContErrForDo1InList()
{
    do1_1ContinuityErrList.clear();
    do1_1ContinuityErrList.append(ui->cbBBATJ2D);
    do1_1ContinuityErrList.append(ui->cbBBATJ2E);
    do1_1ContinuityErrList.append(ui->cbBBATJ2F);
    do1_1ContinuityErrList.append(ui->cbBBATJ2K);
    do1_1ContinuityErrList.append(ui->cbBBATJ2L);
    do1_1ContinuityErrList.append(ui->cbBBATJ2M);
    do1_1ContinuityErrList.append(ui->cbBBATJ3C);
    do1_1ContinuityErrList.append(ui->cbBBATJ3D);
    do1_1ContinuityErrList.append(ui->cbBBATJ4B);
    do1_1ContinuityErrList.append(ui->cbBBATJ5C);
    do1_1ContinuityErrList.append(ui->cbBBATJ5D);
    do1_1ContinuityErrList.append(ui->cbBBATJ5G);
    do1_1ContinuityErrList.append(ui->cbBBATJ62);
    do1_1ContinuityErrList.append(ui->cbBBATJ7C);
    do1_1ContinuityErrList.append(ui->cbBBATJ7D);
    do1_1ContinuityErrList.append(ui->cbBBATJ8D);
    do1_1ContinuityErrList.append(ui->cbBBATJ8B);
    do1_1ContinuityErrList.append(ui->cbBBATJ8F);
}

void BBAT::addDo1OnOffCbInList()
{
    do1_1OnOffCbList.clear();
    do1_1OnOffCbList.append(ui->cbJ2D_OnOff);
    do1_1OnOffCbList.append(ui->cbJ2E_OnOff);
    do1_1OnOffCbList.append(ui->cbJ2F_OnOff);
    do1_1OnOffCbList.append(ui->cbJ2K_OnOff);
    do1_1OnOffCbList.append(ui->cbJ2L_OnOff);
    do1_1OnOffCbList.append(ui->cbJ2M_OnOff);
    do1_1OnOffCbList.append(ui->cbJ3C_OnOff);
    do1_1OnOffCbList.append(ui->cbJ3D_OnOff);
    do1_1OnOffCbList.append(ui->cbJ4B_OnOff);
    do1_1OnOffCbList.append(ui->cbJ5C_OnOff);
    do1_1OnOffCbList.append(ui->cbJ5D_OnOff);
    do1_1OnOffCbList.append(ui->cbJ5G_OnOff);
    do1_1OnOffCbList.append(ui->cbJ62_OnOff);
    do1_1OnOffCbList.append(ui->cbJ7C_OnOff);
    do1_1OnOffCbList.append(ui->cbJ7D_OnOff);
    do1_1OnOffCbList.append(ui->cbJ8D_OnOff);
    do1_1OnOffCbList.append(ui->cbJ8B_OnOff);
    do1_1OnOffCbList.append(ui->cbJ8F_OnOff);
}

void BBAT::addDo2OnOffCbInList()
{
    do1_2OnOffCbList.clear();
    do1_2OnOffCbList.append(ui->cbJ2A_OnOff);
    do1_2OnOffCbList.append(ui->cbJ2B_OnOff);
    do1_2OnOffCbList.append(ui->cbJ2C_OnOff);
    do1_2OnOffCbList.append(ui->cbJ2G_OnOff);
    do1_2OnOffCbList.append(ui->cbJ2H_OnOff);
    do1_2OnOffCbList.append(ui->cbJ2J_OnOff);
    do1_2OnOffCbList.append(ui->cbJ3A_OnOff);
    do1_2OnOffCbList.append(ui->cbJ3B_OnOff);
    do1_2OnOffCbList.append(ui->cbJ4A_OnOff);
    do1_2OnOffCbList.append(ui->cbJ5A_OnOff);
    do1_2OnOffCbList.append(ui->cbJ5B_OnOff);
    do1_2OnOffCbList.append(ui->cbJ5E_OnOff);
    do1_2OnOffCbList.append(ui->cbJ5F_OnOff);
    do1_2OnOffCbList.append(ui->cbJ61_OnOff);
    do1_2OnOffCbList.append(ui->cbJ7A_OnOff);
    do1_2OnOffCbList.append(ui->cbJ7B_OnOff);
    do1_2OnOffCbList.append(ui->cbJ8A_OnOff);
    do1_2OnOffCbList.append(ui->cbJ8C_OnOff);
    do1_2OnOffCbList.append(ui->cbJ8E_OnOff);
}

void BBAT::addDiDoStructInList()
{
    addDoStructInList();
}

void BBAT::addDoStructInList()
{
    do1_1List.clear();
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

void BBAT::startTest()
{
    //Check if correct harness is connected
    checkCorrectHarness();

    //Check if Power ON DI is received
    checkPowerOnDI();

    //Check if timer check DIs received
    checkTimerChkDIs();
}

void BBAT::checkCorrectHarness()
{
    int harnessChkDI1= mainAppWin->modbusCommObj->getDiValue(HARNESS_BBAT_CHK_DI1);
    int harnessChkDI2 = mainAppWin->modbusCommObj->getDiValue(HARNESS_BBAT_CHK_DI2);

    if(harnessChkDI1 == 1)
    {
        ui->lblCorrectHDI1->setStyleSheet(DI_RECEIVED_STYLESHEET);

        //Check if continuity error for DI1 is selected
        if(ui->cbContErrHarnessDO1->isChecked())
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

    if(harnessChkDI2 == 1)
    {
        ui->lblCorrectHDI2->setStyleSheet(DI_RECEIVED_STYLESHEET);

        //Check if continuity error for DI2 is selected
        if(ui->cbContErrHarnessDO2->isChecked())
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
    mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bbatDoval);
}

void BBAT::checkPowerOnDI()
{
    resetAllDisAndDosLabels();

    int powerOnDI = mainAppWin->modbusCommObj->getDiValue(POWER_ON_DI);

    if(powerOnDI == 1)
    {
        ui->lblPowerOn->setStyleSheet(DI_RECEIVED_STYLESHEET);

        //qDebug()<<"do1_1List.count:"<<do1_1List.count();

        for (int i = 0; i < do1_1List.count(); i++)
        {
            if(do1_1ContinuityErrList.at(i)->isChecked() == 1)
            {
                setRegisterHigh(do1_1List.at(i).doNum, 0);
                do1_1LabelList[i]->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
            }
            else if (do1_1ContinuityErrList.at(i)->isChecked() != 1)
            {
                setRegisterHigh(do1_1List.at(i).doNum, 1);
                do1_1LabelList[i]->setStyleSheet(GREEN_BUTTON_STYLESHEET);
            }
            mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bbatDoval);
            //        qDebug()<<"bbatDoval = "<<bbatDoval;
        }

        for(int i = 0; i< do1_2List.count(); i++)
        {
            if(do1_2ContinuityErrList.at(i)->isChecked() == 1)
            {
                setRegisterHigh(do1_2List.at(i).doNum, 0);
                do1_2LabelList[i]->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
            }
            else if (do1_2ContinuityErrList.at(i)->isChecked() != 1)
            {
                setRegisterHigh(do1_2List.at(i).doNum, 1);
                do1_2LabelList[i]->setStyleSheet(GREEN_BUTTON_STYLESHEET);
            }
            mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bbatDoval);
            //        qDebug()<<"bbatDoval = "<<bbatDoval;
        }

        //check if DO on off is selected
        checkDoOnOffSelected();

        //Check if J8G DI is received
        checkJ8GDI();
    }
}

void BBAT::checkDoOnOffSelected()
{
    for (int i = 0; i < do1_1List.count(); i++)
    {
        if(do1_1OnOffCbList.at(i)->isChecked() == 1)
        {
            setRegisterHigh(do1_1List.at(i).doNum, 1);
            do1_1LabelList[i]->setStyleSheet(YELLOW_BUTTON_STYLESHEET);
        }
        //        else if (do1_1ContinuityErrList.at(i)->isChecked() != 1)
        //        {
        //            setRegisterHigh(do1_1List.at(i).doNum, 0);
        //            do1_1LabelList[i]->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
        //        }
        mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bbatDoval);
        //        qDebug()<<"bbatDoval = "<<bbatDoval;
    }

    for(int i = 0; i< do1_2List.count(); i++)
    {
        if(do1_2OnOffCbList.at(i)->isChecked() == 1)
        {
            setRegisterHigh(do1_2List.at(i).doNum, 1);
            do1_2LabelList[i]->setStyleSheet(YELLOW_BUTTON_STYLESHEET);
        }
        //        else if (do1_2ContinuityErrList.at(i)->isChecked() != 1)
        //        {
        //            setRegisterHigh(do1_2List.at(i).doNum, 0);
        //            do1_2LabelList[i]->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
        //        }
        mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bbatDoval);
        //        qDebug()<<"bbatDoval = "<<bbatDoval;
    }
}

void BBAT::checkJ8GDI()
{
    int J8GDI = mainAppWin->modbusCommObj->getDiValue(BBAT_DI_8);

    if(J8GDI == 1)
    {
        ui->lblJ8G_DI->setStyleSheet(DI_RECEIVED_STYLESHEET);

        if(ui->cbBBATJ8G->isChecked() == 1)
        {
            bbatDoval[2]  = mainAppWin->modbusCommObj->setBitHigh(bbatDoval[1],((BBAT_DO_46) - 32),0);
            ui->lbl_J8H_DO->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
        else if(ui->cbBBATJ8G->isChecked() !=1)
        {
            bbatDoval[2]  = mainAppWin->modbusCommObj->setBitHigh(bbatDoval[1],((BBAT_DO_46) - 32),1);
            ui->lbl_J8H_DO->setStyleSheet(DO_GREEN_STYLESHEET);
        }
    }
    else
    {
        ui->lblJ8G_DI->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
    }
}

void BBAT::checkTimerChkDIs()
{
    int timerChkDI1 = mainAppWin->modbusCommObj->getDiValue(BBAT_TIMERCHK_DI_1);
    int timerChkDI2 = mainAppWin->modbusCommObj->getDiValue(BBAT_TIMERCHK_DI_2);

    if(timerChkDI1 == 1 && timerChkDI2 == 1)
    {
        ui->dsTimerVal->setEnabled(false);
        timerChkCount++;
    }

    if(timerChkDI1 == 1)
    {
        setRegisterHigh(timerchkDoList.at(0).doNum, 1);
        ui->lblTimerChkDI1->setStyleSheet(DI_RECEIVED_STYLESHEET);
    }
    if(timerChkDI2 == 1)
    {
        setRegisterHigh(timerchkDoList.at(1).doNum, 1);
        ui->lblTimerChkDI2->setStyleSheet(DI_RECEIVED_STYLESHEET);
    }

    int timerValue = (ui->dsTimerVal->value()) * MS_TO_SEC;

    if(timerChkCount % 10)
    {
        qDebug()<<"timerValue:"<<timerValue<<"timerChkCountInSecs:"<<timerChkCount/10;
    }

    if(timerChkCount >= timerValue)
    {
        timerChkCount = 0;

        if(ui->cbTimerChkDO1->isChecked() == 1)
        {
            setRegisterHigh(timerchkDoList.at(0).doNum, 0);
            ui->lblTimerChkDO1->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
        else if(ui->cbTimerChkDO1->isChecked() != 1)
        {
            setRegisterHigh(timerchkDoList.at(0).doNum, 1);
            ui->lblTimerChkDO1->setStyleSheet(DO_GREEN_STYLESHEET);
        }

        if(ui->cbTimerChkDO2->isChecked() == 1)
        {
            setRegisterHigh(timerchkDoList.at(1).doNum, 0);
            ui->lblTimerChkDO2->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
        else if(ui->cbTimerChkDO2->isChecked() != 1)
        {
            setRegisterHigh(timerchkDoList.at(1).doNum, 1);
            ui->lblTimerChkDO2->setStyleSheet(DO_GREEN_STYLESHEET);
        }

        mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bbatDoval);

        sendAiData();
    }
}

void BBAT::sendAiData()
{
    bbatAoVal[BBAT_AO_1] = (ui->dbsJ7aToJ7b->value() / 2);
    bbatAoVal[BBAT_AO_2] = (ui->dbsJ7btoJ7c->value() / 2);
    bbatAoVal[BBAT_AO_3] = (ui->dbsJ7aToJ7c->value() / 2);

    mainAppWin->modbusCommObj->sendDoAoData(AI_TRANS_ID,16, bbatAoVal);
}

void BBAT::resetAllDisAndDosLabels()
{
    //Reset DIs
    ui->lblPowerOn->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
    ui->lbl_J8H_DO->setStyleSheet(DEFAULT_DO_STYLESHEET);

    //Reset DOs
    for(int i = 0; i< do1_1LabelList.count(); i++)
    {
        do1_1LabelList.at(i)->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
    }

    for(int i = 0; i< do1_2LabelList.count(); i++)
    {
        do1_2LabelList.at(i)->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
    }

    ui->lbl_J8H_DO->setStyleSheet(DEFAULT_DO_STYLESHEET);
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
