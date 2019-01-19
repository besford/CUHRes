#ifndef CUHRESPARSER_H
#define CUHRESPARSER_H

#include <QFile>
#include <QString>



class CuHRESParser
{
    public:
        CuHRESParser();

    public:
        bool parseTransactionFile(const QString&);
};

#endif // CUHRESPARSER_H
