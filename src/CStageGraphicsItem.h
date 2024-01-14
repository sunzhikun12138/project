#ifndef CSTAGEGRAPHICSITEM_H
#define CSTAGEGRAPHICSITEM_H
#include <QGraphicsItem>
#include "CStageEnum.h"

class CStageGraphicsItem : public QGraphicsItem
{
public:
    explicit CStageGraphicsItem(QGraphicsItem *parent = NULL);
    void setStageInfo(const CStageStruct::CStageInfo &stageInfo);
private:
    //根据坐标值获取时间
    QDateTime getTimeByPointF(QPointF point);
    void updateXml(QDateTime startTime,QDateTime endTime);
protected:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    CStageStruct::CStageInfo m_stageInfo;
    QRectF m_location;
    QPointF m_point;
};

#endif // CSTAGEGRAPHICSITEM_H
