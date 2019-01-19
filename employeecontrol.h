#ifndef EMPLOYEECONTROL_H
#define EMPLOYEECONTROL_H

#include "employee.h"

class EmployeeControl
{
    public:
        EmployeeControl();
        static Employee* updateEmployee(int, const QHash<QString, QVariant>&);
        static Employee* addEmployee(const QHash<QString, QVariant>&);
        static Employee* destroyRole(int, const QString&);

    private:
        static void paramsToEmployee(Employee*, const QHash<QString, QVariant> &);
};

#endif // EMPLOYEECONTROL_H
