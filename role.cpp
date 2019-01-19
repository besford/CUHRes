/*
 * Class:       Role
 * Purpose:     Entity object used for modeling employee role.
 */

#include "role.h"

Role::Role(QString id, double wage)
{
    this->id = id;
    this->wage = wage;
}

QString Role::getID() const
{ return this->id; }

double Role::getWage() const
{ return this->wage; }

void Role::setWage(double wage)
{ this->wage = wage; }
