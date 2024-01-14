#include "TestGraphicsItem.h"
#include "CStageTreeWidget.h"
#include "CStageGraphicsScene.h"
#include "CStageAddItem.h"
#include "CStageEnum.h"
#include "CReadXmlFile.h"
#include "CWriteXmlFile.h"
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPushButton>
#include <QUuid>
#include <QGraphicsItem>

TestGraphicsItem::TestGraphicsItem(QWidget *parent)
    : QWidget(parent),m_pTreeWidget(NULL),m_pStageScene(NULL),
      m_pAddWidget(NULL),m_hashUid2Item(QHash<QString,QPair<QTreeWidgetItem*,CStageGraphicsItem*>>()),
      m_pView(NULL)
{
    initWidget();
    initData();
}

TestGraphicsItem::~TestGraphicsItem()
{

}

void TestGraphicsItem::initWidget()
{
    if(!m_pTreeWidget)
    {
        m_pTreeWidget = new CStageTreeWidget;
        m_pTreeWidget->setParent(this);
    }
    QHBoxLayout *pHLaout = new QHBoxLayout;
    //create TreeWidget to show the stage tree
    pHLaout->addWidget(m_pTreeWidget);
    if(!m_pView)
    {
        m_pView = new QGraphicsView;
        m_pView->setDragMode(QGraphicsView::ScrollHandDrag);
        m_pView->installEventFilter(this);
    }
    if(!m_pStageScene)
    {
        m_pStageScene = new CStageGraphicsScene;
        m_pStageScene->setParent(this);
    }
    m_pView->setScene(m_pStageScene);
    m_pView->centerOn(0,0);
    //create graphicsview to show gantt chart
    pHLaout->addWidget(m_pView);
    //create button
    QVBoxLayout *pVLayout = new QVBoxLayout;
    QPushButton *pBtnCreate = new QPushButton(this);
    pBtnCreate->setText("create");
    connect(pBtnCreate,SIGNAL(clicked(bool)),this,SLOT(slotCreateAddWidget()));
    pVLayout->addWidget(pBtnCreate);
    pHLaout->addLayout(pVLayout);
    this->setLayout(pHLaout);
}

void TestGraphicsItem::initData()
{
    QVector<CStageStruct::CStageInfo> vecStageInfo = CReadXmlFile::getInstance()->getStageInfo();
    for(int i = 0;i<vecStageInfo.size();i++)
    {
        CStageStruct::CStageInfo stageInfo = vecStageInfo.at(i);
        QTreeWidgetItem *pTreeItem = m_pTreeWidget->addStageItem(stageInfo);
        CStageGraphicsItem *pSceneItem = m_pStageScene->addStageItem2GraphicsScene(stageInfo);
        m_pView->centerOn((QGraphicsItem*)pSceneItem);
        QPair<QTreeWidgetItem*,CStageGraphicsItem*> pairTree2Scene = qMakePair(pTreeItem,pSceneItem);
        m_hashUid2Item.insert(stageInfo.strUid,pairTree2Scene);
    }
}

void TestGraphicsItem::slotCreateAddWidget()
{
    if(!m_pAddWidget)
    {
        m_pAddWidget = new CStageAddItem;
        connect(m_pAddWidget,SIGNAL(signalAddItem(QString,QDateTime,QDateTime)),this,SLOT(slotAddItem(QString,QDateTime,QDateTime)));
    }
    m_pAddWidget->show();
}

void TestGraphicsItem::slotAddItem(QString strStageName,QDateTime startDateTime,QDateTime endDateTime)
{
    CStageStruct::CStageInfo stageInfo;
    stageInfo.strUid = QUuid::createUuid().toString();
    stageInfo.strStageName = strStageName;
    stageInfo.startDateTime = startDateTime;
    stageInfo.endDateTime = endDateTime;
    QTreeWidgetItem *pTreeItem = m_pTreeWidget->addStageItem(stageInfo);
    CStageGraphicsItem *pSceneItem = m_pStageScene->addStageItem2GraphicsScene(stageInfo);
    QPair<QTreeWidgetItem*,CStageGraphicsItem*> pairTree2Scene = qMakePair(pTreeItem,pSceneItem);
    m_hashUid2Item.insert(stageInfo.strUid,pairTree2Scene);
    //QGraphicsItem *pItem = dynamic_cast<QGraphicsItem*>(pSceneItem);
    m_pView->centerOn((QGraphicsItem*)pSceneItem);
}

bool TestGraphicsItem::eventFilter(QObject *watched, QEvent *event)
{
    if(m_pView == qobject_cast<QGraphicsView*>(watched))
    {
        m_pStageScene->update();
    }
    return QObject::eventFilter(watched,event);
}
