/*
 * Class:       RoleOrm
 * Purpose:     Responsible for building role objects from information
 *              stored in db. Also responsible for applying changes
 *              in local role information to the db.
 */

#include "roleorm.h"
#include "cunicsdb.h"

CunicsDb& RoleOrm::db = CunicsDb::db();

RoleOrm::RoleOrm()
{

}

/*
 * Function:     find
 * Purpose:      Retreives a role from the db with a designed role Id.
 *
 * in:           QString id, the id number of the desired role.
 *
 * return:       A pointer to the role.
 */
QList<Role*> RoleOrm::find(const QString& id)
{
    QList<Role*> roles;

    /*Query db for role information*/
    QSqlQuery query = db.request("roles", "id = '" + id + "'");
    int idIndex = query.record().indexOf("id");
    int wageIndex = query.record().indexOf("wage");

    /*Build role object*/
    if (query.next())
    {
        QString id = query.value(idIndex).toString();
        double wage = query.value(wageIndex).toDouble();
        roles.append(new Role(id, wage));
    }

    /*return role object*/
    return roles;
}

void RoleOrm::roleToParams(Role *role, QHash<QString, QVariant> &params)
{
    params["wage"] = QVariant(role->getWage());
}

/*
 * Function:     update
 * Purpose:      updates a given role's representation on the db
 *
 * in:           Role* role, a pointer to the role to be updated.
 */
void RoleOrm::update(Role *role)
{
    QHash<QString, QVariant> params;

    QString id = "";
    id.append("id = '").append(role->getID()).append("'");
    roleToParams(role, params);

    db.updateResource(id, "roles", params);
}
