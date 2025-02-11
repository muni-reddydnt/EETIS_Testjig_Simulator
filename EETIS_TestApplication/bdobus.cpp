#include "bdobus.h"
#include "mainwindow.h"
#include "ui_bdobus.h"
#include <QThread>


extern MainWindow *mainAppWin;
bdobus::bdobus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bdobus)
{
    ui->setupUi(this);

    ui->ckCrossShellLoading->hide();
    ui->ckCrossEmergencyStop1->hide();
    ui->ckCrossBDOBUSJ19J110_SafetyKeyConnector2->hide();
    ui->ckCrossBDOBUSJ115J116_SafetyKeyConnector->hide();
    for(int i = 0;i<16;i++)
    {
        btnDiEnalbeDisable[i] = true;
    }
    displayUPdata = new QTimer(this);
    connect(displayUPdata, SIGNAL(timeout()),this, SLOT(startTest()));
    //displayUPdata->start(100);

    uiListappend();
    addDiDoStructInList();
}

bdobus::~bdobus()
{
    delete ui;
}

void bdobus::setRegisterHIgh(int bitPosition, bool highLow)
{
    if(bitPosition > 0 && bitPosition < 16)
    {
        bdobusDoval[0] = mainAppWin->modbusCommObj->setBitHigh(bdobusDoval[0],bitPosition,highLow);
    }
    else if(bitPosition  >= 16 && bitPosition  <32)
    {
        bdobusDoval[1] = mainAppWin->modbusCommObj->setBitHigh(bdobusDoval[1],(bitPosition - 16),highLow);
    }
    else if(bitPosition  >= 32 && bitPosition  <48)
    {
        bdobusDoval[2] = mainAppWin->modbusCommObj->setBitHigh(bdobusDoval[2],(bitPosition - 32),highLow);
    }
    else if(bitPosition  >= 48 && bitPosition  <64)
    {
        bdobusDoval[3] = mainAppWin->modbusCommObj->setBitHigh(bdobusDoval[3],(bitPosition - 48),highLow);
    }
}

void bdobus::addDiStructInList()
{
    diBDOBUSList.clear();
    //    BDOBUSteststruct.diNum = BDOBUS_SHELLCHK_DI;
    //    diBDOBUSList.append(BDOBUSteststruct);
    //    BDOBUSteststruct.diNum = BDOBUS_EMERGNCYCHK_DI;
    //    diBDOBUSList.append(BDOBUSteststruct);
    BDOBUSteststruct.diNum = BDOBUSDI1;
    diBDOBUSList.append(BDOBUSteststruct);
    BDOBUSteststruct.diNum = BDOBUSDI2;
    diBDOBUSList.append(BDOBUSteststruct);
    BDOBUSteststruct.diNum = BDOBUSDI3;
    diBDOBUSList.append(BDOBUSteststruct);
    BDOBUSteststruct.diNum = BDOBUSDI4;
    diBDOBUSList.append(BDOBUSteststruct);
    BDOBUSteststruct.diNum = BDOBUSDI5;
    diBDOBUSList.append(BDOBUSteststruct);
    BDOBUSteststruct.diNum = BDOBUSDI6;
    diBDOBUSList.append(BDOBUSteststruct);
    BDOBUSteststruct.diNum = BDOBUSDI7;
    diBDOBUSList.append(BDOBUSteststruct);
    BDOBUSteststruct.diNum = BDOBUSDI8;
    diBDOBUSList.append(BDOBUSteststruct);
    BDOBUSteststruct.diNum = BDOBUSDI9;
    diBDOBUSList.append(BDOBUSteststruct);
    BDOBUSteststruct.diNum = BDOBUSDI10;
    diBDOBUSList.append(BDOBUSteststruct);
}

