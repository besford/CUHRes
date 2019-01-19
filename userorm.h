#ifndef USERORM_H
#define USERORM_H

#include "user.h"
#include "cunicsdb.h"

class UserOrm
{
    public:
        UserOrm();
        static QList<User*> find(int);

    private:
        static CunicsDb &db;
};

#endif // USERORM_H
