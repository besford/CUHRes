/*
 * Class:       UsereOrm
 * Purpose:     Responsible for building user objects from information
 *              stored in db.
 */

#include "userorm.h"
#include "employeeorm.h"
#include "payrollspecialistorm.h"

CunicsDb& UserOrm::db = CunicsDb::db();

UserOrm::UserOrm()
{

}

/*
 * Function:     find
 * Purpose:      retreives a user from the db with a designed userId.
 *
 * in:           int id, the id number of the desired user.
 *
 * return:       a pointer to the user.
 */
QList<User*> UserOrm::find(int id)
{
    QList<User*> users;

    /*Request user information from db*/
    QSqlQuery query = db.request("users", "id = " + QString::number(id));
    int typeIndex = query.record().indexOf("type");
    int typeIdIndex = query.record().indexOf("type_id");

    /*Build new user object*/
    if (query.next())
    {
        QString type = query.value(typeIndex).toString();
        int typeId = query.value(typeIdIndex).toInt();

        if (type == "employee")
            users.append(EmployeeOrm::find(typeId)[0]);
        else
            users.append(PayrollSpecialistOrm::find(typeId)[0]);
    }

    /*Return new User object*/
    return users;
}