void bdobus::addDoStructInList()
{
    doBDOBUSList.clear();
    //    BDOBUStestDOstruct.doNum = BDOBUS_SHELLCHK_DO;
    //    doBDOBUSList.append(BDOBUStestDOstruct);
    //    BDOBUStestDOstruct.doNum = BDOBUS_EMERGNCYCHK_DO;
    //    doBDOBUSList.append(BDOBUStestDOstruct);
    BDOBUStestDOstruct.doNum = BDOBUSDO1;
    doBDOBUSList.append(BDOBUStestDOstruct);
    BDOBUStestDOstruct.doNum = BDOBUSDO2;
    doBDOBUSList.append(BDOBUStestDOstruct);
    BDOBUStestDOstruct.doNum = BDOBUSDO3;
    doBDOBUSList.append(BDOBUStestDOstruct);
    BDOBUStestDOstruct.doNum = BDOBUSDO4;
    doBDOBUSList.append(BDOBUStestDOstruct);
    BDOBUStestDOstruct.doNum = BDOBUSDO5;
    doBDOBUSList.append(BDOBUStestDOstruct);
    BDOBUStestDOstruct.doNum = BDOBUSDO6;
    doBDOBUSList.append(BDOBUStestDOstruct);
    BDOBUStestDOstruct.doNum = BDOBUSDO7;
    doBDOBUSList.append(BDOBUStestDOstruct);
    BDOBUStestDOstruct.doNum = BDOBUSDO8;
    doBDOBUSList.append(BDOBUStestDOstruct);
    BDOBUStestDOstruct.doNum = BDOBUSDO9;
    doBDOBUSList.append(BDOBUStestDOstruct);
    BDOBUStestDOstruct.doNum = BDOBUSDO10;
    doBDOBUSList.append(BDOBUStestDOstruct);
}

void bdobus::sefty()
{
    BODOBUSdiStructseftyObj.diNum = BDOBUS_SAFTEY_DI_1;
    diBDOBUSListsefty.append(BODOBUSdiStructseftyObj);
    BODOBUSdiStructseftyObj.diNum = BDOBUS_SAFTEY_DI_2;
    diBDOBUSListsefty.append(BODOBUSdiStructseftyObj);
}

void bdobus::seftyDO()
{
    BDOBUStestDOstructseftyobj.doNum = BDOBUS_SAFTEY_DO_1;
    BODOBUSdoStructseftyList.append(BDOBUStestDOstructseftyobj);
    BDOBUStestDOstructseftyobj.doNum = BDOBUS_SAFTEY_DO_2;
    BODOBUSdoStructseftyList.append(BDOBUStestDOstructseftyobj);
}

void bdobus::addDiDoStructInList()
{
    addDiStructInList();
    addDoStructInList();
    sefty();
    seftyDO();
}

void bdobus::resetAllDisAndDosLabels()
{
    if(BDOBUSDidataList[0].Result == 1)
    {
        for(int i = 0; i< diLabelList.count(); i++)
        {
            diLabelList.at(i)->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
            doLabelList.at(i)->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }

        for(int i = 0; i< safetyConnectorDiLabelList.count(); i++)
        {
            safetyConnectorDiLabelList.at(i)->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
            safetyConnectorDoLabelList.at(i)->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }

    }
}

void bdobus::uiListappend()
{
    diListappend();
    doListappend();
    continutyErrorListappend();
    crossContinutyErrorListappend();
    ckForceDoOnListAppend();
    ckForceDoOnOffListAppend();
}

void bdobus::doListappend()
{
    doLabelList.clear();
    //doLabelList.append(ui->lblShellLoadingLED);
    //doLabelList.append(ui->lblEmergencyStopLED);
    doLabelList.append(ui->lblBDOBUSJ17J21LED);
    doLabelList.append(ui->lblBDOBUSJ18J22LED);
    doLabelList.append(ui->lblBDOBUSJ19J23LED);
    doLabelList.append(ui->lblBDOBUSJ19J110LED);
    doLabelList.append(ui->lblBDOBUSJ110J24LED);
    doLabelList.append(ui->lblBDOBUSJ111J25LED);
    doLabelList.append(ui->lblBDOBUSJ112J26LED);
    doLabelList.append(ui->lblBDOBUSJ113J27LED);
    doLabelList.append(ui->lblBDOBUSJ114J28LED);
    doLabelList.append(ui->lblBDOBUSJ115J29LED);
    //    doLabelList.append(ui->lblBDOBUSJ115J116LED);
    //    doLabelList.append(ui->lblBDOBUSJ116J210LED);
    safetyConnectorDoLabelList.append(ui->lblKeyConnecter1LED);
    safetyConnectorDoLabelList.append(ui->lblKeyConnecter2LED);
}

