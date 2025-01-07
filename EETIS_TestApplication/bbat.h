#ifndef BBAT_H
#define BBAT_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QCheckBox>

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
#define BBATDO1_20                     41


#define BBATAO01                     4
#define BBATAO02                     5
#define BBATAO03                     7


#define BBATDI_POWEROFF21              30
#define BBATDI_POWEROFF22              40


#define POWER_ON_DI                 60


#define HARNESS_BBAT_CHK_DI1        5
#define HARNESS_BBAT_CHK_DI2        33

#define HARNESS_BBAT_CHK_DO1        0
#define HARNESS_BBAT_CHK_DO2        1


#pragma pack(1)
typedef struct
{
    int doNum;
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
    int diNum;
}BBATdoStruct;


namespace Ui {
class BBAT;
}

class BBAT : public QWidget
{
    Q_OBJECT

public:
    BBATdiStruct BBATDoStruct;
    BBATdiStruct BBATDoStruct1;
    BBATdiStruct BBATPowerOffDoStruct;
    BBATdoStruct BBATDiStruct;
    QList<BBATdiStruct>doBBATList;
    QList<BBATdiStruct>doBBATList1;
    QList<BBATdiStruct>doBBATPowerOffList;
    BBATDiresultStruct BBATDiResultStruct;
    QList<BBATDiresultStruct> BBATDidataList;
    BBATdoStruct BBATtestDOstruct;
    QList<BBATdoStruct>diBBATList;
    QList<QLabel*> doLabelList;
    QList<QCheckBox*> continutyErrorList;
    QList<QCheckBox*> crossContinutyErrorList;
    //QList<QLabel*> diLabelList;
    explicit BBAT(QWidget *parent = 0);
    ~BBAT();

    void addDoStructInList();
    void addDiStructInList();
    short bbatDoval[4] = {0};
    short bbatAoVal[16] = {0};
protected:
    void processHarnessDiDO();
    int checkCorrectHarness();
    void processDoVals();

    void uiListappend();
    void diListappend();
    void addDiDoStructInList();
    void sendAiData();
protected slots:
    void update();

private:
    Ui::BBAT *ui;
    QTimer *updateUidata;
    int inputCount = 0;
    int startSendAo = 0;
    void setRegisterHigh(int bitPosition, bool highLow);
    int powerOffDO = 0;
};

#endif // BBAT_H
