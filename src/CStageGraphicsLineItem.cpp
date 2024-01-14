#include "CStageGraphicsLineItem.h"
#include "CStageEnum.h"
#include <QDate>
#include <QPainter>

CStageGraphicsLineItem::CStageGraphicsLineItem(QGraphicsItem *parent)
    :QGraphicsItem(parent),m_location(QRectF())
{

}

void CStageGraphicsLineItem::setLocation(QRectF location)
{
    m_location = location;
}

QRectF CStageGraphicsLineItem::boundingRect() const
{
    return m_location;
}

void CStageGraphicsLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black));
    QPointF point1,point2;
    int nIndex = this->data(CStageEnum::enLineIndexType).toInt(NULL);
    point1.setX(nIndex*ITEMWIDTH);
    point1.setY(ITEMHEIGHT/2);
    point2.setX(nIndex*ITEMWIDTH);
    point2.setY(SCENEHEIGHT);
    //draw the line of time
    painter->drawLine(point1,point2);
    QDate date = this->data(CStageEnum::enLineTimeType).toDate();
    //draw the time of line
    painter->drawText(QRectF(nIndex*ITEMWIDTH,0,ITEMWIDTH,ITEMHEIGHT/2),date.toString(DATEFAMART));
}
