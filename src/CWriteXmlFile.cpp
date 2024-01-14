#include "CWriteXmlFile.h"
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>

CWriteXmlFile *CWriteXmlFile::getInstance()
{
    static CWriteXmlFile instance;
    return &instance;
}

void CWriteXmlFile::saveStageInfos(QVector<CStageStruct::CStageInfo> vecStageinfo)
{
    QFile file("../res/SaveNode.xml");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"saveStageInfos"<<file.errorString();
        return;
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(false);
    writer.writeStartDocument();
    writer.writeStartElement("Project");
    writer.writeTextElement("name","TestProject");
    writer.writeTextElement("id","{123456}");
    for(int i = 0;i<vecStageinfo.size();i++)
    {
        writer.writeStartElement("Stage");
        writer.writeTextElement("id",vecStageinfo.at(i).strUid);
        writer.writeTextElement("name",vecStageinfo.at(i).strStageName);
        writer.writeTextElement("startTime",vecStageinfo.at(i).startDateTime.toString(DATETIMEFAMART));
        writer.writeTextElement("endTime",vecStageinfo.at(i).endDateTime.toString(DATETIMEFAMART));
        writer.writeTextElement("index",QString::number(vecStageinfo.at(i).nIndex));
        writer.writeEndElement();
    }
    writer.writeEndElement();
    file.close();
}

CWriteXmlFile::CWriteXmlFile()
{

}
