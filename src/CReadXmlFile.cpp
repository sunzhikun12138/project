#include "CReadXmlFile.h"
#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>

CReadXmlFile *CReadXmlFile::getInstance()
{
    static CReadXmlFile instance;
    return &instance;
}

QVector<CStageStruct::CStageInfo> CReadXmlFile::getStageInfo() const
{
    return m_vecStageInfo;
}

CReadXmlFile::CReadXmlFile():m_vecStageInfo(QVector<CStageStruct::CStageInfo>())
{
    praseXmlFile();
}

void CReadXmlFile::praseXmlFile()
{
    QFile file("../res/SaveNode.xml");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"praseXmlFile"<<file.errorString();
        return;
    }
    QXmlStreamReader reader(&file);
    while(!reader.atEnd() && !reader.hasError())
    {
        QXmlStreamReader::TokenType token = reader.readNext();
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        if(reader.isStartElement() && reader.name() == "Stage")
        {
            QXmlStreamAttributes attrs = reader.attributes();
            CStageStruct::CStageInfo info;
            for(int i = 0;i<attrs.size();i++)
            {
                if("id" == attrs.at(i).name())
                {
                    info.strUid = attrs.at(i).value().toString();
                }
                else if("name" == attrs.at(i).name())
                {
                    info.strStageName = attrs.at(i).value().toString();
                }
                else if("startTime" == attrs.at(i).name())
                {
                    info.startDateTime = QDateTime::fromString(attrs.at(i).value().toString(),DATETIMEFAMART);
                }
                else if("endTime" == attrs.at(i).name())
                {
                    info.endDateTime = QDateTime::fromString(attrs.at(i).value().toString(),DATETIMEFAMART);
                }
                else if("index" == attrs.at(i).name())
                {
                    info.nIndex = attrs.at(i).value().toInt();
                }
            }
            m_vecStageInfo.push_back(info);
        }
    }
    file.close();
}
