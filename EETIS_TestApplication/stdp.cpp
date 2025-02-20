#include "stdp.h"
#include "mainwindow.h"
#include "ui_stdp.h"


extern MainWindow *mainAppWin;
stdp::stdp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stdp)
{
    ui->setupUi(this);
    stdpTimer = new QTimer(this);
    connect(stdpTimer, SIGNAL(timeout()),this, SLOT(startTest()));
    //stdpTimer->start(100);

    aiSendTimer = new QTimer(this);
    connect(aiSendTimer, SIGNAL(timeout()),this, SLOT(sendAoData()));


    uiListappend();

    //clear pbStatus
    memset(&pbSts[0], 0, sizeof(pbSts));

}

stdp::~stdp()
{
    delete ui;
}

void stdp::checkCorrectHarness()
{
    int harnessChkDI1= mainAppWin->modbusCommObj->getDiValue(HARNESS_STDP_CHK_DI1);
    int harnessChkDI2 = mainAppWin->modbusCommObj->getDiValue(HARNESS_STDP_CHK_DI2);

    if(ui->cbHarnessD1_On->isChecked() == 1)
    {
        setRegisterHIgh(HARNESS_STDP_CHK_DO1,1);
        ui->lblHarnessDO1->setStyleSheet(YELLOW_DO_STYLESHEET);
    }
    else if(ui->cbHarnessD1_Off->isChecked() == 1)
    {
        setRegisterHIgh(HARNESS_STDP_CHK_DO1,1);
        ui->lblHarnessDO1->setStyleSheet(DEFAULT_DO_STYLESHEET);
    }
    else
    {
        if(harnessChkDI1 == 1)
        {
            //qDebug()<<"start test1";
            ui->lblCorrectHDI1->setStyleSheet(DI_RECEIVED_STYLESHEET);

            //Check if continuity error for DI1 is selected
            if(ui->cbContErrHarnessDO1->isChecked())
            {
                setRegisterHIgh(HARNESS_STDP_CHK_DO1,0);
                ui->lblHarnessDO1->setStyleSheet("QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}");
            }
            else
            {
                setRegisterHIgh(HARNESS_STDP_CHK_DO1,1);
                ui->lblHarnessDO1->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
            }
        }
        else
        {
            setRegisterHIgh(HARNESS_STDP_CHK_DO1,0);
            ui->lblCorrectHDI1->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
            ui->lblHarnessDO1->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
    }

    if(ui->cbHarnessD2_On->isChecked() == 1)
    {
        setRegisterHIgh(HARNESS_STDP_CHK_DO2,1);
        ui->lblHarnessDO2->setStyleSheet(YELLOW_DO_STYLESHEET);
    }
    else if(ui->cbHarnessD2_Off->isChecked() == 1)
    {
        setRegisterHIgh(HARNESS_STDP_CHK_DO2,1);
        ui->lblHarnessDO2->setStyleSheet(DEFAULT_DO_STYLESHEET);
    }
    else
    {
        if(harnessChkDI2 == 1)
        {
            qDebug()<<"start test2";
            ui->lblCorrectHDI2->setStyleSheet(DI_RECEIVED_STYLESHEET);

            //Check if continuity error for DI2 is selected
            if(ui->cbContErrHarnessDO2->isChecked())
            {
                setRegisterHIgh(HARNESS_STDP_CHK_DO2,0);
                ui->lblHarnessDO2->setStyleSheet("QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}");
            }
            else
            {
                setRegisterHIgh(HARNESS_STDP_CHK_DO2,1);
                ui->lblHarnessDO2->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
            }
        }
        else
        {
            setRegisterHIgh(HARNESS_STDP_CHK_DO2,0);
            ui->lblCorrectHDI2->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
            ui->lblHarnessDO2->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
    }
    mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, stdpDoval);
}

void stdp::checkContinuty()
{
    int ContinuityCheck = mainAppWin->modbusCommObj->getDiValue(CONTINUTY_CHECK_STDP_DI);

    if(ui->ckContinutyCheck_On->isChecked() == 1)
    {
        setRegisterHIgh(CONTINUTY_CHECK_STDP_DO,1);
        ui->lblContinutyCheckLED->setStyleSheet(YELLOW_DO_STYLESHEET);
    }
    else if(ui->ckContinutyCheck_Off->isChecked() == 1)
    {
        setRegisterHIgh(CONTINUTY_CHECK_STDP_DO,0);
        ui->lblContinutyCheckLED->setStyleSheet(DEFAULT_DO_STYLESHEET);;
    }
    else
    {
        if(ContinuityCheck == 1)
        {
            ui->lblContinutyCheck->setStyleSheet(GREEN_BUTTON_STYLESHEET);
            if(ui->ckContinutyCheck->isChecked() == 1)
            {
                setRegisterHIgh(CONTINUTY_CHECK_STDP_DO,0);
                ui->lblContinutyCheckLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
               }
            else
            {
                setRegisterHIgh(CONTINUTY_CHECK_STDP_DO,1);
                ui->lblContinutyCheckLED->setStyleSheet(DO_GREEN_STYLESHEET);
            }
        }
        else
        {
            ui->lblContinutyCheck->setStyleSheet(DEFAULT_STYLESHEET);
            setRegisterHIgh(CONTINUTY_CHECK_STDP_DO,0);
            ui->lblContinutyCheckLED->setStyleSheet(DEFAULT_DO_STYLESHEET);

        }
    }
    mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, stdpDoval);
}

