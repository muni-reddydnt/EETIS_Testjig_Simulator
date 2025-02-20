#include "bfcmdf.h"
#include "ui_bfcmdf.h"
#include "mainwindow.h"

extern MainWindow *mainAppWin;
bfcmdf::bfcmdf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bfcmdf)
{
    ui->setupUi(this);
    bfcmdfTimer = new QTimer(this);
    connect(bfcmdfTimer, SIGNAL(timeout()),this, SLOT(startTest()));
    bfcmdfTimer->start(100);
    uiListappend();
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

void bfcmdf::diListappend()
{
    diLabelList.clear();
    diLabelList.append(ui->lblFireButton1);
    diLabelList.append(ui->lblFireButton2);
    diLabelList.append(ui->lblBreechClosing1);
    diLabelList.append(ui->lblBreechClosing2);
    diLabelList.append(ui->lblSwitch);
}

void bfcmdf::doListappend()
{
    doLabelList.clear();
    doLabelList.append(ui->lblFireButton1_LED);
    doLabelList.append(ui->lblFireButton2_LED);
    doLabelList.append(ui->lblBreechClosing1_LED);
    doLabelList.append(ui->lblBreechClosing2_LED);
    doLabelList.append(ui->lblSwitch_LED);
}

void bfcmdf::continutyErrorListappend()
{
    continutyErrorList.clear();
    continutyErrorList.append(ui->cbContinutyFireButton1);
    continutyErrorList.append(ui->cbContinutyFireButton2);
    continutyErrorList.append(ui->cbContinutyBreechClosing1);
    continutyErrorList.append(ui->cbContinutyBreechClosing2);
    continutyErrorList.append(ui->cbContinutySwitch);
}

void bfcmdf::crossContinutyErrorListappend()
{
    crossContinutyErrorList.clear();
    crossContinutyErrorList.append(ui->cbCrossContinutyFireButton1);
    crossContinutyErrorList.append(ui->cbCrossContinutyFireButton2);
    crossContinutyErrorList.append(ui->cbCrossContinutyBreechClosing1);
    crossContinutyErrorList.append(ui->cbCrossContinutyBreechClosing2);
    crossContinutyErrorList.append(ui->cbCrossContinutySwitch);
}

void bfcmdf::ckForceDoOnListAppend()
{
    do_OnCbList.clear();
    do_OnCbList.append(ui->cbFireButton1_On);
    do_OnCbList.append(ui->cbFireButton2_On);
    do_OnCbList.append(ui->cbBreechClosing1_On);
    do_OnCbList.append(ui->cbBreechClosing2_On);
    do_OnCbList.append(ui->cbSwitch_On);
}

void bfcmdf::ckForceDoOnOffListAppend()
{
    do_OffCbList.clear();
    do_OffCbList.append(ui->cbFireButton1_Off);
    do_OffCbList.append(ui->cbFireButton2_Off);
    do_OffCbList.append(ui->cbBreechClosing1_Off);
    do_OffCbList.append(ui->cbBreechClosing2_Off);
    do_OffCbList.append(ui->cbSwitch_Off);
}

void bfcmdf::addDiStructInList()
{
    diBFCMDFDiList.clear();
    BFCMDFDiStrut.diNum = BFCMDF_FIRE_BUTTON_DI1;
    diBFCMDFDiList.append(BFCMDFDiStrut);
    BFCMDFDiStrut.diNum = BFCMDF_FIRE_BUTTON_DI2;
    diBFCMDFDiList.append(BFCMDFDiStrut);
    BFCMDFDiStrut.diNum = BFCMDF_BREECHCLOSING_DI1;
    diBFCMDFDiList.append(BFCMDFDiStrut);
    BFCMDFDiStrut.diNum = BFCMDF_BREECHCLOSING_DI2;
    diBFCMDFDiList.append(BFCMDFDiStrut);
    BFCMDFDiStrut.diNum = BFCMDF_CONTINUITY_DI;
    diBFCMDFDiList.append(BFCMDFDiStrut);
}

void bfcmdf::addDoStructInList()
{
    doBFCMDFList.clear();
    BFCMDFDoStrut.doNum = BFCMDF_FIRE_BUTTON_DO1;
    doBFCMDFList.append(BFCMDFDoStrut);
    BFCMDFDoStrut.doNum = BFCMDF_FIRE_BUTTON_DO2;
    doBFCMDFList.append(BFCMDFDoStrut);
    BFCMDFDoStrut.doNum = BFCMDF_BREECHCLOSING_DO1;
    doBFCMDFList.append(BFCMDFDoStrut);
    BFCMDFDoStrut.doNum = BFCMDF_BREECHCLOSING_DO2;
    doBFCMDFList.append(BFCMDFDoStrut);
    BFCMDFDoStrut.doNum = BFCMDF_CONTINUITY_DO;
    doBFCMDFList.append(BFCMDFDoStrut);
}

void bfcmdf::uiListappend()
{
     diListappend();
     doListappend();
     continutyErrorListappend();
     crossContinutyErrorListappend();
     ckForceDoOnListAppend();
     ckForceDoOnOffListAppend();
     addDiStructInList();
     addDoStructInList();
}

void bfcmdf::checkPoweronDI()
{
    int powerOn = mainAppWin->modbusCommObj->getDiValue(BFCMDF_POWERON_DI);
    if(powerOn == 1)
    {
        ui->lblPowerOn->setStyleSheet(GREEN_BUTTON_STYLESHEET);
    }
    else
    {
        ui->lblPowerOn->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
    }
}

void bfcmdf::checkDIs()
{
    int fireReadyLed = mainAppWin->modbusCommObj->getDiValue(BFCMDF_FIRE_READY_DI);
    int fireForbiddenLed = mainAppWin->modbusCommObj->getDiValue(BFCMDF_FIRE_FORBIDDEN_DI);
    int shellLoadedLed = mainAppWin->modbusCommObj->getDiValue(BFCMDF_SHELLLOADING_LED_DI);
    if(fireReadyLed == 1)
    {
        ui->lblFireReady->setStyleSheet(GREEN_BUTTON_STYLESHEET);
    }
    else
    {
        ui->lblFireReady->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
    }

    if(fireForbiddenLed == 1)
    {
        ui->lblFireForbidden->setStyleSheet(GREEN_BUTTON_STYLESHEET);
    }
    else
    {
        ui->lblFireForbidden->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
    }

    if(shellLoadedLed == 1)
    {
        ui->lblShellLoaded->setStyleSheet(GREEN_BUTTON_STYLESHEET);
    }
    else
    {
        ui->lblShellLoaded->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
    }
}

void bfcmdf::sendTestDos()
{
    if(BFCMDFResultList.at(3).Result == 1)
    {
        testDiCount = 1;
    }

    if(testDiCount == 1 && BFCMDFResultList.at(3).Result == 0)
    {
        mainAppWin->modbusCommObj->setRegisterHIgh(BFCMDF_FIREREADY_DO, 1,bfcmdfDoval);
        mainAppWin->modbusCommObj->setRegisterHIgh(BFCMDF_FIRE_FORBIDDEN_LED_DO, 1,bfcmdfDoval);
        mainAppWin->modbusCommObj->setRegisterHIgh(BFCMDF_SHELLLOADING_LED_DO, 1,bfcmdfDoval);
    }
    else
    {
        mainAppWin->modbusCommObj->setRegisterHIgh(BFCMDF_FIREREADY_DO, 0,bfcmdfDoval);
        mainAppWin->modbusCommObj->setRegisterHIgh(BFCMDF_FIRE_FORBIDDEN_LED_DO, 0,bfcmdfDoval);
        mainAppWin->modbusCommObj->setRegisterHIgh(BFCMDF_SHELLLOADING_LED_DO, 0,bfcmdfDoval);
    }
}

void bfcmdf::startTest()
{
    BFCMDFResultList.clear();
    for(int i =0; i< doBFCMDFList.count(); i++)
    {
        BFCMDFDiResultStruct.Result = mainAppWin->modbusCommObj->getDiValue(diBFCMDFDiList.at(i).diNum);
        BFCMDFResultList.append(BFCMDFDiResultStruct);
    }
    processHarnessDiDO();
    checkPoweronDI();
    checkDIs();
    processContinutyProcess();
    sendTestDos();
}

void bfcmdf::processHarnessDiDO()
{
    if(ui->ckHarnessForceDoOn->isChecked() == 1)
    {
        mainAppWin->modbusCommObj->setRegisterHIgh(HARNESS_BFCMD_CHK_DO1, 1,bfcmdfDoval);
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
            ui->lblHarness->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
            mainAppWin->modbusCommObj->setRegisterHIgh(HARNESS_BFCMD_CHK_DO1, 0, bfcmdfDoval);
            ui->lblHarnessLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
    }
    mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bfcmdfDoval);

}

