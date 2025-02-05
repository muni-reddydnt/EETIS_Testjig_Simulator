#ifndef DISPOPUP_H
#define DISPOPUP_H

#include <QWidget>

namespace Ui {
class disPopup;
}

class disPopup : public QWidget
{
    Q_OBJECT

public:
    explicit disPopup(QWidget *parent = 0);
    void showMessage(QString msg);
    ~disPopup();

private slots:
    void on_btnPopupOK_clicked();

private:
    Ui::disPopup *ui;
};

#endif // DISPOPUP_H
