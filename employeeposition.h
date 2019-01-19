#ifndef EMPLOYEEPOSITION_H
#define EMPLOYEEPOSITION_H

#include "workterm.h"
#include <QString>

class EmployeePosition
{
    public:
        EmployeePosition(const QString&, const QString&, const WorkTerm&, double, int, double leavePercentage);

    public:
        const QString& getRole() const;
        const QString& getType() const;
        const WorkTerm& getTerm() const;
        double getWage() const;
        int getHours() const;
        void setRole(const QString&);
        void setType(const QString&);
        void setTerm(const WorkTerm&);
        void setWage(double);
        void setHours(int);
        double calcSalary() const;

    private:
        QString role, type;
        WorkTerm    term;
        double      wage;
        int         hours;
        double      leavePercentage;
};

#endif // EMPLOYEEPOSITION_H
