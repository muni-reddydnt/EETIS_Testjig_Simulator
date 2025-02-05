#include "dispopup.h"
#include "ui_dispopup.h"

extern int showPopupIndex;

disPopup::disPopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::disPopup)
{
    ui->setupUi(this);
}

void disPopup::showMessage(QString msg)
{
    ui->lblError->setText(msg);
}

disPopup::~disPopup()
{
    delete ui;
}

void disPopup::on_btnPopupOK_clicked()
{
    switch(showPopupIndex)
    {
    case 1:
        break;
    default:
        break;
    }
}