void bdobus::diListappend()
{
    diLabelList.clear();
    //diLabelList.append(ui->lblShellLoading);
    //diLabelList.append(ui->lblEmergencyStop);
    diLabelList.append(ui->lblBDOBUSJ17J21);
    diLabelList.append(ui->lblBDOBUSJ18J22);
    diLabelList.append(ui->lblBDOBUSJ19J23);
    diLabelList.append(ui->lblBDOBUSJ19J110);
    diLabelList.append(ui->lblBDOBUSJ110J24);
    diLabelList.append(ui->lblBDOBUSJ111J25);
    diLabelList.append(ui->lblBDOBUSJ112J26);
    diLabelList.append(ui->lblBDOBUSJ113J27);
    diLabelList.append(ui->lblBDOBUSJ114J28);
    diLabelList.append(ui->lblBDOBUSJ115J29);
    //    diLabelList.append(ui->lblBDOBUSJ115J116);
    //    diLabelList.append(ui->lblBDOBUSJ116J210);
    safetyConnectorDiLabelList.append(ui->lblKeyConnecter1);
    safetyConnectorDiLabelList.append(ui->lblKeyConnecter2);
}

void bdobus::ckForceDoOnListAppend()
{
    do_OnCbList.clear();
    safetyConnecotdo_OnCbList.clear();
    do_OnCbList.append(ui->cbJ17ToJ21_On);
    do_OnCbList.append(ui->cbJ18ToJ22_On);
    do_OnCbList.append(ui->cbJ19ToJ23_On);
    do_OnCbList.append(ui->cbJ19ToJ110_On);
    do_OnCbList.append(ui->cbJ110ToJ24_On);
    do_OnCbList.append(ui->cbJ111ToJ25_On);
    do_OnCbList.append(ui->cbJ112ToJ26_On);
    do_OnCbList.append(ui->cbJ113ToJ27_On);
    do_OnCbList.append(ui->cbJ114ToJ28_On);
    do_OnCbList.append(ui->cbJ115ToJ29_On);
    safetyConnecotdo_OnCbList.append(ui->ckSafetyKeyConnector1_On);
    safetyConnecotdo_OnCbList.append(ui->ckSafetyKeyConnector2_On);
}

void bdobus::ckForceDoOnOffListAppend()
{
    do_OffCbList.clear();
    do_OffCbList.append(ui->cbJ17ToJ21_Off);
    do_OffCbList.append(ui->cbJ18ToJ22_Off);
    do_OffCbList.append(ui->cbJ19ToJ23_Off);
    do_OffCbList.append(ui->cbJ19ToJ110_Off);
    do_OffCbList.append(ui->cbJ110ToJ24_Off);
    do_OffCbList.append(ui->cbJ111ToJ25_Off);
    do_OffCbList.append(ui->cbJ112ToJ26_Off);
    do_OffCbList.append(ui->cbJ113ToJ27_Off);
    do_OffCbList.append(ui->cbJ114ToJ28_Off);
    do_OffCbList.append(ui->cbJ115ToJ29_Off);
    safetyConnecotdo_OffCbList.append(ui->ckSafetyKeyConnector1_Off);
    safetyConnecotdo_OffCbList.append(ui->ckSafetyKeyConnector2_Off);
}

void bdobus::continutyErrorListappend()
{
    //continutyErrorList.append(ui->ckShellLoading);
    //continutyErrorList.append(ui->ckEmergencyStop);
    continutyErrorList.append(ui->ckBDOBUSJ17J21);
    continutyErrorList.append(ui->ckBDOBUSJ18J22);
    continutyErrorList.append(ui->ckBDOBUSJ19J23);
    continutyErrorList.append(ui->ckBDOBUSJ19J110);
    continutyErrorList.append(ui->ckBDOBUSJ110J24);
    continutyErrorList.append(ui->ckBDOBUSJ111J25);
    continutyErrorList.append(ui->ckBDOBUSJ112J26);
    continutyErrorList.append(ui->ckBDOBUSJ113J27);
    continutyErrorList.append(ui->ckBDOBUSJ114J28);
    continutyErrorList.append(ui->ckBDOBUSJ115J29);
    safetyContinutyErrorList.append(ui->ckcontinuty_KeyConnecter1);
    safetyContinutyErrorList.append(ui->ckcontinuty_KeyConnecter2);
    //    continutyErrorList.append(ui->ckBDOBUSJ115J116);
    //    continutyErrorList.append(ui->ckBDOBUSJ116J210);
    //continutyErrorList.append(ui->ckHarnessContinutyError);
}

