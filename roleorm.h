#ifndef ROLEORM_H
#define ROLEORM_H

#include "role.h"
#include "cunicsdb.h"
#include <QList>

class RoleOrm
{
    public:
        RoleOrm();
        static QList<Role*> find(const QString&);
        static void update(Role*);

    private:
        static CunicsDb &db;
        static void roleToParams(Role *, QHash<QString, QVariant> &);
};

#endif // ROLEORM_H
