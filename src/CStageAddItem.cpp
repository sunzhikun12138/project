#include "CStageAddItem.h"
#include "ui_CStageAddItem.h"
#include "CStageEnum.h"
#include <QDateTime>

CStageAddItem::CStageAddItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CStageAddItem)
{
    ui->setupUi(this);
    initWidget();
}
void CStageAddItem::initWidget()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    ui->lineEdit_startTime->setText(currentDateTime.toString(DATETIMEFAMART));
    ui->lineEdit_endTime->setText(currentDateTime.toString(DATETIMEFAMART));
    ui->lineEdit_stageName->setText("stage");
    //connect signal and slot
    connect(ui->pushButton_cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->pushButton_ok,SIGNAL(clicked(bool)),this,SLOT(slotOKClicked()));
}

void CStageAddItem::slotOKClicked()
{
    QString strStageName = ui->lineEdit_stageName->text();
    QString strStartDateTime = ui->lineEdit_startTime->text();
    QString strEndDateTime = ui->lineEdit_endTime->text();
    //notify TestGraphicsItem add item ->
    emit signalAddItem(strStageName,QDateTime::fromString(strStartDateTime,DATETIMEFAMART),QDateTime::fromString(strEndDateTime,DATETIMEFAMART));
    this->setVisible(false);
}
CStageAddItem::~CStageAddItem()
{
    delete ui;
}
