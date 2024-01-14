#include "CStageGraphicsItem.h"
#include "CStageEnum.h"
#include "CReadXmlFile.h"
#include "CWriteXmlFile.h"
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QDebug>

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
    //计算一个像素点代表多少秒--100px==1天==86400s
    int nDiffSecs = (point.x()+m_point.x())*864;
    QDateTime retTime = QDateTime::fromString(STARTDATETIME,DATETIMEFAMART).addSecs(nDiffSecs);
    return retTime;
}

void CStageGraphicsItem::updateXml(QDateTime startTime, QDateTime endTime)
{
    CReadXmlFile::getInstance()->praseXmlFile();
    QVector<CStageStruct::CStageInfo> vecStageInfo = CReadXmlFile::getInstance()->getStageInfo();
    for(int i = 0;i<vecStageInfo.size();i++)
    {
        if(vecStageInfo.at(i).strUid == m_stageInfo.strUid)
        {
            //更新该阶段的开始时间和结束时间
            vecStageInfo[i].startDateTime = startTime;
            vecStageInfo[i].endDateTime = endTime;
        }
    }
    m_stageInfo.startDateTime = startTime;
    m_stageInfo.endDateTime = endTime;
    //将修改完的阶段信息写入xml文件
    CWriteXmlFile::getInstance()->saveStageInfos(vecStageInfo);
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
        QPointF startPoint = value.toPointF();
        QPointF endPoint = startPoint;
        endPoint.setX(startPoint.x()+m_location.width());
        QDateTime startTime = getTimeByPointF(startPoint);
        QDateTime endTime = getTimeByPointF(endPoint);
        //更新xml文件中的位置信息
        updateXml(startTime,endTime);
    }
    return QGraphicsItem::itemChange(change,value);
}
