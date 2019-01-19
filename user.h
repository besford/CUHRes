#ifndef USER_H
#define USER_H

#include "username.h"
#include <QString>
#include <QHash>
#include <QVariant>

class User
{
    public:
        User();
        User(int, const UserName& name, const QString&);
        User(const int, const QString&, const QString&, const QString&);
        User(QHash<QString, QVariant> const&);
        virtual ~User() = 0;
        virtual int getUID() const;
        virtual const UserName& getName() const;
        virtual void setUID(int);
        virtual void setName(const UserName&);
        virtual QString getType();

    protected:
        int      uID;
        UserName name;
        QString  type;
};

#endif // USER_H
