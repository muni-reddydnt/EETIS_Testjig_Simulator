#ifndef BBAT_H
#define BBAT_H

#include <QWidget>

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
}BBATresultStruct;
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
    BBATdiStruct BBATteststruct;
    QList<BBATdiStruct>diBBATList;
    BBATresultStruct BBATtestResult;
    QList<BBATresultStruct> BBATresultList;
    BBATdoStruct BBATtestDOstruct;
    QList<BBATdoStruct>doBBATList;
    explicit BBAT(QWidget *parent = 0);
    ~BBAT();

    void addDiStructInList();

private:
    Ui::BBAT *ui;
};

#endif // BBAT_H