void bdobus::crossContinutyErrorListappend()
{
    //    crossContinutyErrorList.append(ui->ckCrossShellLoading);
    //    crossContinutyErrorList.append(ui->ckCrossEmergencyStop);
    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ17J21);
    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ18J22);
    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ19J23);
    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ19J110);
    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ110J24);
    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ111J25);
    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ112J26);
    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ113J27);
    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ114J28);
    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ115J29);
    //    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ115J116);
    //    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ116J210);
}

void bdobus::startTest()
{
    qDebug()<<"hi";
    BDOBUSDidataList.clear();
    BODOBUSDiSeftydataStructlist.clear();
    for(int i=0 ;i <diBDOBUSList.count();i++)
    {
        BDOBUSDiResultStruct.Result = mainAppWin->modbusCommObj->getDiValue(diBDOBUSList.at(i).diNum);
        BDOBUSDidataList.append(BDOBUSDiResultStruct);

        //qDebug()<<"DI "<<i<<":"<<BDOBUSDiResultStruct.Result;
    }

    for(int i=0 ;i <diBDOBUSListsefty.count();i++)
    {
        BODOBUSDiSeftydataStructObj.Result = mainAppWin->modbusCommObj->getDiValue(diBDOBUSListsefty.at(i).diNum);
        BODOBUSDiSeftydataStructlist.append(BODOBUSDiSeftydataStructObj);
    }


    //Check if correct harness is connected
    processHarnessDiDO();

    //shell and emergency
    ProcessShellEmergencyDiDO();

    //DI-DO test
    processDiToDO();





    //    processShellLoadingEmgncyStop();
#if 0
    qDebug()<<"BDOBUSDidataList.length() = "<<BDOBUSDidataList.length();
    qDebug()<<"BDOBUSDidataList.at(0).Result = "<<BDOBUSDidataList.at(0).Result;
    qDebug()<<"BDOBUSDidataList.at(1).Result = "<<BDOBUSDidataList.at(1).Result;
    qDebug()<<"BDOBUSDidataList.at(2).Result = "<<BDOBUSDidataList.at(2).Result;
    qDebug()<<"BDOBUSDidataList.at(3).Result = "<<BDOBUSDidataList.at(3).Result;
    qDebug()<<"BDOBUSDidataList.at(4).Result = "<<BDOBUSDidataList.at(4).Result;
    qDebug()<<"BDOBUSDidataList.at(5).Result = "<<BDOBUSDidataList.at(5).Result;
    qDebug()<<"BDOBUSDidataList.at(6).Result = "<<BDOBUSDidataList.at(6).Result;
    qDebug()<<"BDOBUSDidataList.at(7).Result = "<<BDOBUSDidataList.at(7).Result;
    qDebug()<<"BDOBUSDidataList.at(8).Result = "<<BDOBUSDidataList.at(8).Result;
    qDebug()<<"BDOBUSDidataList.at(9).Result = "<<BDOBUSDidataList.at(9).Result;
#endif
}

