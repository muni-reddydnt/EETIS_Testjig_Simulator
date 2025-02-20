#ifndef FCU_H
#define FCU_H

#include <QWidget>
#include <QTimer>


#define DEFAULT_BUTTON_STYLESHEET  "background:rgb(234, 236, 247);border: 4px solid rgb(53,74, 131);color:rgb(53,74, 131);\
border-radius:5px;"

#define DEFAULT_DO_STYLESHEET  "QLabel { color : white; background-color : rgb(234, 236, 247); border-radius:15px;}"

#define DO_GREEN_STYLESHEET    "QLabel { background-color : rgb(73, 202, 66); border-radius:15px;}"

#define GREEN_BUTTON_STYLESHEET  "background: rgb(73, 202, 66);border: 4px solid rgb(53,74, 131);color:rgb(53,74, 131);\
border-radius:5px;"

#define DI_RECEIVED_STYLESHEET   "QLabel{background-color: rgb(0, 170, 255);border: 4px solid rgb(53,74, 131);color:rgb(53,74, 131);\
border-radius:5px;}"

#define YELLOW_DO_STYLESHEET    "QLabel { color : white; background-color : rgb(255, 255, 0); border-radius:15px;}"



#define HARNESS_FCU_CHK_DI1        2
#define HARNESS_FCU_CHK_DI2        33
#define HARNESS_FCU_CHK_DO1        32
#define HARNESS_FCU_CHK_DO2        49

namespace Ui {
class fcu;
}

class fcu : public QWidget
{
    Q_OBJECT

public:
    explicit fcu(QWidget *parent = 0);
    ~fcu();
protected:
    void checkHarness();
protected slots:
    void startTest();

private:
    Ui::fcu *ui;
    QTimer *fcuTimer;
    short fcuDoval[4] = {0};
};

#endif // FCU_H
