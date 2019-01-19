#ifndef PAYROLLSPECIALISTORM_H
#define PAYROLLSPECIALISTORM_H

#include "payrollspecialist.h"
#include "cunicsdb.h"

class PayrollSpecialistOrm
{
    public:
        PayrollSpecialistOrm();
        static QList<PayrollSpecialist*> find(int id);
    private:
        static CunicsDb &db;
};

#endif // PAYROLLSPECIALISTORM_H
