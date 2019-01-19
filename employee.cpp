/*
 * Class:       Employee
 * Purpose:     Entity object used for modeling employee information.
 *              and employee users.
 */

#include "employee.h"
#include <QDate>

Employee::Employee(int uID, const QString& fname, const QString& lname, const QString& start_leave, const QString& end_leave, double leavePerc)
    : User(uID, fname, lname, "employee")
{
    defaultInit();
    this->start_leave = start_leave;
    this->end_leave = end_leave;
    this->leavePerc = leavePerc;
}


Employee::Employee(int uID, const UserName& name, const QString& start_leave, const QString& end_leave, double leavePerc)
    : User(uID, name, "employee")
{
    defaultInit();
    this->start_leave = start_leave;
    this->end_leave = end_leave;
    this->leavePerc = leavePerc;
}

Employee::Employee(const QHash<QString, QVariant> &params)
    : User(params)
{
    defaultInit();
    if (params.contains("employee_id"))
        this->uID = params["employee_id"].toInt();
    if (params.contains("start_leave"))
        setStartLeave(params["start_leave"].toString());
    if (params.contains("end_leave"))
        setEndLeave(params["end_leave"].toString());
    if (params.contains("leave_percentage"))
        setLeavePerc(params["leave_percentage"].toDouble());
}

Employee::~Employee()
{
    for (int i = 0; i < this->positions.size(); i++ )
        delete this->positions[i];
}

void Employee::defaultInit()
{
    this->start_leave = QDate::currentDate().toString("yyyy-MM-dd") ;
    this->end_leave = "";
    this->leavePerc = 100;
}

int Employee::getSalary()
{
    int total = 0;

    for (int i = 0; i < this->positions.size(); i++)
        total += positions.at(i)->calcSalary();

    return total;
}

int Employee::getWage()
{
    int wage = 0;

    for (int i = 0; i < this->positions.size(); i++)
        wage += positions.at(i)->getWage();

    return wage;
}

int Employee::getHours()
{
    int hours = 0;
    for (int i = 0; i < this->positions.size(); i++)
        hours += positions.at(i)->getHours();

    return hours;
}

QList<EmployeePosition*>& Employee::getPositions()
{ return this->positions; }

EmployeePosition* Employee::getPositionForRole(QString role)
{
    for(QList<EmployeePosition*>::iterator itr = this->positions.begin(); itr != this->positions.end(); itr++) {
        if ((*itr)->getRole() == role) {
            return *itr;
        }
    }
    return NULL;
}


const QString& Employee::getStartLeave() const
{ return this->start_leave; }

const QString& Employee::getEndLeave() const
{ return this->end_leave; }

double Employee::getLeavePerc() const
{ return this->leavePerc; }

void Employee::setStartLeave(const QString& start_leave)
{ this->start_leave = start_leave; }

void Employee::setEndLeave(const QString& end_leave)
{ this->end_leave = end_leave; }

void Employee::setLeavePerc(double leavePerc)
{ this->leavePerc = leavePerc; }
