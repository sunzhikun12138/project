#ifndef CREADXMLFILE_H
#define CREADXMLFILE_H

#include "CStageEnum.h"
#include <QVector>

class CReadXmlFile
{
public:
    static CReadXmlFile *getInstance();
    void praseXmlFile();
    QVector<CStageStruct::CStageInfo> getStageInfo() const;
private:
    CReadXmlFile();
private:
    QVector<CStageStruct::CStageInfo> m_vecStageInfo;
};

#endif // CREADXMLFILE_H
