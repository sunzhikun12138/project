#ifndef CSTAGEENUM_H
#define CSTAGEENUM_H
#include <QDate>
#include <qnamespace.h>

#define ITEMWIDTH 100
#define ITEMHEIGHT 50
#define SCENEWIDTH 3652400 //calculate by nDiffDate*ITEMWIDTH
#define SCENEHEIGHT 1000
#define STARTDATE "2000.01.01"
#define ENDDATE "2099.12.31"
#define STARTDATETIME "2000.01.01 00:00:00"
#define ENDDATETIME "2099.12.31 23:59:59"
#define DATEFAMART "yyyy.MM.dd"
#define DATETIMEFAMART "yyyy.MM.dd hh:mm:ss"

namespace CStageEnum
{
    enum ItemDataType
    {
        enSceneUidType = Qt::UserRole,
        enSceneStartDateType = Qt::UserRole + 1,
        enSceneEndDateType = Qt::UserRole + 2,
        enSceneIndexType = Qt::UserRole +3
    };
    enum LineItemDataType
    {
        enLineIndexType = Qt::UserRole,
        enLineTimeType = Qt::UserRole + 1
    };
    enum TreeItemDataType
    {
        enTreeUidType = Qt::UserRole,
        enTreeStartDateType = Qt::UserRole + 1,
        enTreeEndDateType = Qt::UserRole + 2,
        enTreeIndexType = Qt::UserRole + 3
    };
}

namespace CStageStruct
{
    struct CStageInfo
    {
        CStageInfo()
        {
            strUid = QString();
            strStageName = QString();
            startDateTime = QDateTime();
            endDateTime = QDateTime();
            nIndex = -1;
        }

        QString strUid;
        QString strStageName;
        QDateTime startDateTime;
        QDateTime endDateTime;
        int nIndex;
    };
}


#endif // CSTAGEENUM_H