void stdp::setRegisterHIgh(int bitPosition, bool highLow)
{
    if(bitPosition > 0 && bitPosition < 16)
    {
        stdpDoval[0] = mainAppWin->modbusCommObj->setBitHigh(stdpDoval[0],bitPosition,highLow);
    }
    else if(bitPosition  >= 16 && bitPosition  <32)
    {
        stdpDoval[1] = mainAppWin->modbusCommObj->setBitHigh(stdpDoval[1],(bitPosition - 16),highLow);
    }
    else if(bitPosition  >= 32 && bitPosition  <48)
    {
        stdpDoval[2] = mainAppWin->modbusCommObj->setBitHigh(stdpDoval[2],(bitPosition - 32),highLow);
    }
    else if(bitPosition  >= 48 && bitPosition  <64)
    {
        stdpDoval[3] = mainAppWin->modbusCommObj->setBitHigh(stdpDoval[3],(bitPosition - 48),highLow);
    }
}

void stdp::checkPushButtonData()
{
    //
    for(int i = 0; i < doSTDPList.count(); i++)
    {
        if(pbSts[i] == 1)
        {
            //memset(&stdpDoval, 0,sizeof(stdpDoval));
            setRegisterHIgh(doSTDPList.at(i).doNum, 1);
            pbList.at(i)->setStyleSheet(PUSHBUTTON_YELLOW_STYLESHEET);
            doLblsList.at(i)->setStyleSheet(YELLOW_DO_STYLESHEET);
        }
        else
        {
            setRegisterHIgh(doSTDPList.at(i).doNum, 0);
            pbList.at(i)->setStyleSheet(PUSHBUTTON_DEFAULT_STYLESHEET);
            doLblsList.at(i)->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
//        qDebug()<<"hello"<<i;
//        qDebug()<<"pbSts : "<<i<<pbSts[i];
    }

    mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, stdpDoval);
}

void stdp::startTest()
{
    //qDebug()<<"Di Timer";
    STDPdiResultList.clear();
    Aidata = mainAppWin->modbusCommObj->getAiValue(STDP_AI);
    for(int i = 0; i < diSTDPList.count(); i++)
    {
        stdpDidataStructResult.Result = mainAppWin->modbusCommObj->getDiValue(diSTDPList.at(i).diNum);
        STDPdiResultList.append(stdpDidataStructResult);
    }
    //harness
    checkCorrectHarness();
    //Emergency
    checkEmergency();
    //power on Di check
    checkPowerOnDi();
    //Continuty check
    checkContinuty();
    diData();
    checkPushButtonData();

    //set Ao data
    setDataInAO();


    if(powerOnDI == 1)
    {
        aiStartCount++;
    }
    else
    {
        aiStartCount = 0;
        aiSend = false;
    }


    if(aiStartCount >= AI_TIME_OUT && aiSend == false)
    {
        aiStartCount = 0;
        aiSendTimer->start(100);
        stdpTimer->stop();
    }



}

void stdp::on_pbDeadman_clicked()
{
    //deadManSts = !deadManSts;
    pbSts[0] = !pbSts[0];
}

