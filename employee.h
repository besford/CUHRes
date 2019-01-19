#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "user.h"
#include "employeeposition.h"
#include "username.h"

#include <QString>

class Employee
        : public User
{
    public:
        Employee(int, const QString&, const QString&, const QString&, const QString&, double);
        Employee(int, const UserName&, const QString&, const QString&, double);
        Employee(const QHash<QString, QVariant>& params);
        ~Employee();
  
    public:
        int getWage();
        int getSalary();
        int getHours();
        double getLeavePerc() const;
        const QString& getStartLeave() const;
        const QString& getEndLeave() const;
        QList<EmployeePosition*>& getPositions();
        EmployeePosition* getPositionForRole(QString);
        void setStartLeave(const QString&);
        void setEndLeave(const QString&);
        void setLeavePerc(double);

    private:
        void defaultInit();
        QList<EmployeePosition*> positions;
        QString start_leave;
        QString end_leave;
        double leavePerc;
};

#endif // EMPLOYEE_H