void bdobus::processDiToDO()
{
    // resetAllDisAndDosLabels();
    if(flag == false)
    {
        //qDebug()<< "flag = "<< flag ;

        for (int i = 0; i < BDOBUSDidataList.count(); i++)
        {

            if(do_OnCbList.at(i)->isChecked() == 1)
            {
                setRegisterHIgh(doBDOBUSList.at(i).doNum, 1);
                doLabelList[i]->setStyleSheet(YELLOW_DO_STYLESHEET);
            }
            else if(do_OffCbList.at(i)->isChecked() == 1)
            {
                setRegisterHIgh(doBDOBUSList.at(i).doNum, 0);
                doLabelList[i]->setStyleSheet(DEFAULT_DO_STYLESHEET);
            }
            else
            {
                if(BDOBUSDidataList[i].Result == 1 )
                {
                    //qDebug()<< "i = "<< i ;
                    tempSafteyConnectorCheck = i;
                    //memset(&bdobusDoval, 0,sizeof(bdobusDoval));
                    if(crossContinutyErrorList.at(i)->isChecked() == 1)   //1 in insted
                    {
                        setRegisterHIgh(doBDOBUSList.at(i).doNum, 1);
                        doLabelList[i]->setStyleSheet(DO_GREEN_STYLESHEET);

                        if(i  <= doBDOBUSList.count() - 3)
                        {
                            setRegisterHIgh(doBDOBUSList.at(i + 1).doNum, 1);
                            setRegisterHIgh(doBDOBUSList.at(i + 2).doNum, 1);
                            doLabelList[i + 1]->setStyleSheet(DO_GREEN_STYLESHEET);
                            doLabelList[i + 2]->setStyleSheet(DO_GREEN_STYLESHEET);
                        }
                        else if(i == doBDOBUSList.count() - 2)
                        {
                            setRegisterHIgh(doBDOBUSList.at(i + 1).doNum, 1);
                            setRegisterHIgh(doBDOBUSList.at(0).doNum, 1);
                            doLabelList[i + 1]->setStyleSheet(DO_GREEN_STYLESHEET);
                            doLabelList[0]->setStyleSheet(DO_GREEN_STYLESHEET);
                        }
                        else if(i == /*9*/doBDOBUSList.count() - 1)
                        {
                            setRegisterHIgh(doBDOBUSList.at(0).doNum, 1);
                            setRegisterHIgh(doBDOBUSList.at(1).doNum, 1);
                            doLabelList[0]->setStyleSheet(DO_GREEN_STYLESHEET);
                            doLabelList[1]->setStyleSheet(DO_GREEN_STYLESHEET);
                        }
                        diLabelList[i]->setStyleSheet(DI_RECEIVED_STYLESHEET);
                    }

                    if(continutyErrorList.at(i)->isChecked() == 1)
                    {
                        setRegisterHIgh(doBDOBUSList.at(i).doNum, 0);
                        doLabelList[i]->setStyleSheet(DEFAULT_DO_STYLESHEET);
                        diLabelList[i]->setStyleSheet(DI_RECEIVED_STYLESHEET);
                    }
                    if(crossContinutyErrorList.at(i)->isChecked() != 1 && continutyErrorList.at(i)->isChecked() != 1)
                    {

                        setRegisterHIgh(doBDOBUSList.at(i).doNum, 1);
                        doLabelList[i]->setStyleSheet(DO_GREEN_STYLESHEET);
                        diLabelList[i]->setStyleSheet(DI_RECEIVED_STYLESHEET);
                    }
                    //setRegisterHIgh(doBDOBUSList.at(i).doNum, 0);

                }
                else
                {
                    //qDebug()<<"doBDOBUSList :"<<doBDOBUSList.at(i).doNum<<" i:"<<i;
                    //memset(&bdobusDoval, 0,sizeof(bdobusDoval));
                    setRegisterHIgh(doBDOBUSList.at(i).doNum, 0);
                    doLabelList[i]->setStyleSheet(DEFAULT_DO_STYLESHEET);
                    diLabelList[i]->setStyleSheet(DEFAULT_STYLESHEET);
                }
            }
            mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bdobusDoval);
        }
    }

    // After the loop, explicitly turn off the last DO (index 9)

    if(tempSafteyConnectorCheck >= 9 /*&& BODOBUSDiSeftydataStructlist[0].Result == 1*/)
    {
        int temp = 0;
        temp = BODOBUSDiSeftydataStructObj.Result = mainAppWin->modbusCommObj->getDiValue(BDOBUS_SAFTEY_DI_1);
        //        memset(&bdobusDoval, 0,sizeof(bdobusDoval));
        flag =true;
//        if(temp == 1)
//        {
            //setRegisterHIgh(doBDOBUSList.at(9).doNum, 0);
            //memset(&bdobusDoval, 0,sizeof(bdobusDoval));
            safetyConnectorTest();
        //}

    }
}

void bdobus::processHarnessDiDO()
{
    if(ui->ckHarnessForceDoOn->isChecked() == 1)
    {
        setRegisterHIgh(HARNESS_BDOBUS_CHK_DO1, 1);
        ui->lblHarnessLED->setStyleSheet(YELLOW_DO_STYLESHEET);
    }
    else if(ui->ckHarnessForceDoOff->isChecked() == 1)
    {
        setRegisterHIgh(HARNESS_BDOBUS_CHK_DO1, 0);
        ui->lblHarnessLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
    }
    else
    {
        if(checkCorrectHarness() == 1)
        {
            if(ui->ckHarnessContinutyError->isChecked() != 1)
            {
                setRegisterHIgh(HARNESS_BDOBUS_CHK_DO1, 1);
                //bdobusDoval[2]  = mainAppWin->modbusCommObj->setBitHigh(bdobusDoval[2],(HARNESS_BDOBUS_CHK_DO1 - 32),1);
                ui->lblHarness->setStyleSheet(DI_RECEIVED_STYLESHEET);
                ui->lblHarnessLED->setStyleSheet(DO_GREEN_STYLESHEET);
            }
            else if(ui->ckHarnessContinutyError->isChecked() == 1)
            {
                setRegisterHIgh(HARNESS_BDOBUS_CHK_DO1, 0);
                //bdobusDoval[0]  = mainAppWin->modbusCommObj->setBitHigh(bdobusDoval[0],(HARNESS_BDOBUS_CHK_DO1),0);
                ui->lblHarness->setStyleSheet(DEFAULT_STYLESHEET);
                ui->lblHarnessLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
            }
        }
        else
        {
            setRegisterHIgh(HARNESS_BDOBUS_CHK_DO1, 0);
            ui->lblHarness->setStyleSheet(DEFAULT_STYLESHEET);
            ui->lblHarnessLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
    }
    mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bdobusDoval);
}

