#ifndef RFU_H
#define RFU_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QCheckBox>


#define HARNESS_RFU_CHK_DO1        31
#define HARNESS_RFU_CHK_DI1        2


#define  RFUDO1          26
#define  RFUDO2          27
#define  RFUDO3          28

#define  RFUDI1          26
#define  RFUDI2          27
#define  RFUDI3          28

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
    short rfuDoval[4] = {0};
    rfudiStruct rfuDistruct;
    QList<rfudiStruct>diRfuList;
    rfudoStruct rfuDostruct;
    QList<rfudoStruct>doRfuList;
    rfuDidataStruct rfuDiResultStruct;
    QList<rfuDidataStruct> rfuDidataList;

protected slots:
    void update();
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
private:
    Ui::rfu *ui;
    QTimer *displayUPdata;
};

#endif // RFU_H