void stdp::on_pbUnlocking_clicked()
{
    //unlockingSts = !unlockingSts;
    pbSts[1] = !pbSts[1];
}

void stdp::on_pbGRFD_clicked()
{
    //grfdSts = !grfdSts;
    pbSts[2] = !pbSts[2];
}

void stdp::on_pbGRRD_clicked()
{
    //grrdSts = !grrdSts;
    pbSts[3] = !pbSts[3];
}

void stdp::on_pbLIT_clicked()
{
    //litSts = !litSts;
    pbSts[4] = !pbSts[4];
}

void stdp::on_pbLCWup_clicked()
{
    //lcwUpSts = !lcwUpSts;
    pbSts[5] = !pbSts[5];
}

void stdp::on_pbLCWdn_clicked()
{
    //lcwDnSts = !lcwDnSts;
    pbSts[6] = !pbSts[6];
}

void stdp::on_pbRCWup_clicked()
{
    //rcwUpSts = !rcwUpSts;
    pbSts[7] = !pbSts[7];
}

void stdp::on_pbRCWdn_clicked()
{
    //rcwDnSts = !rcwDnSts;
    pbSts[8] = !pbSts[8];

}

void stdp::on_pbLSup_clicked()
{
    //lsUpSts = !lsUpSts;
    pbSts[9] = !pbSts[9];
}

void stdp::on_pbLSdn_clicked()
{
    //lsDnSts = !lsDnSts;
    pbSts[10] = !pbSts[10];
}

void stdp::on_pbRSup_clicked()
{
    //rsUpSts = !rsUpSts;
    pbSts[11] = !pbSts[11];
}

void stdp::on_pbRSdn_clicked()
{
    //rsDnSts = !rsDnSts;
    pbSts[12] = !pbSts[12];
}

void stdp::uiListappend()
{
    crossContinutyErrorListappend();
    addDoStructInList();
    addDoLblInList();
    addPbInList();
    hideCrosss();
    addDilblInList();
    addDiStructInList();

}

void stdp::addDoLblInList()
{
    doLblsList.clear();
    doLblsList.append(ui->lblDeadmanLED);
    doLblsList.append(ui->lblUnlockingLED);
    doLblsList.append(ui->lblGRFDLED);
    doLblsList.append(ui->lblGRRDLED);
    doLblsList.append(ui->lblLITLED);
    doLblsList.append(ui->lblLCWupLED);
    doLblsList.append(ui->lblLCWdnLED);
    doLblsList.append(ui->lblRCWupLED);
    doLblsList.append(ui->lblRCWdnLED);
    doLblsList.append(ui->lblLSupLED);
    doLblsList.append(ui->lblLSdnLED);
    doLblsList.append(ui->lblRsupLED);
    doLblsList.append(ui->lblRsdnLED);

}

void stdp::addPbInList()
{
    pbList.clear();
    pbList.append(ui->pbDeadman);
    pbList.append(ui->pbUnlocking);
    pbList.append(ui->pbGRFD);
    pbList.append(ui->pbGRRD);
    pbList.append(ui->pbLIT);
    pbList.append(ui->pbLCWup);
    pbList.append(ui->pbLCWdn);
    pbList.append(ui->pbRCWup);
    pbList.append(ui->pbRCWdn);
    pbList.append(ui->pbLSup);
    pbList.append(ui->pbLSdn);
    pbList.append(ui->pbRSup);
    pbList.append(ui->pbRSdn);

}

void stdp::addDiStructInList()
{
    diSTDPList.clear();
    STDPdiStructObj.diNum = BFLI_STDP_DI;
    diSTDPList.append(STDPdiStructObj);
    STDPdiStructObj.diNum = ACLI_STDP_DI;
    diSTDPList.append(STDPdiStructObj);
    STDPdiStructObj.diNum = LBLI_STDP_DI;
    diSTDPList.append(STDPdiStructObj);
    STDPdiStructObj.diNum = AFLI_STDP_DI;
    diSTDPList.append(STDPdiStructObj);

}

void stdp::addDilblInList()
{
    diLblsList.append(ui->lblBFLI);
    diLblsList.append(ui->lblACLI);
    diLblsList.append(ui->lblLBLI);
    diLblsList.append(ui->lblAFLI);
}