void bdobus::ProcessShellEmergencyDiDO()
{
    int emergency1 = mainAppWin->modbusCommObj->getDiValue(BDOBUS_EMERGNCYCHK_DI1);
    int emergency2 = mainAppWin->modbusCommObj->getDiValue(BDOBUS_EMERGNCYCHK_DI2);
    int shellLoading  = mainAppWin->modbusCommObj->getDiValue(BDOBUS_SHELLCHK_DI);

    //shell loading
    if(ui->cbShellLoading_On->isChecked() == 1)
    {
        setRegisterHIgh(BDOBUS_SHELLCHK_DO, 1);
        ui->lblShellLoadingLED->setStyleSheet(YELLOW_DO_STYLESHEET);
    }
    else if(ui->cbShellLoading_Off->isChecked() == 1)
    {
        setRegisterHIgh(BDOBUS_SHELLCHK_DO, 0);
        ui->lblShellLoadingLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
    }
    else
    {
        if(shellLoading == 1)
        {
            if(ui->ckShellLoading->isChecked() != 1)
            {
                ui->lblShellLoading->setStyleSheet(DI_RECEIVED_STYLESHEET);
                ui->lblShellLoadingLED->setStyleSheet(DO_GREEN_STYLESHEET);
                setRegisterHIgh(BDOBUS_SHELLCHK_DO, 1);
            }
            else if(ui->ckShellLoading->isChecked() == 1)
            {
                ui->lblShellLoadingLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
                setRegisterHIgh(BDOBUS_SHELLCHK_DO, 0);
            }
        }
        else
        {
            ui->lblShellLoadingLED->setStyleSheet(DEFAULT_DO_STYLESHEET);
            setRegisterHIgh(BDOBUS_SHELLCHK_DO, 0);
            ui->lblShellLoading->setStyleSheet(DEFAULT_STYLESHEET);
        }
    }


    //Emergency stop1
    if(ui->cbEmgStop1_On->isChecked() == 1)
    {
        ui->lblEmergencyStop1LED->setStyleSheet(YELLOW_DO_STYLESHEET);
        setRegisterHIgh(BDOBUS_EMERGNCYCHK_DO1, 1);
    }
    else if(ui->cbEmgStop1_Off->isChecked() == 1)
    {
        ui->lblEmergencyStop1LED->setStyleSheet(DEFAULT_DO_STYLESHEET);
        setRegisterHIgh(BDOBUS_EMERGNCYCHK_DO1, 0);
    }
    else
    {
        if(emergency1 == 1)
        {
            if(ui->ckEmergencyStop1->isChecked() != 1)
            {
                ui->lblEmergencyStop1->setStyleSheet(DI_RECEIVED_STYLESHEET);
                ui->lblEmergencyStop1LED->setStyleSheet(DO_GREEN_STYLESHEET);
                setRegisterHIgh(BDOBUS_EMERGNCYCHK_DO1, 1);
            }
            else if(ui->ckEmergencyStop1->isChecked() == 1)
            {
                ui->lblEmergencyStop1LED->setStyleSheet(DEFAULT_DO_STYLESHEET);
                setRegisterHIgh(BDOBUS_EMERGNCYCHK_DO1, 0);
            }
        }
        else
        {
            ui->lblEmergencyStop1LED->setStyleSheet(DEFAULT_DO_STYLESHEET);
            setRegisterHIgh(BDOBUS_EMERGNCYCHK_DO1, 0);
            ui->lblEmergencyStop1->setStyleSheet(DEFAULT_STYLESHEET);
        }
    }

    //Emergency stop2
    if(ui->cbEmgStop2_On->isChecked() == 1)
    {
        ui->lblEmergencyStop2LED->setStyleSheet(YELLOW_DO_STYLESHEET);
        setRegisterHIgh(BDOBUS_EMERGNCYCHK_DO2, 1);
    }
    else if(ui->cbEmgStop2_Off->isChecked() == 1)
    {
        ui->lblEmergencyStop2LED->setStyleSheet(DEFAULT_DO_STYLESHEET);
        setRegisterHIgh(BDOBUS_EMERGNCYCHK_DO2, 0);
    }
    else
    {
        if(emergency2 == 1)
        {
            if(ui->ckEmergencyStop2->isChecked() != 1)
            {
                ui->lblEmergencystop2->setStyleSheet(DI_RECEIVED_STYLESHEET);
                ui->lblEmergencyStop2LED->setStyleSheet(DO_GREEN_STYLESHEET);
                setRegisterHIgh(BDOBUS_EMERGNCYCHK_DO2, 1);
            }
            else if(ui->ckEmergencyStop1->isChecked() == 1)
            {
                ui->lblEmergencyStop2LED->setStyleSheet(DEFAULT_DO_STYLESHEET);
                setRegisterHIgh(BDOBUS_EMERGNCYCHK_DO2, 0);
            }
        }
        else
        {
            ui->lblEmergencyStop2LED->setStyleSheet(DEFAULT_DO_STYLESHEET);
            setRegisterHIgh(BDOBUS_EMERGNCYCHK_DO2, 0);
            ui->lblEmergencystop2->setStyleSheet(DEFAULT_STYLESHEET);
        }
    }
    mainAppWin->modbusCommObj->sendDoAoData(DI_TRANS_ID,4, bdobusDoval);
}


