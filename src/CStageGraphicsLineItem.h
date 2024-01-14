#ifndef CSTAGEGRAPHICSLINEITEM_H
#define CSTAGEGRAPHICSLINEITEM_H
#include <QGraphicsItem>

class CStageGraphicsLineItem : public QGraphicsItem
{
public:
    explicit CStageGraphicsLineItem(QGraphicsItem *parent = NULL);
    void setLocation(QRectF location);
protected:
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
private:
    QRectF m_location;
};

#endif // CSTAGEGRAPHICSLINEITEM_H
