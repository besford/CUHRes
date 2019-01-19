/*
 * Class:       PayrollSpecialistOrm
 * Purpose:     Responsible for building PayrollSpecialist objects from information
 *              stored in db.
 */

#include "payrollspecialistorm.h"

CunicsDb& PayrollSpecialistOrm::db = CunicsDb::db();

PayrollSpecialistOrm::PayrollSpecialistOrm()
{

}

/*
 * Function:     find
 * Purpose:      retreives a PayrollSpecialist from the db with a designed userId.
 *
 * in:           int id, the id number of the desired PayrollSpecialist.
 *
 * return:       a pointer to the PayrollSpecialist.
 */
QList<PayrollSpecialist*> PayrollSpecialistOrm::find(int id)
{
    QList<PayrollSpecialist*> ps;

    /*Request PayrollSpecialist information from db*/
    QSqlQuery query = db.request("payroll_specialists", "id = " + QString::number(id));

    /*Build PayrollSpecialist object*/
    while (query.next())
        ps.append(new PayrollSpecialist());

    /*Return PayrollSpecialist object*/
    return ps;
}
