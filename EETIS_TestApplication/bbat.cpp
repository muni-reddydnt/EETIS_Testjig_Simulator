#include "bbat.h"
#include "ui_bbat.h"

BBAT::BBAT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BBAT)
{
    ui->setupUi(this);
}

BBAT::~BBAT()
{
    delete ui;
}

void BBAT::addDiStructInList()
{
    diBBATList.clear();
    BBATresultList.clear();
    BBATteststruct.diNum = BBATDO1;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO2;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO3;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO4;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO5;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO6;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO7;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO8;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO9;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO10;
    diBBATList.append(BBATteststruct);
    BBATresultList.clear();
    BBATteststruct.diNum = BBATDO11;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO12;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO13;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO14;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO15;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO16;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO17;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO18;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO19;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO20;
    diBBATList.append(BBATteststruct);


    BBATteststruct.diNum = BBATDO1_1;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_2;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_3;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_4;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_5;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_6;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_7;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_8;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_9;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_10;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_11;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_12;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_13;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_14;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_15;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_16;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_17;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_18;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_19;
    diBBATList.append(BBATteststruct);
    BBATteststruct.diNum = BBATDO1_20;
    diBBATList.append(BBATteststruct);




//    BBATtestDOstruct.doNum = BDOBUSDO1;
//    doBBATList.append(BDOBUStestDOstruct);
//    BBATtestDOstruct.doNum = BDOBUSDO2;
//    doBBATList.append(BDOBUStestDOstruct);
//    BBATtestDOstruct.doNum = BDOBUSDO3;
//    doBBATList.append(BDOBUStestDOstruct);
//    BBATtestDOstruct.doNum = BDOBUSDO4;
//    doBBATList.append(BDOBUStestDOstruct);
//    BBATtestDOstruct.doNum = BDOBUSDO5;
//    doBBATList.append(BDOBUStestDOstruct);
//    BBATtestDOstruct.doNum = BDOBUSDO6;
//    doBBATList.append(BDOBUStestDOstruct);
//    BBATtestDOstruct.doNum = BDOBUSDO7;
//    doBBATList.append(BDOBUStestDOstruct);
//    BBATtestDOstruct.doNum = BDOBUSDO8;
//    doBBATList.append(BDOBUStestDOstruct);
//    BBATtestDOstruct.doNum = BDOBUSDO9;
//    doBBATList.append(BDOBUStestDOstruct);
//    BBATtestDOstruct.doNum = BDOBUSDO10;
//    doBBATList.append(BDOBUStestDOstruct);
}
