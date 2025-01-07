#ifndef BFCMDF_H
#define BFCMDF_H

#include <QWidget>
#include <QTimer>


#define BFCMDFDI1                    1

#define HARNESS_BFCMD_CHK_DI1        5
#define HARNESS_BFCMD_CHK_DO1        10

#define BFCMDFDO1                    1

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
protected slots:
    void update();
    void processHarnessDiDO();
    void processContinutyProcess();

private:
    Ui::bfcmdf *ui;
    QTimer *displayUPdata;
};

#endif // BFCMDF_H
