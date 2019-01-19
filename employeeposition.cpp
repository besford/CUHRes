#include "employeeposition.h"

EmployeePosition::EmployeePosition(const QString& role, const QString& type, const WorkTerm& term, double wage, int hours, double leavePercentage)
{
    this->role = role;
    this->type = type;
    this->term = term;
    this->wage = wage;
    this->hours = hours;
    this->leavePercentage = leavePercentage;
}

void EmployeePosition::setType(const QString& type)
{ this->type = type; }

void EmployeePosition::setTerm(const WorkTerm& term)
{ this->term = term; }

void EmployeePosition::setWage(double wage)
{ this->wage = wage; }

void EmployeePosition::setHours(int hours)
{ this->hours = hours; }

const QString& EmployeePosition::getRole() const
{ return this->role; }

const QString& EmployeePosition::getType() const
{ return this->type; }

const WorkTerm& EmployeePosition::getTerm() const
{ return this->term; }

double EmployeePosition::getWage() const
{ return this->wage  * (leavePercentage / 100.0); }

int EmployeePosition::getHours() const
{ return this->hours; }

double EmployeePosition::calcSalary() const
{ return this->hours * getWage(); }
