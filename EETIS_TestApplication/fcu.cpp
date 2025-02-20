#include "fcu.h"
#include "mainwindow.h"
#include "ui_fcu.h"

extern MainWindow *mainAppWin;

fcu::fcu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fcu)
{
    ui->setupUi(this);
    fcuTimer = new QTimer(this);
    connect(fcuTimer, SIGNAL(timeout()),this, SLOT(startTest()));
    //fcuTimer->start(100);
}

fcu::~fcu()
{
    delete ui;
}

void fcu::checkHarness()
{
    int harnessChkDI1= mainAppWin->modbusCommObj->getDiValue(HARNESS_FCU_CHK_DI1);
    int harnessChkDI2 = mainAppWin->modbusCommObj->getDiValue(HARNESS_FCU_CHK_DI2);

    if(ui->cbHarnessDI1_On->isChecked() == 1)
    {
        ui->lblHarness1LED->setStyleSheet(YELLOW_DO_STYLESHEET);
        mainAppWin->modbusCommObj->setRegisterHIgh(HARNESS_FCU_CHK_DO1, 1,fcuDoval);
    }
    else if(ui->cbHarnessDI1_Off->isChecked() == 1)
    {
        ui->lblHarness1LED->setStyleSheet(DEFAULT_DO_STYLESHEET);
        mainAppWin->modbusCommObj->setRegisterHIgh(HARNESS_FCU_CHK_DO1, 0,fcuDoval);
    }
    else
    {
        if(harnessChkDI1 == 1)
        {
            ui->lblCorrectHDI1->setStyleSheet(GREEN_BUTTON_STYLESHEET);
            if(ui->cbContErrHarness1->isChecked() == 1)
            {
                ui->lblHarness1LED->setStyleSheet(DO_GREEN_STYLESHEET);
                mainAppWin->modbusCommObj->setRegisterHIgh(HARNESS_FCU_CHK_DO1, 0,fcuDoval);
            }
            else
            {
                ui->lblHarness1LED->setStyleSheet(DEFAULT_DO_STYLESHEET);
                mainAppWin->modbusCommObj->setRegisterHIgh(HARNESS_FCU_CHK_DO1, 1,fcuDoval);
            }

        }
        else
        {
            ui->lblCorrectHDI1->setStyleSheet(DEFAULT_BUTTON_STYLESHEET);
            mainAppWin->modbusCommObj->setRegisterHIgh(HARNESS_FCU_CHK_DO1, 0,fcuDoval);
            ui->lblHarness1LED->setStyleSheet(DEFAULT_DO_STYLESHEET);
        }
    }
}

void fcu::startTest()
{
    checkHarness();
}
