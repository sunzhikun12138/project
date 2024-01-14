#include "CStageGraphicsItem.h"
#include "CStageEnum.h"
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>

CStageGraphicsItem::CStageGraphicsItem(QGraphicsItem *parent)
    :QGraphicsItem(parent),m_location(QRectF()),m_point(QPointF()),
      m_stageInfo(CStageStruct::CStageInfo())
{
    this->setFlags(ItemIsMovable | ItemSendsGeometryChanges);
    this->setCacheMode(ItemCoordinateCache);
}

void CStageGraphicsItem::setStageInfo(const CStageStruct::CStageInfo &stageInfo)
{
    m_stageInfo = stageInfo;
    //计算开始时间的横坐标 开始时间与2000.1.1之间的时间差*100
    qint64 nDiffSecs = qAbs(stageInfo.startDateTime.secsTo(QDateTime::fromString(STARTDATETIME,DATETIMEFAMART)));
    qreal startX = nDiffSecs * 100 / 86400;
    //计算结束时间的横坐标
    nDiffSecs = qAbs(stageInfo.endDateTime.secsTo(QDateTime::fromString(STARTDATETIME,DATETIMEFAMART)));
    qreal endX = nDiffSecs * 100 / 86400;
    //初始化绘图区域
    //m_location.setTopLeft(QPointF(startX,m_stageInfo.nIndex*ITEMHEIGHT));
    //m_location.setBottomRight(QPointF(endX,m_stageInfo.nIndex*ITEMHEIGHT));
    m_location.setX(startX);
    m_location.setY(m_stageInfo.nIndex*ITEMHEIGHT);
    m_point.setX(startX);
    m_point.setY(m_stageInfo.nIndex*ITEMHEIGHT);
    m_location.setWidth(endX-startX);
    m_location.setHeight(ITEMHEIGHT);
    //m_location = QRectF(startX,m_stageInfo.nIndex*ITEMHEIGHT,endX,m_stageInfo.nIndex*ITEMHEIGHT);
}

QDateTime CStageGraphicsItem::getTimeByPointF(QPointF point)
{
    return QDateTime::currentDateTime();
}

QRectF CStageGraphicsItem::boundingRect() const
{
    return m_location;
}

void CStageGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(QBrush(qrand()));
    painter->drawRect(m_location);
    painter->setPen(Qt::white);
    QFont font = painter->font();
    font.setPointSize(20);
    painter->setFont(font);
    painter->drawText(m_location,m_stageInfo.strStageName);
}

QVariant CStageGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange)
    {
        QPointF point = value.toPointF();
        // item以m_location的起始点为原点
        if(point.x() < -m_point.x())
        {
            qreal x = -m_point.x();
            point.setX(x);
        }
        else if(point.x() > SCENEWIDTH)
        {
            qreal x = SCENEWIDTH;
            point.setX(x);
            //return QGraphicsItem::itemChange(change,point);
        }
        //limit y range
        if(point.y() != m_location.y())
        {
            qreal y = m_location.y()-ITEMHEIGHT*(m_stageInfo.nIndex);
            point.setY(y);
            //return QGraphicsItem::itemChange(change,point);
        }
        return QGraphicsItem::itemChange(change,point);
    }
    else if(change == ItemPositionHasChanged)
    {

    }
    return QGraphicsItem::itemChange(change,value);
}