void stdp::diData()
{
    for(int i = 0; i < diSTDPList.count(); i++)
    {
        if(STDPdiResultList.at(i).Result == 1)
        {
            diLblsList.at(i)->setStyleSheet(GREEN_BUTTON_STYLESHEET);
        }
        else
        {
            diLblsList.at(i)->setStyleSheet(DEFAULT_STYLESHEET);
        }
    }
}

void stdp::checkPowerOnDi()
{
    powerOnDI = mainAppWin->modbusCommObj->getDiValue(STDP_START_DI);
    if(powerOnDI == 1)
    {
        ui->lblPowerOn->setStyleSheet(GREEN_BUTTON_STYLESHEET);
    }
    else
    {
        ui->lblPowerOn->setStyleSheet(DEFAULT_STYLESHEET);
    }
}

void stdp::checkEmergency()
{
    int Emergency1 = mainAppWin->modbusCommObj->getDiValue(STDP_EMERGENCY_DI1);
    int Emergency2 = mainAppWin->modbusCommObj->getDiValue(STDP_EMERGENCY_DI2);

    if(ui->cbEmgStop1_On->isChecked() == 1)
    {
        setRegisterHIgh(STDP_EMERGENCY_DO1, 1);
        ui->lblEmergency1LED->setStyleSheet(YELLOW_DO_STYLESHEET);
    }
    else if(ui->cbEmgStop1_Off->isChecked() == 1)
    {
        setRegisterHIgh(STDP_EMERGENCY_DO1, 0);
        ui->lblEmergency1LED->setStyleSheet(YELLOW_DO_STYLESHEET);
    }
    else
    {
        if(Emergency1 == 1)
        {
            ui->lblEmergency1->setStyleSheet(GREEN_BUTTON_STYLESHEET);
            ui->lblEmergency1LED->setStyleSheet(DO_GREEN_STYLESHEET);
            setRegisterHIgh(STDP_EMERGENCY_DO1, 1);
        }
        else
        {
            setRegisterHIgh(STDP_EMERGENCY_DO1, 0);
            ui->lblEmergency1->setStyleSheet(DEFAULT_STYLESHEET);
            ui->lblEmergency1LED->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
    }

    //Emergency 2
    if(ui->cbEmgStop2_On->isChecked() == 1)
    {
        setRegisterHIgh(STDP_EMERGENCY_DO2, 1);
        ui->lblEmergency2LED->setStyleSheet(YELLOW_DO_STYLESHEET);
    }
    else if(ui->cbEmgStop2_Off->isChecked() == 1)
    {
        setRegisterHIgh(STDP_EMERGENCY_DO2, 0);
        ui->lblEmergency2LED->setStyleSheet(YELLOW_DO_STYLESHEET);
    }
    else
    {
        if(Emergency2 == 1)
        {
            ui->lblEmergency2->setStyleSheet(GREEN_BUTTON_STYLESHEET);
            ui->lblEmergency2LED->setStyleSheet(DO_GREEN_STYLESHEET);
            setRegisterHIgh(STDP_EMERGENCY_DO2, 1);
        }
        else
        {
            ui->lblEmergency2->setStyleSheet(DEFAULT_STYLESHEET);
            ui->lblEmergency2LED->setStyleSheet(DEFAULT_DO_STYLESHEET);
            setRegisterHIgh(STDP_EMERGENCY_DO2, 0);
        }
    }
    mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, stdpDoval);
}

void stdp::setDataInAO()
{
    //set Ao value

    stdpAoVal[STDP_AO_1] = ((ui->lblAnalogLeftTrailUp->value()) * 2048) / 10.0;
    stdpAoVal[STDP_AO_2] = (ui->lblAnalogLeftTrailDN->value() * 2048) / 10.0;
    stdpAoVal[STDP_AO_3] = (ui->lblAnalogRightTrailUp->value() * 2048) / 10.0;
    stdpAoVal[STDP_AO_4] = (ui->lblAnalogRightTrailDn->value() * 2048) / 10.0;
    qDebug()<< "stdpAoVal[STDP_AO_1] = " <<stdpAoVal[STDP_AO_1];
    qDebug()<< "ui->lblAnalogLeftTrailUp->value() = " <<ui->lblAnalogLeftTrailUp->value();

}



