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
    int diNum;
}BODOBUSdiStructsefty;

#pragma pack(1)
typedef struct
{
    int Result;
    //QString upResult;
}BODOBUSDidataStruct;

#pragma pack(1)
typedef struct
{
    int Result;
    //QString upResult;
}BODOBUSDiSeftydataStruct;
#pragma pack(1)
typedef struct
{
    int doNum;
}BODOBUSdoStruct;

#pragma pack(1)
typedef struct
{
    int doNum;
}BODOBUSdoStructsefty;

#define BTN_BDOBUSJ17J21   1
#define BTN_BDOBUSJ18J22   2

#define BDOBUSDI1                      17
#define BDOBUSDI2                      18
#define BDOBUSDI3                      19
#define BDOBUSDI4                      20
#define BDOBUSDI5                      21
#define BDOBUSDI6                      49
#define BDOBUSDI7                      50
#define BDOBUSDI8                      51
#define BDOBUSDI9                      52
#define BDOBUSDI10                     53

#define BDOBUSDO1                      52
#define BDOBUSDO2                      53
#define BDOBUSDO3                      54
#define BDOBUSDO4                      55
#define BDOBUSDO5                      56
#define BDOBUSDO6                      14
#define BDOBUSDO7                      15
#define BDOBUSDO8                      16
#define BDOBUSDO9                      17
#define BDOBUSDO10                     18

#define HARNESS_BDOBUS_CHK_DI1     2
#define HARNESS_BDOBUS_CHK_DO1     41

#define BDOBUS_SHELLCHK_DI         15
#define BDOBUS_SHELLCHK_DO         12

#define BDOBUS_EMERGNCYCHK_DI1      16
#define BDOBUS_EMERGNCYCHK_DO1      13
#define BDOBUS_EMERGNCYCHK_DI2      32
#define BDOBUS_EMERGNCYCHK_DO2      42


//#define BDOBUS_EMERGNCYCHK_DI      16
//#define BDOBUS_EMERGNCYCHK_DO     13
//#define BDOBUS_DI_EMERGNCYCHK_2      32
//#define BDOBUS_DO_EMERGNCYCHK_2      42

#define BDOBUS_SAFTEY_DO_1              15
#define BDOBUS_SAFTEY_DO_2              18

#define BDOBUS_SAFTEY_DI_1              18
#define BDOBUS_SAFTEY_DI_2              21

#define HIGH                        1
#define LOW                         0

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
    QList<QLabel*> safetyConnectorDiLabelList;
    QList<QLabel*> doLabelList;
    QList<QLabel*> safetyConnectorDoLabelList;
    QList<QCheckBox*> continutyErrorList;
    QList<QCheckBox*> safetyContinutyErrorList;
    QList<QCheckBox*> crossContinutyErrorList;
    QList<QCheckBox*> do_OnCbList;
    QList<QCheckBox*> do_OffCbList;
    QList<QCheckBox*> safetyConnecotdo_OnCbList;
    QList<QCheckBox*> safetyConnecotdo_OffCbList;

    BODOBUSdiStruct BDOBUSteststruct;
    BODOBUSdiStructsefty BODOBUSdiStructseftyObj;
    QList<BODOBUSdiStruct>diBDOBUSList;
    QList<BODOBUSdiStructsefty>diBDOBUSListsefty;
    BODOBUSDidataStruct BDOBUSDiResultStruct;
    BODOBUSDiSeftydataStruct BODOBUSDiSeftydataStructObj;
    QList<BODOBUSDidataStruct> BDOBUSDidataList;
    QList<BODOBUSDiSeftydataStruct> BODOBUSDiSeftydataStructlist;
    BODOBUSdoStruct BDOBUStestDOstruct;
    BODOBUSdoStructsefty BDOBUStestDOstructseftyobj;
    QList<BODOBUSdoStruct>doBDOBUSList;
    QList<BODOBUSdoStructsefty>BODOBUSdoStructseftyList;
    //char sendDOs[NO_OF_DOs] = {0};
    short bdobusDoval[4] = {0};
protected:
    void setRegisterHIgh(int bitPosition, bool highLow );

    void uiListappend();
    void doListappend();
    void diListappend();
    void ckForceDoOnListAppend();
    void ckForceDoOnOffListAppend();
    void continutyErrorListappend();
    void crossContinutyErrorListappend();
    void addDiStructInList();
    void addDoStructInList();
    void sefty();
    void seftyDO();
    void addDiDoStructInList();
    void resetAllDisAndDosLabels();

    int checkCorrectHarness();
    void safetyConnectorTest();

private slots:
    void startTest();
    void processDiToDO();
    void processHarnessDiDO();
    void ProcessShellEmergencyDiDO();
private:
    Ui::bdobus *ui;
    int diData[4] = {0};
    int doData[4] = {0};
    bool btnDiEnalbeDisable[16] = {0};
    QTimer *bdobusTimer;
    int tempSafteyConnectorCheck = 0;
    int temp = 0;
    bool flag =false;
    int shellCount = 0, Emergency1Count = 0, Emergency2Count = 0, safteyCounter1 = 0, safteyCounter2 = 0;
    int continutyCount[12] = {0};
    int safteyKeyConnector1 = 0, safteyKeyConnector2 = 0;
};

#endif // BDOBUS_H
