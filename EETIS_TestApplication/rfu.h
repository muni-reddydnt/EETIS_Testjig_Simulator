#ifndef RFU_H
#define RFU_H

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




#define HARNESS_RFU_CHK_DO       41
#define HARNESS_RFU_CHK_DI        2


#define  RFUDO1          26
#define  RFUDO2          27
#define  RFUDO3          28

#define  RFUDI1          26
#define  RFUDI2          27
#define  RFUDI3          28



#define  RFU_BREECHCLOSING_DI1          6
#define  RFU_BREECHCLOSING_DI2          8
#define  RFU_FIRE_DI1                   5
#define  RFU_FIRE_DI2                   7
#define  RFU_BREECHLOADING_DI           9





#define  RFU_BREECHCLOSING_DO1          3
#define  RFU_BREECHCLOSING_DO2          5
#define  RFU_FIRE_DO1                   2
#define  RFU_FIRE_DO2                   4
#define  RFU_BREECHLOADING_DO           6






#pragma pack(1)
typedef struct
{
    int diNum;
}rfudiStruct;

#pragma pack(1)
typedef struct
{
    int doNum;
}rfudoStruct;

#pragma pack(1)
typedef struct
{
    int Result;
    //QString upResult;
}rfuDidataStruct;


namespace Ui {
class rfu;
}

class rfu : public QWidget
{
    Q_OBJECT

public:
    explicit rfu(QWidget *parent = 0);
    ~rfu();
    QList<QLabel*> diLabelList;
    QList<QLabel*> doLabelList;
    QList<QCheckBox*> continutyErrorList;
    QList<QCheckBox*> crossContinutyErrorList;
    QList<QCheckBox*> forceDoOnList;
    QList<QCheckBox*> forceDoOffList;
    short rfuDoval[4] = {0};
    rfudiStruct rfuDistruct;
    QList<rfudiStruct>diRfuList;
    rfudoStruct rfuDostruct;
    QList<rfudoStruct>doRfuList;
    rfuDidataStruct rfuDiResultStruct;
    QList<rfuDidataStruct> rfuDidataList;

protected slots:
    void startTest();
protected:
    int checkCorrectHarness();
    void processHarnessDiDO();
    void processDiDo();
    void setRegisterHIgh(int bitPosition, bool highLow );
    void addDiStructInList();
    void addDoStructInList();
    void addDiDoStructInList();
    void uiListappend();
    void doListappend();
    void diListappend();
    void continutyErrorListappend();
    void crossContinutyErrorListappend();
    void ckForceDoOnListAppend();
    void ckForceDoOffListAppend();
private:
    Ui::rfu *ui;
    QTimer *displayUPdata;
};

#endif // RFU_H