void bdobus::safetyConnectorTest()
{
    for (int i = 0; i < BODOBUSDiSeftydataStructlist.count(); i++)
        {
            qDebug()<< "i : "<< i;
            //memset(&bdobusDoval, 0,sizeof(bdobusDoval));
            if(safetyConnecotdo_OnCbList.at(i)->isChecked() == 1)
            {
                setRegisterHIgh(BODOBUSdoStructseftyList.at(i).doNum, 1);
                safetyConnectorDoLabelList.at(i)->setStyleSheet(YELLOW_DO_STYLESHEET);
            }
            else if(safetyConnecotdo_OffCbList.at(i)->isChecked() == 1)
            {
                setRegisterHIgh(BODOBUSdoStructseftyList.at(i).doNum, 0);
                safetyConnectorDoLabelList.at(i)->setStyleSheet(DEFAULT_DO_STYLESHEET);
            }
            else
            {
                if(BODOBUSDiSeftydataStructlist[i].Result == 1)
                {
                    memset(&bdobusDoval, 0,sizeof(bdobusDoval));
                    if(safetyContinutyErrorList.at(i)->isChecked() == 1)
                    {
                        safetyConnectorDiLabelList.at(i)->setStyleSheet(DEFAULT_STYLESHEET);
                        setRegisterHIgh(BODOBUSdoStructseftyList.at(i).doNum, 0);
                        safetyConnectorDoLabelList.at(i)->setStyleSheet(DEFAULT_DO_STYLESHEET);
                    }
                    else
                    {
                        if(i == 1)
                        {
                            memset(&bdobusDoval, 0,sizeof(bdobusDoval));
                        }
                        safetyConnectorDiLabelList.at(i)->setStyleSheet(DI_RECEIVED_STYLESHEET);
                        setRegisterHIgh(BODOBUSdoStructseftyList.at(i).doNum, 1);
                        safetyConnectorDoLabelList.at(i)->setStyleSheet(DO_GREEN_STYLESHEET);
                    }
                }
                else
                {
                    //memset(&bdobusDoval, 0,sizeof(bdobusDoval));
                    safetyConnectorDiLabelList.at(i)->setStyleSheet(DEFAULT_STYLESHEET);
                    //setRegisterHIgh(BODOBUSdoStructseftyList.at(i).doNum, 0);
                    safetyConnectorDoLabelList.at(i)->setStyleSheet(DEFAULT_DO_STYLESHEET);
                }
            }
        }
}


int bdobus::checkCorrectHarness()
{
    int value1= mainAppWin->modbusCommObj->getDiValue(HARNESS_BDOBUS_CHK_DI1);
    return (value1);
}
