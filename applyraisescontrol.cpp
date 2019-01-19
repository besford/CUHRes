/*
 * Class:       ApplyRaisesControl
 * Purpose:     Serves as the control object for applying employee raises.
 *
 */

#include "applyraisescontrol.h"
#include "roleorm.h"
#include <QDebug>

ApplyRaisesControl::ApplyRaisesControl()
{

}

/*
 * Function:     ApplyRaises
 * Purpose:      Applies a raise to an employee's role designated
 *               by a provided roleId
 *
 * in:           string roleId, the id of the role to apply the raise to
 * in:           double raiseAmt, the size of the raise to be applied. May be a percentage
 *               or fixed amount.
 * in:           bool isPerc, tells the function whether or not the raiseAmt is a percentage
 *               or a fixed amount.
 *
 * return:       the new wage of the role.
 */
double ApplyRaisesControl::applyRaise(const QString& roleId, double raiseAmt, bool isPerc)
{
    /*Find role designated by roleId in db*/
    Role* role = RoleOrm::find(roleId).first();
    if (!role) {
        qDebug() << "No role " << roleId << " found in the db";
        return 0;
    }

    /*If is percentage apply raise %, else apply fixed rate*/
    if (!isPerc)
        role->setWage(role->getWage() + raiseAmt);
    else
        role->setWage(role->getWage() * (raiseAmt / 100.0));

    /*Apply wage update to db*/
    RoleOrm::update(role);

    double raise = role->getWage();

    delete role;

    return raise;
}