void stdp::sendAoData()
{
    int Aidata = mainAppWin->modbusCommObj->getAiValue(STDP_AI);
    qDebug()<<"AI Timer";
    aiStopCount++;
    aiStartCount++;
//    ui->lblAnalogLeftTrailUp->setValue(25);
//    ui->lblAnalogLeftTrailDN->setValue(45);
//    ui->lblAnalogRightTrailUp->setValue(25);
//    ui->lblAnalogRightTrailDn->setValue(45);
    //set Ai value
    stdpAoVal[STDP_AO_1] = ui->lblAnalogLeftTrailUp->value();
    stdpAoVal[STDP_AO_2] = ui->lblAnalogLeftTrailDN->value();
    stdpAoVal[STDP_AO_3] = ui->lblAnalogRightTrailUp->value();
    stdpAoVal[STDP_AO_4] = ui->lblAnalogRightTrailDn->value();
    if(Aidata == 5)
    {
        mainAppWin->modbusCommObj->sendDoAoData(AI_TRANS_ID, 16, stdpAoVal);
    }
    if(aiStartCount >= AI_TIME_OUT - 30)
    {
        stdpTimer->start(100);
        aiSendTimer->stop();
        aiSend = true;
        aiStopCount = 0;
        //qDebug()<<"if aiStopCount = "<<aiStopCount;
        //qDebug()<<"if aiStartCount = "<<aiStartCount;
        aiStartCount = 0;
    }
    else
    {

    }
}

void stdp::hideCrosss()
{
    for(int i = 0; i < crossContinutyErrorList.count(); i++)
    {
        crossContinutyErrorList.at(i)->hide();
    }
    ui->txtCrossContinuityError->hide();
}

void stdp::addDoStructInList()
{
    STDPdoStructDOstruct.doNum = DEADMAN_STDP_DO;
    doSTDPList.append(STDPdoStructDOstruct);
    STDPdoStructDOstruct.doNum = UNLOCKING_STDP_DO;
    doSTDPList.append(STDPdoStructDOstruct);
    STDPdoStructDOstruct.doNum = GRFD_STDP_DO;
    doSTDPList.append(STDPdoStructDOstruct);
    STDPdoStructDOstruct.doNum = GRRD_STDP_DO;
    doSTDPList.append(STDPdoStructDOstruct);
    STDPdoStructDOstruct.doNum = LIT_STDP_DO;
    doSTDPList.append(STDPdoStructDOstruct);
    STDPdoStructDOstruct.doNum = LCW_UP_STDP_DO;
    doSTDPList.append(STDPdoStructDOstruct);
    STDPdoStructDOstruct.doNum = LCW_DN_STDP_DO;
    doSTDPList.append(STDPdoStructDOstruct);
    STDPdoStructDOstruct.doNum = RCW_UP_STDP_DO;
    doSTDPList.append(STDPdoStructDOstruct);
    STDPdoStructDOstruct.doNum = RCW_DN_STDP_DO;
    doSTDPList.append(STDPdoStructDOstruct);
    STDPdoStructDOstruct.doNum = LS_UP_STDP_DO;
    doSTDPList.append(STDPdoStructDOstruct);
    STDPdoStructDOstruct.doNum = LS_DN_STDP_DO;
    doSTDPList.append(STDPdoStructDOstruct);
    STDPdoStructDOstruct.doNum = RS_UP_STDP_DO;
    doSTDPList.append(STDPdoStructDOstruct);
    STDPdoStructDOstruct.doNum = RS_DN_STDP_DO;
    doSTDPList.append(STDPdoStructDOstruct);
}

void stdp::crossContinutyErrorListappend()
{
    crossContinutyErrorList.clear();
    crossContinutyErrorList.append(ui->ckCrossContinutyError);
    crossContinutyErrorList.append(ui->ckUnlocking);
    crossContinutyErrorList.append(ui->ckGRFD);
    crossContinutyErrorList.append(ui->ckGRRD);
    crossContinutyErrorList.append(ui->ckLIT);
    crossContinutyErrorList.append(ui->ckLCWup);
    crossContinutyErrorList.append(ui->ckLCUdn);
    crossContinutyErrorList.append(ui->ckRCWup);
    crossContinutyErrorList.append(ui->ckRCWdn);
    crossContinutyErrorList.append(ui->ckLSup);
    crossContinutyErrorList.append(ui->ckLSdn);
    crossContinutyErrorList.append(ui->ckRSup);
    crossContinutyErrorList.append(ui->ckRSdn);
}

