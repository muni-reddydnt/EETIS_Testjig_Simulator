#include "bdobus.h"
#include "ui_bdobus.h"

bdobus::bdobus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bdobus)
{
    ui->setupUi(this);
    modbusCommObj = new modbusComm(this);
    //modbusCommObj->status = 0;
    //btnBDOBUSJ17J21 = true;
    ui->ckCrossShellLoading->hide();
    ui->ckCrossEmergencyStop->hide();
    for(int i = 0;i<16;i++)
    {
        btnDiEnalbeDisable[i] = true;
    }
    displayUPdata = new QTimer(this);
    connect(displayUPdata, SIGNAL(timeout()),this, SLOT(update()));
    displayUPdata->start(100);

    uiListappend();
    addDiDoStructInList();
}

bdobus::~bdobus()
{
    delete ui;
}

int bdobus::setBitHigh(int val, int bitPosition, bool highLow)
{
    if (highLow) {

        return val |= (1 << bitPosition);
    } else {
        return val &= ~(1 << bitPosition);
    }
}

void bdobus::setRegisterHIgh(int bitPosition, bool highLow)
{
    if(bitPosition > 0 && bitPosition < 16)
    {
        modbusCommObj->dival[0] = setBitHigh(modbusCommObj->dival[0],bitPosition,highLow);
    }
    else if(bitPosition  >= 16 && bitPosition  <32)
    {
        modbusCommObj->dival[1] = setBitHigh(modbusCommObj->dival[1],(bitPosition - 16),highLow);
    }
    else if(bitPosition  >= 32 && bitPosition  <48)
    {
        modbusCommObj->dival[2] = setBitHigh(modbusCommObj->dival[2],(bitPosition - 32),highLow);
    }
    else if(bitPosition  >= 48 && bitPosition  <64)
    {
        modbusCommObj->dival[3] = setBitHigh(modbusCommObj->dival[3],(bitPosition - 48),highLow);
    }
}


void bdobus::addDiStructInList()
{
    diBDOBUSList.clear();
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
    //    BDOBUSteststruct.diNum = HARNESS_BDOBUS_CHK_DI1;
    //    diBDOBUSList.append(BDOBUSteststruct);
    BDOBUSteststruct.diNum = BDOBUS_DI_SHELLCHK;
    diBDOBUSList.append(BDOBUSteststruct);
    BDOBUSteststruct.diNum = BDOBUS_DI_EMERGNCYCHK;
    diBDOBUSList.append(BDOBUSteststruct);
}

void bdobus::addDoStructInList()
{
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

    //    BDOBUStestDOstruct.doNum = HARNESS_BDOBUS_CHK_DO1;
    //    doBDOBUSList.append(BDOBUStestDOstruct);

    BDOBUStestDOstruct.doNum = BDOBUS_DO_SHELLCHK;
    doBDOBUSList.append(BDOBUStestDOstruct);
    BDOBUStestDOstruct.doNum = BDOBUS_DO_EMERGNCYCHK;
    doBDOBUSList.append(BDOBUStestDOstruct);
}

void bdobus::addDiDoStructInList()
{
    addDiStructInList();
    addDoStructInList();
}

