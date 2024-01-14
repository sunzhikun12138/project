#ifndef CSTAGEGRAPHICSSCENE_H
#define CSTAGEGRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QTreeWidgetItem>
#include "CStageEnum.h"
class CStageGraphicsItem;
class CStageGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CStageGraphicsScene(QGraphicsScene *parent = NULL);
    CStageGraphicsItem* addStageItem2GraphicsScene(const CStageStruct::CStageInfo &stageInfo);
private:
    void initWidget();
};

#endif // CSTAGEGRAPHICSSCENE_H
