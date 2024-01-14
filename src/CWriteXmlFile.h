#ifndef CWRITEXMLFILE_H
#define CWRITEXMLFILE_H

#include "CStageEnum.h"

class CWriteXmlFile
{
public:
    static CWriteXmlFile *getInstance();
    void saveStageInfos(QVector<CStageStruct::CStageInfo> vecStageinfo);
private:
    CWriteXmlFile();
};

#endif // CWRITEXMLFILE_H
