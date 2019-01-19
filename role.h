#ifndef ROLE_H
#define ROLE_H

#include <QString>

class Role
{
    public:
        Role(QString, double);
        QString getID() const;
        double getWage() const;
        void setWage(double);
    private:
        QString id;
        double wage;
};

#endif // ROLE_H
