#ifndef EMPLOYEEORM_H
#define EMPLOYEEORM_H

#include "employee.h"
#include "cunicsdb.h"

class EmployeeOrm
{
    public:
        EmployeeOrm();
        static QList<Employee*> all();
        static QList<Employee*> find(int id);
        static QList<Employee*> filter(const QString&);
        static int add(Employee*);
        static void update(Employee*);
        static void destroyRole(Employee*, const QString&);

    private:
        static Employee* buildFromQuery(const QSqlQuery&);
        static void buildEmployeePositions(Employee&, QList<EmployeePosition*>&);
        static void employeeToParams(const Employee *, QHash<QString, QVariant> &);
        static void employeePositionToParams(EmployeePosition *, QHash<QString, QVariant> &);
        static bool positionExists(int , const QString&);
        static CunicsDb &db;
};

#endif // EMPLOYEEORM_H
