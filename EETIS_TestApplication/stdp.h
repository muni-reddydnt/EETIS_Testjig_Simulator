#ifndef STDP_H
#define STDP_H

#include <QWidget>
#include <QTimer>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>




#define DEFAULT_BUTTON_STYLESHEET  "background:rgb(234, 236, 247);border: 4px solid rgb(53,74, 131);color:rgb(53,74, 131);\
border-radius:5px;"

#define DEFAULT_DO_STYLESHEET  "QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}"

#define DO_GREEN_STYLESHEET    "QLabel { background-color : rgb(73, 202, 66); border-radius:15px;}"

#define GREEN_BUTTON_STYLESHEET  "background: rgb(73, 202, 66);border: 4px solid rgb(53,74, 131);color:rgb(53,74, 131);\
border-radius:5px;"

#define DI_RECEIVED_STYLESHEET   "QLabel{background-color: rgb(0, 170, 255);border: 4px solid rgb(53,74, 131);color:rgb(53,74, 131);\
border-radius:5px;}"

#define YELLOW_DO_STYLESHEET    "QLabel { color : white; background-color : rgb(255, 255, 0); border-radius:15px;}"

#define PUSHBUTTON_YELLOW_STYLESHEET  "background-color: rgb(205, 220, 57); color: rgb(255, 255, 255);"
#define PUSHBUTTON_DEFAULT_STYLESHEET  "background-color: rgb(53, 74, 131); color: rgb(255, 255, 255);"




#define HARNESS_STDP_CHK_DI1              2
#define HARNESS_STDP_CHK_DI2              33
#define HARNESS_STDP_CHK_DO1              41
#define HARNESS_STDP_CHK_DO2              50

#define CONTINUTY_CHECK_STDP_DI           26
#define CONTINUTY_CHECK_STDP_DO           31

#define DEADMAN_STDP_DO                   26
#define UNLOCKING_STDP_DO                 27
#define GRFD_STDP_DO                      28
#define GRRD_STDP_DO                      29
#define LIT_STDP_DO                       32
#define LCW_UP_STDP_DO                    33
#define LCW_DN_STDP_DO                    34
#define RCW_UP_STDP_DO                    35
#define RCW_DN_STDP_DO                    36
#define LS_UP_STDP_DO                     37
#define LS_DN_STDP_DO                     38
#define RS_UP_STDP_DO                     39
#define RS_DN_STDP_DO                     40


#define BFLI_STDP_DI                      28
#define ACLI_STDP_DI                      29
#define LBLI_STDP_DI                      30
#define AFLI_STDP_DI                      31

#define STDP_AO_1                      1
#define STDP_AO_2                      2
#define STDP_AO_3                      3
#define STDP_AO_4                      4

//#define STDP_START_DI                  1  in Instruction Exel

#define STDP_START_DI                  4     //in MainApplication

#define STDP_EMERGENCY_DI1          25
#define STDP_EMERGENCY_DO1          30

#define STDP_EMERGENCY_DI2          27
#define STDP_EMERGENCY_DO2          25

#define AI_TIME_OUT             50

#define STDP_AI               1

#pragma pack(1)
typedef struct
{
    int doNum;
}STDPdoStruct;

#pragma pack(1)
typedef struct
{
    int diNum;
}STDPdiStruct;


#pragma pack(1)
typedef struct
{
    int Result;
}stdpDidataStruct;

namespace Ui {
class stdp;
}

class stdp : public QWidget
{
    Q_OBJECT

public:
    explicit stdp(QWidget *parent = 0);
    ~stdp();
    short stdpDoval[4] = {0};
    //short stdpAoVal[16] = {0};
    short stdpAoVal[16] = {0};
    QList<QCheckBox*> crossContinutyErrorList;
    STDPdoStruct STDPdoStructDOstruct;
    STDPdiStruct STDPdiStructObj;
    stdpDidataStruct stdpDidataStructResult;
    QList<stdpDidataStruct> STDPdiResultList;
    QList<STDPdiStruct> diSTDPList;
    QList<STDPdoStruct> doSTDPList;
    QList<QLabel*> doLblsList;
    QList<QPushButton*>pbList;
    QList<QLabel*> diLblsList;

protected:
    void hideCrosss();
    void checkCorrectHarness();
    void checkContinuty();
    void setRegisterHIgh(int bitPosition, bool highLow );
    void checkPushButtonData();
    void crossContinutyErrorListappend();
    void addDoStructInList();
    void uiListappend();
    void addDoLblInList();
    void addPbInList();
    void addDiStructInList();
    void addDilblInList();
    void diData();
    //void sendAoData();
    void checkPowerOnDi();
    void checkEmergency();
    void setDataInAO();

protected slots:
    void startTest();
    void sendAoData();

private slots:
    void on_pbDeadman_clicked();

    void on_pbUnlocking_clicked();

    void on_pbGRFD_clicked();

    void on_pbGRRD_clicked();

    void on_pbLIT_clicked();

    void on_pbLCWup_clicked();

    void on_pbLCWdn_clicked();

    void on_pbRCWup_clicked();

    void on_pbRCWdn_clicked();

    void on_pbLSup_clicked();

    void on_pbLSdn_clicked();

    void on_pbRSup_clicked();

    void on_pbRSdn_clicked();

private:
    Ui::stdp *ui;
    QTimer *updateUidata;
    QTimer *aiSendTimer;
    bool deadManSts= false, unlockingSts = false, grfdSts = false, grrdSts = false, litSts = false;
    bool lcwUpSts = false,  lcwDnSts = false, rcwUpSts = false,  rcwDnSts = false, lsUpSts = false;
    bool lsDnSts = false, rsUpSts = false, rsDnSts = false;
    bool pbSts[13] = {0};
    int aiStartCount = 0;
    int aiStopCount = 0;
    int powerOnDI = 0;
    bool aiSend = false;
    int Aidata = 0;
};


#endif // STDP_H
