#include "cuhresparser.h"

#include <QJsonDocument>
#include <QtDebug>
#include <QTextStream>

#include "cuhresdataprocessor.h"

CuHRESParser::CuHRESParser()
{

}

bool CuHRESParser::parseTransactionFile(const QString& path) {

    int numErrors = 0;
    /*open transaction file for read*/
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not read transaction file" << file.fileName() << ": " << file.errorString();
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        /*reading line by line*/
        QString line = in.readLine();
        QByteArray fileData = line.toUtf8();

        /*check if data was read*/
        if (fileData.isEmpty()) {
            qDebug() << "No data avalailable from file" << file.fileName();
            return false;
        }

        /*populate json document*/
        QJsonDocument doc = QJsonDocument::fromJson(fileData);
        if (!doc.isObject()) {
            qDebug() << "Document is not a valid json object";
            return false;
        }

        CuhresDataProcessor dataProcessor;
        if (dataProcessor.processData(doc) == false)
        {
            numErrors++;
        }
    }
    file.close();
    if (numErrors == 0)
    {
        return true;
    }
    return false;
}
