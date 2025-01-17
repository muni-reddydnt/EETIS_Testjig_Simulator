#ifndef BBAT_H
#define BBAT_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QCheckBox>
/*
#define BBATDO1                      2
#define BBATDO2                      3
#define BBATDO3                      4
#define BBATDO4                      5
#define BBATDO5                      6
#define BBATDO6                      7
#define BBATDO7                      8
#define BBATDO8                      9
#define BBATDO9                      10
#define BBATDO10                     11
#define BBATDO11                     12
#define BBATDO12                     13
#define BBATDO13                     14
#define BBATDO14                     15
#define BBATDO15                     16
#define BBATDO16                     17
#define BBATDO17                     18
#define BBATDO18                     19
#define BBATDO19                     20
#define BBATDO20                     21

#define BBATDO1_1                      22
#define BBATDO1_2                      23
#define BBATDO1_3                      24
#define BBATDO1_4                      25
#define BBATDO1_5                      26
#define BBATDO1_6                      27
#define BBATDO1_7                      28
#define BBATDO1_8                      29
#define BBATDO1_9                      30
#define BBATDO1_10                     31
#define BBATDO1_11                     32
#define BBATDO1_12                     33
#define BBATDO1_13                     34
#define BBATDO1_14                     35
#define BBATDO1_15                     36
#define BBATDO1_16                     37
#define BBATDO1_17                     38
#define BBATDO1_18                     39
#define BBATDO1_19                     40
#define BBATDO1_20                     41*/

#define DEFAULT_STYLESHEET  "QLabel {background:rgb(234, 236, 247);border: 4px solid rgb(53,74, 131);color:rgb(53,74, 131);\
border-radius:5px;}"

#define DEFAULT_DO_STYLESHEET  "QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}"

#define DI_RECEIVED_STYLESHEET   "QLabel{background-color: rgb(0, 170, 255);border: 4px solid rgb(53,74, 131);color:rgb(53,74, 131);\
border-radius:5px;}"

#define GREEN_BUTTON_STYLESHEET  "background: rgb(73, 202, 66);border: 4px solid rgb(53,74, 131);color:rgb(53,74, 131);\
border-radius:5px;"

#define BBAT_DO1_1                      2
#define BBAT_DO1_2                      22
#define BBAT_DO2_1                      3
#define BBAT_DO2_2                      23
#define BBAT_DO3_1                      4
#define BBAT_DO3_2                      24
#define BBAT_DO4_1                      5
#define BBAT_DO4_2                      25
#define BBAT_DO5_1                      6
#define BBAT_DO5_2                      26
#define BBAT_DO6_1                      7
#define BBAT_DO6_2                      27
#define BBAT_DO7_1                      8
#define BBAT_DO7_2                      28
#define BBAT_DO8_1                      9
#define BBAT_DO8_2                      29
#define BBAT_DO9_1                      10
#define BBAT_DO9_2                      32
#define BBAT_DO10_1                     11
#define BBAT_DO10_2                     33
#define BBAT_DO11_1                     12
#define BBAT_DO11_2                     34
#define BBAT_DO12_1                     13      //this DO is used twice along with DO 12_2 & 13_2
#define BBAT_DO12_2                     35
#define BBAT_DO13_2                     36
#define BBAT_DO14_1                     14
#define BBAT_DO14_2                     37
#define BBAT_DO15_1                     15
#define BBAT_DO15_2                     38
#define BBAT_DO16_1                     16
#define BBAT_DO16_2                     39
#define BBAT_DO17_1                     17
#define BBAT_DO17_2                     42
#define BBAT_DO18_1                     18
#define BBAT_DO18_2                     43
#define BBAT_DO19_1                     19
#define BBAT_DO19_2                     44

#define BBAT_DI_8                      8
#define BBAT_DO_46                     46

#define BBAT_AO_1                      4
#define BBAT_AO_2                      5
#define BBAT_AO_3                      7

#define BBAT_TIMERCHK_DI_1              6
#define BBAT_TIMERCHK_DI_2              7
#define BBAT_TIMERCHK_DO_1              31
#define BBAT_TIMERCHK_DO_2              41

#define POWER_ON_DI                    60

#define HARNESS_BBAT_CHK_DI1        5
#define HARNESS_BBAT_CHK_DI2        33
#define HARNESS_BBAT_CHK_DO1        20
#define HARNESS_BBAT_CHK_DO2        48

#define MS_TO_SEC                   1000

#pragma pack(1)
typedef struct
{
    int diNum;
}BBATdiStruct;

#pragma pack(1)
typedef struct
{
    int Result;
    QString upResult;
}BBATDiresultStruct;

#pragma pack(1)
typedef struct
{
    int doNum;
}BBATdoStruct;

namespace Ui {
class BBAT;
}

class BBAT : public QWidget
{
    Q_OBJECT

public:
    BBATdoStruct stBBATDo;
//    BBATdiStruct BBATDoStruct1;
    BBATdoStruct stBBATTimerchkDo;
    BBATdiStruct stBBATDi;

    QList<BBATdoStruct>do1_1List;
    QList<BBATdoStruct>do1_2List;
    QList<BBATdoStruct>timerchkDoList;

//    BBATDiresultStruct BBATDiResultStruct;
//    QList<BBATDiresultStruct> BBATDidataList;
//    BBATdoStruct BBATtestDOstruct;
    QList<BBATdiStruct>diBBATList;

    QList<QLabel*> diLabelList;
    QList<QLabel*> do1_1LabelList;
    QList<QLabel*> do1_2LabelList;
    QList<QCheckBox*> continuityErrListForDO1;
    QList<QCheckBox*> continuityErrListForDO2;
    //QList<QLabel*> diLabelList;
    explicit BBAT(QWidget *parent = 0);
    ~BBAT();

    void addDoStructInList();
    void addDiStructInList();
    short bbatDoval[4] = {0};
    short bbatAoVal[16] = {0};
protected:
    void processHarnessDiDO();
    void processOfPowerOffDOToDI();
    void checkCorrectHarness();
    void processDoVals();

    void uiListappend();
    void resetAllDisAndDos();
    void addDo1LabelsInList();
    void addDo2LabelsInList();
    void addContErrForDo1InList();
    void addContErrForDo2InList();
    void addDiDoStructInList();
    void sendAiData();

protected slots:
    void startTest();

private:
    Ui::BBAT *ui;
    QTimer *updateUidata;
    int timerChkCount = 0;
    int startSendAo = 0;
    void setRegisterHigh(int bitPosition, bool highLow);
    int timerChkDO1 = 0;
    int timerChkDO2 = 0;
    int timerChkDI1 = 0;
    int timerChkDI2 = 0;
    bool startTimerCount = false;
};

#endif // BBAT_H
