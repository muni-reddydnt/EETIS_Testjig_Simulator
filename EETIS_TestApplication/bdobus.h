#ifndef BDOBUS_H
#define BDOBUS_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QCheckBox>
//#include "modbuscomm.h"
//#include "globals.h"


#define DEFAULT_BUTTON_STYLESHEET  "background:rgb(234, 236, 247);border: 4px solid rgb(53,74, 131);color:rgb(53,74, 131);\
border-radius:5px;"

#define DEFAULT_DO_STYLESHEET  "QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}"

#define DO_GREEN_STYLESHEET    "QLabel { background-color : rgb(73, 202, 66); border-radius:15px;}"

#define GREEN_BUTTON_STYLESHEET  "background: rgb(73, 202, 66);border: 4px solid rgb(53,74, 131);color:rgb(53,74, 131);\
border-radius:5px;"

#define DI_RECEIVED_STYLESHEET   "QLabel{background-color: rgb(0, 170, 255);border: 4px solid rgb(53,74, 131);color:rgb(53,74, 131);\
border-radius:5px;}"

#define YELLOW_DO_STYLESHEET    "QLabel { color : white; background-color : rgb(255, 255, 0); border-radius:15px;}"

#pragma pack(1)
typedef struct
{
    int diNum;
}BODOBUSdiStruct;

#pragma pack(1)
typedef struct
{
    int Result;
    //QString upResult;
}BODOBUSDidataStruct;

#pragma pack(1)
typedef struct
{
    int doNum;
}BODOBUSdoStruct;


#define BTN_BDOBUSJ17J21   1
#define BTN_BDOBUSJ18J22   2



#define BDOBUSDI1                      17
#define BDOBUSDI2                      34
#define BDOBUSDI3                      18
#define BDOBUSDI4                      35
#define BDOBUSDI5                      19
#define BDOBUSDI6                      54
#define BDOBUSDI7                      20
#define BDOBUSDI8                      53
#define BDOBUSDI9                      21
#define BDOBUSDI10                     37


#define BDOBUSDO1                      14
#define BDOBUSDO2                      47
#define BDOBUSDO3                      15
#define BDOBUSDO4                      48
#define BDOBUSDO5                      16
#define BDOBUSDO6                      53
#define BDOBUSDO7                      17
#define BDOBUSDO8                      52
#define BDOBUSDO9                      18
#define BDOBUSDO10                     49


////receive from main
//#define BDOBUS_DO_SHELLCHK         12
//#define BDOBUS_DO_EMERGNCYCHK      16

////send to main
//#define BDOBUS_DI_SHELLCHK         12
//#define BDOBUS_DI_EMERGNCYCHK      13


#define HARNESS_BDOBUS_CHK_DI1     2

#define HARNESS_BDOBUS_CHK_DO1     1

#define HIGH                        1
#define LOW                         0

#define BDOBUS_DI_SHELLCHK         15
#define BDOBUS_DI_EMERGNCYCHK      16


#define BDOBUS_DO_SHELLCHK         12
#define BDOBUS_DO_EMERGNCYCHK      13



namespace Ui {
class bdobus;
}

class bdobus : public QWidget
{
    Q_OBJECT

public:
    explicit bdobus(QWidget *parent = 0);
    ~bdobus();
    //modbusComm *modbusCommObj;
    QList<QLabel*> diLabelList;
    QList<QLabel*> doLabelList;
    QList<QCheckBox*> continutyErrorList;
    QList<QCheckBox*> crossContinutyErrorList;

    BODOBUSdiStruct BDOBUSteststruct;
    QList<BODOBUSdiStruct>diBDOBUSList;
    BODOBUSDidataStruct BDOBUSDiResultStruct;
    QList<BODOBUSDidataStruct> BDOBUSDidataList;
    BODOBUSdoStruct BDOBUStestDOstruct;
    QList<BODOBUSdoStruct>doBDOBUSList;
    //char sendDOs[NO_OF_DOs] = {0};
    short bdobusDoval[4] = {0};
protected:
    void setRegisterHIgh(int bitPosition, bool highLow );

    //void addDiStructInList();

    void uiListappend();
    void doListappend();
    void diListappend();
    void continutyErrorListappend();
    void crossContinutyErrorListappend();

    void addDiStructInList();
    void addDoStructInList();
    void addDiDoStructInList();

    void resetAllDisAndDos();


    int checkCorrectHarness();

private slots:
    void update();
    void processDiToDO();
    void processHarnessDiDO();
    //void processShellLoadingEmgncyStop();
    //void processEnableDisableCkError();

    //void CombineProcessDido();
private:
    Ui::bdobus *ui;
    int diData[4] = {0};
    int doData[4] = {0};
    bool btnDiEnalbeDisable[16] = {0};
    QTimer *displayUPdata;
};

#endif // BDOBUS_H