void bfcmdf::processContinutyProcess()
{
    for(int i =0; i < BFCMDFResultList.count(); i++)
    {
        if(do_OnCbList.at(i)->isChecked() == 1)
        {
            mainAppWin->modbusCommObj->setRegisterHIgh(doBFCMDFList.at(i).doNum, 1, bfcmdfDoval);
            doLabelList.at(i)->setStyleSheet(YELLOW_DO_STYLESHEET);
        }
        else if(do_OffCbList.at(i)->isChecked() == 1)
        {
            mainAppWin->modbusCommObj->setRegisterHIgh(doBFCMDFList.at(i).doNum, 0, bfcmdfDoval);
            doLabelList.at(i)->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
        else
        {
            if(BFCMDFResultList.at(i).Result == 1)
            {
                diLabelList.at(i)->setStyleSheet(GREEN_BUTTON_STYLESHEET);
                if(continutyErrorList.at(i)->isChecked() == 1)
                {
                    mainAppWin->modbusCommObj->setRegisterHIgh(doBFCMDFList.at(i).doNum, 0, bfcmdfDoval);
                    doLabelList.at(i)->setStyleSheet(DEFAULT_DO_STYLESHEET);
                }
                else
                {
                    mainAppWin->modbusCommObj->setRegisterHIgh(doBFCMDFList.at(i).doNum, 1, bfcmdfDoval);
                    doLabelList.at(i)->setStyleSheet(DO_GREEN_STYLESHEET);
                }
            }
            else
            {
                doLabelList.at(i)->setStyleSheet(DEFAULT_DO_STYLESHEET);
                mainAppWin->modbusCommObj->setRegisterHIgh(doBFCMDFList.at(i).doNum, 0, bfcmdfDoval);
                diLabelList.at(i)->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
            }
        }
    }
    mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bfcmdfDoval);

}
