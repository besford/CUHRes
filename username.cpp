/*
 * Class:       UserName
 * Purpose:     Entity object responsible for modelling a User's name.
 */

#include "username.h"

UserName::UserName()
{
    this->fName = "n/a";
    this->lName = "n/a";
}

UserName::UserName(const QString& fName, const QString& lName)
{
    this->fName = fName;
    this->lName = lName;
}

const QString& UserName::getFName()  const
{ return this->fName; }

const QString& UserName::getLName() const
{ return this->lName; }

void UserName::setFName(const QString& fName) {
    this->fName = fName;
}

void UserName::setLName(const QString& lName) {
    this->lName = lName;
}
