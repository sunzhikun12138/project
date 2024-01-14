#ifndef CSTAGETREEWIDGET_H
#define CSTAGETREEWIDGET_H
#include <QDate>
#include <QTreeWidget>
#include "CStageEnum.h"

class CStageTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit CStageTreeWidget(QTreeWidget *parent = NULL);
    QTreeWidgetItem* addStageItem(CStageStruct::CStageInfo &stageInfo);
private:
    void initData();

};

#endif // CSTAGETREEWIDGET_H
