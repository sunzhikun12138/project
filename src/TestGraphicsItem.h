#ifndef TESTGRAPHICSITEM_H
#define TESTGRAPHICSITEM_H

#include <QDate>
#include <QWidget>
#include <QTreeWidgetItem>
#include <QGraphicsView>

class CStageTreeWidget;
class CStageGraphicsScene;
class CStageAddItem;
class CStageGraphicsItem;

class TestGraphicsItem : public QWidget
{
    Q_OBJECT

public:
    TestGraphicsItem(QWidget *parent = 0);
    ~TestGraphicsItem();
private:
    void initWidget();
    void initData();

private slots:
    void slotCreateAddWidget();
    void slotAddItem(QString strStageName,QDateTime startDateTime,QDateTime endDateTime);
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    CStageTreeWidget *m_pTreeWidget;
    CStageGraphicsScene *m_pStageScene;
    QGraphicsView *m_pView;
    CStageAddItem *m_pAddWidget;
    QHash<QString,QPair<QTreeWidgetItem*,CStageGraphicsItem*>> m_hashUid2Item;
};

#endif // TESTGRAPHICSITEM_H
