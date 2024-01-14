#include "CStageTreeWidget.h"

CStageTreeWidget::CStageTreeWidget(QTreeWidget *parent)
    :QTreeWidget(parent)
{
    this->setHeaderHidden(true);
    initData();
}

QTreeWidgetItem* CStageTreeWidget::addStageItem(CStageStruct::CStageInfo &stageInfo)
{
    QTreeWidgetItem *pItem = new QTreeWidgetItem;
    pItem->setSizeHint(0,QSize(0,ITEMHEIGHT));
    pItem->setText(0,stageInfo.strStageName);
    pItem->setData(0,CStageEnum::enTreeUidType,stageInfo.strUid);
    pItem->setData(0,CStageEnum::enTreeStartDateType,stageInfo.startDateTime);
    pItem->setData(0,CStageEnum::enTreeEndDateType,stageInfo.endDateTime);
    stageInfo.nIndex = this->topLevelItemCount();
    pItem->setData(0,CStageEnum::enTreeIndexType,stageInfo.nIndex);
    this->addTopLevelItem(pItem);
    return pItem;
}

void CStageTreeWidget::initData()
{
    QTreeWidgetItem *pItem = new QTreeWidgetItem;
    pItem->setSizeHint(0,QSize(0,ITEMHEIGHT));
    pItem->setText(0,"Ê±¼ä");
    this->addTopLevelItem(pItem);
}