void bdobus::resetAllDisAndDos()
{
    if(BDOBUSDidataList[0].Result == 1)
    {
        for(int i = 0; i< diLabelList.count(); i++)
        {
            diLabelList.at(i)->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
            doLabelList.at(i)->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
    }
}

void bdobus::uiListappend()
{
    diListappend();
    doListappend();
    continutyErrorListappend();
    crossContinutyErrorListappend();
}

void bdobus::doListappend()
{
    doLabelList.clear();
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
    doLabelList.append(ui->lblShellLoadingLED);
    doLabelList.append(ui->lblEmergencyStopLED);
    //    doLabelList.append(ui->lblBDOBUSJ115J116LED);
    //    doLabelList.append(ui->lblBDOBUSJ116J210LED);
}

void bdobus::diListappend()
{
    diLabelList.clear();
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
    diLabelList.append(ui->lblShellLoading);
    diLabelList.append(ui->lblEmergencyStop);
    //    diLabelList.append(ui->lblBDOBUSJ115J116);
    //    diLabelList.append(ui->lblBDOBUSJ116J210);
}

void bdobus::continutyErrorListappend()
{
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
    continutyErrorList.append(ui->ckShellLoading);
    continutyErrorList.append(ui->ckEmergencyStop);
    //    continutyErrorList.append(ui->ckBDOBUSJ115J116);
    //    continutyErrorList.append(ui->ckBDOBUSJ116J210);
    //continutyErrorList.append(ui->ckHarnessContinutyError);
}

void bdobus::crossContinutyErrorListappend()
{
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
    crossContinutyErrorList.append(ui->ckCrossShellLoading);
    crossContinutyErrorList.append(ui->ckCrossEmergencyStop);
    //    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ115J116);
    //    crossContinutyErrorList.append(ui->ckCrossBDOBUSJ116J210);
}



void bdobus::update()
{
    BDOBUSDidataList.clear();
    modbusCommObj->transactionId = DI_TRANS_ID;
    for(int i=0 ;i <diBDOBUSList.count();i++)
    {
        BDOBUSDiResultStruct.Result = modbusCommObj->getDiValue(diBDOBUSList.at(i).diNum);
        BDOBUSDidataList.append(BDOBUSDiResultStruct);
    }
    processDiToDO();
    processHarnessDiDO();
    if(modbusCommObj->startSendData == 1)
    {
        modbusCommObj->sendData();
    }
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

    memset(&modbusCommObj->dival[0], 0 , sizeof(modbusCommObj->dival));
    resetAllDisAndDos();
    for (int i = 0; i < BDOBUSDidataList.count(); i++)
    {
        if(BDOBUSDidataList[i].Result == 1 && crossContinutyErrorList.at(i)->isChecked() == 1)
        {
            setRegisterHIgh(doBDOBUSList.at(i).doNum, 1);
            doLabelList[i]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
            if(i  < doBDOBUSList.count() - 4)
            {
                setRegisterHIgh(doBDOBUSList.at(i + 1).doNum, 1);
                setRegisterHIgh(doBDOBUSList.at(i + 2).doNum, 1);
                doLabelList[i + 1]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
                doLabelList[i + 2]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
            }
            else if(i == doBDOBUSList.count() - 3)
            {
                setRegisterHIgh(doBDOBUSList.at(i + 1).doNum, 1);
                setRegisterHIgh(doBDOBUSList.at(0).doNum, 1);
                doLabelList[i + 1]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
                doLabelList[0]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
            }
            else if(i == doBDOBUSList.count() - 2)
            {
                setRegisterHIgh(doBDOBUSList.at(0).doNum, 1);
                setRegisterHIgh(doBDOBUSList.at(1).doNum, 1);
                doLabelList[0]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
                doLabelList[1]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
            }
            diLabelList[i]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        }

        if(BDOBUSDidataList[i].Result == 1 && continutyErrorList.at(i)->isChecked() == 1)
        {
            setRegisterHIgh(doBDOBUSList.at(i).doNum, 0);
            doLabelList[i]->setStyleSheet("QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}");
            diLabelList[i]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        }

        if(BDOBUSDidataList[i].Result == 1  && crossContinutyErrorList.at(i)->isChecked() != 1 && continutyErrorList.at(i)->isChecked() != 1)
        {
            setRegisterHIgh(doBDOBUSList.at(i).doNum, 1);
            doLabelList[i]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
            diLabelList[i]->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        }
    }
}



void bdobus::processHarnessDiDO()
{
    if(checkCorrectHarness() == 1 && ui->ckHarnessContinutyError->isChecked() != 1)
    {
        // memset(&modbusCommObj->dival[0], 0 , sizeof(modbusCommObj->dival));
        modbusCommObj->dival[0]  = setBitHigh(modbusCommObj->dival[0],(HARNESS_BDOBUS_CHK_DO1),1);
        ui->lblHarness->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        ui->lblHarnessLED->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
    }
    else if(checkCorrectHarness() == 1 && ui->ckHarnessContinutyError->isChecked() == 1)
    {
        //memset(&modbusCommObj->dival[0], 0 , sizeof(modbusCommObj->dival));
        modbusCommObj->dival[0]  = setBitHigh(modbusCommObj->dival[0],(HARNESS_BDOBUS_CHK_DO1),0);
        ui->lblHarness->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        ui->lblHarnessLED->setStyleSheet("QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}");
    }
    else
    {
        //memset(&modbusCommObj->dival[0], 0 , sizeof(modbusCommObj->dival));
        modbusCommObj->dival[0]  = setBitHigh(modbusCommObj->dival[0],(HARNESS_BDOBUS_CHK_DO1),0);
        ui->lblHarness->setStyleSheet("QLabel { color : white; background-color : rgb(233, 69, 69); border-radius:5px;}");
        ui->lblHarnessLED->setStyleSheet("QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}");
    }
}

void bdobus::processShellLoadingEmgncyStop()
{
    //shell loading
    if(modbusCommObj->receivDIs[BDOBUS_DI_SHELLCHK] == 1 && ui->ckShellLoading->isChecked() != 1)
    {
        memset(&modbusCommObj->dival[0], 0 , sizeof(modbusCommObj->dival));
        modbusCommObj->dival[0]  = setBitHigh(modbusCommObj->dival[0],(BDOBUS_DO_SHELLCHK),1);
        ui->lblShellLoading->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        ui->lblShellLoadingLED->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
    }
    else if(modbusCommObj->receivDIs[BDOBUS_DI_SHELLCHK] == 1 && ui->ckShellLoading->isChecked() == 1)
    {
        memset(&modbusCommObj->dival[0], 0 , sizeof(modbusCommObj->dival));
        modbusCommObj->dival[0]  = setBitHigh(modbusCommObj->dival[0],(BDOBUS_DO_SHELLCHK),0);
        ui->lblShellLoading->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        ui->lblShellLoadingLED->setStyleSheet("QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}");
    }
    else
    {
        memset(&modbusCommObj->dival[0], 0 , sizeof(modbusCommObj->dival));
        modbusCommObj->dival[0]  = setBitHigh(modbusCommObj->dival[0],(BDOBUS_DO_SHELLCHK),0);
        ui->lblShellLoading->setStyleSheet("QLabel { color : white; background-color : rgb(233, 69, 69); border-radius:5px;}");
        ui->lblShellLoadingLED->setStyleSheet("QLabel { color : white; background-color : rgb(233, 69, 69); border-radius:15px;}");
    }





    //Shell loading
    if(modbusCommObj->receivDIs[BDOBUS_DI_SHELLCHK] == 1 && ui->ckEmergencyStop->isChecked() != 1 )
    {
        memset(&modbusCommObj->dival[0], 0 , sizeof(modbusCommObj->dival));
        ui->lblShellLoading->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        //modbusCommObj->dival[0]  = setBitHigh(modbusCommObj->dival[0],(BDOBUS_DO_SHELLCHK),1);
        setRegisterHIgh(BDOBUS_DO_SHELLCHK, 1);
        ui->lblShellLoadingLED->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
    }
    else
    {
        memset(&modbusCommObj->dival[0], 0 , sizeof(modbusCommObj->dival));
        ui->lblShellLoading->setStyleSheet("QLabel { color : white; background-color : rgb(233, 69, 69); border-radius:5px;}");
        // modbusCommObj->dival[0]  = setBitHigh(modbusCommObj->dival[0],(BDOBUS_DO_SHELLCHK),0);
        setRegisterHIgh(BDOBUS_DO_SHELLCHK, 0);
        ui->lblShellLoadingLED->setStyleSheet("QLabel { color : white; background-color : rgb(233, 69, 69); border-radius:15px;}");

    }


    //Emergency stop
    if(modbusCommObj->receivDIs[BDOBUS_DI_EMERGNCYCHK] == 1)
    {
        //qDebug()<<"Shell Loading true";
        memset(&modbusCommObj->dival[0], 0 , sizeof(modbusCommObj->dival));
        ui->lblEmergencyStop->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:5px;}");
        //modbusCommObj->dival[0]  = setBitHigh(modbusCommObj->dival[0],(BDOBUS_DI_EMERGNCYCHK),1);
        setRegisterHIgh(BDOBUS_DO_EMERGNCYCHK, 1);
        ui->lblEmergencyStopLED->setStyleSheet("QLabel { color : white; background-color : rgb(73, 202, 66); border-radius:15px;}");
    }
    else
    {
        memset(&modbusCommObj->dival[0], 0 , sizeof(modbusCommObj->dival));
        ui->lblEmergencyStop->setStyleSheet("QLabel { color : white; background-color : rgb(233, 69, 69); border-radius:5px;}");
        //modbusCommObj->dival[0]  = setBitHigh(modbusCommObj->dival[0],(BDOBUS_DI_EMERGNCYCHK),0);
        setRegisterHIgh(BDOBUS_DO_EMERGNCYCHK, 0);
        ui->lblEmergencyStopLED->setStyleSheet("QLabel { color : white; background-color : rgb(233, 69, 69); border-radius:15px;}");

    }

}


//check box enable disable
void bdobus::processEnableDisableCkError()
{
    for(int i = 0; i<13; i++)
    {
        if(continutyErrorList.at(i)->isChecked() == 1)
        {
            crossContinutyErrorList.at(i)->setEnabled(false);
        }
        else if(crossContinutyErrorList.at(i)->isChecked() == 1)
        {
            continutyErrorList.at(i)->setEnabled(false);
        }

    }

}




int bdobus::checkCorrectHarness()
{

    int value1= modbusCommObj->getDiValue(HARNESS_BDOBUS_CHK_DI1);


    // plcCommObj->setDoValue(HARNESS_BDOBUS_CHK_DO1,LOW);
    return (value1);
}
