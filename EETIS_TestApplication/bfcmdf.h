#ifndef BFCMDF_H
#define BFCMDF_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QCheckBox>



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
}BFCMDFdiStrut;

#pragma pack(1)
typedef struct
{
    int Result;
    //QString upResult;
}BFCMDFdiresultStruct;

#pragma pack(1)
typedef struct
{
    int doNum;
}BFCMDFdoStruct;




#define HARNESS_BFCMD_CHK_DI1                         2
#define HARNESS_BFCMD_CHK_DO1                         41

#define BFCMDF_POWERON_DI                             1

#define BFCMDF_FIRE_READY_DI                            22
#define BFCMDF_FIREREADY_DO                            22

#define BFCMDF_FIRE_FORBIDDEN_DI                       23
#define BFCMDF_FIRE_FORBIDDEN_LED_DO                       23

#define BFCMDF_SHELLLOADING_LED_DI                    24
#define BFCMDF_SHELLLOADING_LED_DO                    24

#define BFCMDF_FIRE_BUTTON_DI1                        12
#define BFCMDF_FIRE_BUTTON_DI2                        14

#define BFCMDF_FIRE_BUTTON_DO1                        7
#define BFCMDF_FIRE_BUTTON_DO2                        11

#define BFCMDF_BREECHCLOSING_DI1                      10
#define BFCMDF_BREECHCLOSING_DI2                      11

#define BFCMDF_BREECHCLOSING_DO1                      9
#define BFCMDF_BREECHCLOSING_DO2                      10

#define BFCMDF_CONTINUITY_DI                             13
#define BFCMDF_CONTINUITY_DO                             8


namespace Ui {
class bfcmdf;
}

class bfcmdf : public QWidget
{
    Q_OBJECT

public:
    explicit bfcmdf(QWidget *parent = 0);
    ~bfcmdf();
    int checkCorrectHarness();
    short bfcmdfDoval[4] = {0};
    QList<QLabel*> diLabelList;
    QList<QLabel*> doLabelList;
    QList<QCheckBox*> continutyErrorList;
    QList<QCheckBox*> crossContinutyErrorList;
    QList<QCheckBox*> do_OnCbList;
    QList<QCheckBox*> do_OffCbList;
    QList<BFCMDFdiStrut>diBFCMDFDiList;
    QList<BFCMDFdoStruct>doBFCMDFList;
    QList<BFCMDFdiresultStruct>BFCMDFResultList;
    BFCMDFdiStrut BFCMDFDiStrut;
    BFCMDFdoStruct BFCMDFDoStrut;
    BFCMDFdiresultStruct BFCMDFDiResultStruct;

protected:
    void diListappend();
    void doListappend();
    void continutyErrorListappend();
    void crossContinutyErrorListappend();
    void ckForceDoOnListAppend();
    void ckForceDoOnOffListAppend();
    void addDiStructInList();
    void addDoStructInList();
    void uiListappend();
    void checkPoweronDI();
    void checkDIs();

protected slots:
    void startTest();
    void processHarnessDiDO();
    void processContinutyProcess();

private:
    Ui::bfcmdf *ui;
    QTimer *displayUPdata;
};

#endif // BFCMDF_H
