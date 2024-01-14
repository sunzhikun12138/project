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
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("Project");
    writer.writeAttribute(QXmlStreamAttribute("name","TestProject"));
    writer.writeAttribute(QXmlStreamAttribute("id","{123456}"));
    for(int i = 0;i<vecStageinfo.size();i++)
    {
        writer.writeStartElement("Stage");
        writer.writeAttribute(QXmlStreamAttribute("id",vecStageinfo.at(i).strUid));
        writer.writeAttribute(QXmlStreamAttribute("name",vecStageinfo.at(i).strStageName));
        writer.writeAttribute(QXmlStreamAttribute("startTime",vecStageinfo.at(i).startDateTime.toString(DATETIMEFAMART)));
        writer.writeAttribute(QXmlStreamAttribute("endTime",vecStageinfo.at(i).endDateTime.toString(DATETIMEFAMART)));
        writer.writeAttribute(QXmlStreamAttribute("index",QString::number(vecStageinfo.at(i).nIndex)));
        writer.writeEndElement();
    }
    writer.writeEndElement();
    file.close();
}

CWriteXmlFile::CWriteXmlFile()
{

}
