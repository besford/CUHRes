/*
 * Class:       User
 * Purpose:     Entity object used for modeling users of the CuNICS system.
 */

#include "user.h"

User::User()
{
    this->uID = 0;
    this->name = UserName();
}

User::User(int uID, const UserName &name, const QString &type)
{
    this->uID = uID;
    this->name = name;
    this->type = type;
}

User::User(int uID, const QString& fName, const QString& lName, const QString &type)
{
    this->uID = uID;
    this->name = UserName(fName, lName);
    this->type = type;
}

User::User(QHash<QString, QVariant> const& params) {
    this->uID = params["user_id"].toInt();
    this->name = UserName(params["fname"].toString(), params["lname"].toString());
}

User::~User(){}

int User::getUID() const
{ return this->uID; }

const UserName& User::getName() const
{ return this->name; }

QString User::getType()
{ return this->type; }

void User::setUID(int uID)
{ this->uID = uID; }


void User::setName(const UserName& name)
{ this->name = name; }
