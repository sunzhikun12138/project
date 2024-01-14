#ifndef CSTAGEADDITEM_H
#define CSTAGEADDITEM_H

#include <QWidget>

namespace Ui {
class CStageAddItem;
}

class CStageAddItem : public QWidget
{
    Q_OBJECT

public:
    explicit CStageAddItem(QWidget *parent = 0);
    ~CStageAddItem();
private:
    void initWidget();
private slots:
    void slotOKClicked();
signals:
    void signalAddItem(const QString &strStageName,const QDateTime &startDateTime,const QDateTime &endDateTime);

private:
    Ui::CStageAddItem *ui;
};

#endif // CSTAGEADDITEM_H
