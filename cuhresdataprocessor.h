#ifndef CUHRESDATAPROCESSOR
#define CUHRESDATAPROCESSOR

#include <QJsonDocument>

class CuhresDataProcessor
{
    public:
        CuhresDataProcessor();
        static bool processData(QJsonDocument doc);
};


#endif // CUHRESDATAPROCESSOR

