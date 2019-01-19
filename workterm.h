#ifndef WORKTERM_H
#define WORKTERM_H

#include <QString>

class WorkTerm
{
    public:
        WorkTerm();
        WorkTerm(const QString&, const QString&);

    public:
        const QString& getSDate() const;
        const QString& getEDate() const;
        void         setSDate(const QString&);
        void         setEDate(const QString&);

    private:
        QString sDate;
        QString eDate;

};

#endif // WORKTERM_H
