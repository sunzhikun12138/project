#include "CStageGraphicsScene.h"
#include "CStageGraphicsItem.h"
#include "CStageGraphicsLineItem.h"
#include <QDate>

CStageGraphicsScene::CStageGraphicsScene(QGraphicsScene *parent)
    :QGraphicsScene(parent)
{
    this->setSceneRect(0,0,SCENEWIDTH,SCENEHEIGHT);
    initWidget();
}

CStageGraphicsItem* CStageGraphicsScene::addStageItem2GraphicsScene(const CStageStruct::CStageInfo &stageInfo)
{
    CStageGraphicsItem *pItem = new CStageGraphicsItem;
    pItem->setStageInfo(stageInfo);
    this->addItem(pItem);
    return pItem;
}

void CStageGraphicsScene::initWidget()
{
    CStageGraphicsLineItem *pItem = NULL;
    //calculate the length of time line item
    QDate startDate = QDate::fromString(STARTDATE,DATEFAMART);
    QDate endDate = QDate::fromString(ENDDATE,DATEFAMART);
    qint64 nDiffDate = startDate.daysTo(endDate);
    for(int i = 0;i<nDiffDate;i++)
    {
        pItem = new CStageGraphicsLineItem;
        pItem->setLocation(QRectF(i*ITEMWIDTH,ITEMHEIGHT/2,ITEMWIDTH,SCENEHEIGHT));
        pItem->setData(CStageEnum::enLineIndexType,i);
        pItem->setData(CStageEnum::enLineTimeType,startDate.addDays(i));
        this->addItem(pItem);
    }
}
