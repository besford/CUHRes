/*
 * Class:       EmployeeControl
 * Purpose:     Control object for performing operations on employeedata.
 */

#include "employeecontrol.h"
#include "employeeorm.h"

EmployeeControl::EmployeeControl()
{
}

/*
 * Function:     addEmployee
 * Purpose:      Adds an empoyee object to the db.
 *
 * in:           QHash<QString, QVariant>& params, hashed data for employee to be added
 *               to the db.
 *
 * return:       Pointer to a newly created employee object.
 */
Employee* EmployeeControl::addEmployee(const QHash<QString, QVariant>& params)
{
    // build employee from params
    Employee* emp = new Employee(params);

    // persist employee
    int id = EmployeeOrm::add(emp);

    // return newly created employee
    delete emp;

    return EmployeeOrm::find(id).first();
}

/*
 * Function:     updateEmployee
 * Purpose:      Updates a designated employee in the db.
 *
 * in:           int id, id number for employee to be updated.
 * in:           QHash<QString, QVariant>& params, hash data for employee to be updated
 *               in the db.
 *
 * return:       Pointer to updated employee object.
 */
Employee* EmployeeControl::updateEmployee(int id, const QHash<QString, QVariant>& params)
{
    // get employee
    QList<Employee*> list = EmployeeOrm::find(id);
    Employee* emp = list.first();

    // assign params to employee
    paramsToEmployee(emp, params);

    // update employee
    EmployeeOrm::update(emp);

    // return employee
    delete emp;

    return EmployeeOrm::find(id).first();
}

/*
 * Function:     destroyRole
 * Purpose:      Removes a designated role from a designated employee.
 *
 * in:           int id, id number of employee whos role is to be removed.
 * in:           QString& role, the role to be removed.
 *
 * return:       Pointer to a newly created employee object.
 */
Employee* EmployeeControl::destroyRole(int id, const QString& role)
{
    // get employee
    QList<Employee*> list = EmployeeOrm::find(id);
    Employee* emp = list.first();

    // destroy role
    EmployeeOrm::destroyRole(emp, role);

    // return employee
    delete emp;

    return EmployeeOrm::find(id).first();;
}

/*
 * Function:     paramsToEmployee
 * Purpose:      Builds an employee object using hashed employee data
 *
 * out:          Employee* emp, pointer to employee to be created
 * in:           QHash<QString, QVariant>& params, hashed data for employee to
 *               be built.
 */
void EmployeeControl::paramsToEmployee(Employee* emp, const QHash<QString, QVariant>& params)
{
    if (params.contains("fname") || params.contains("lname")) {
        QString fname = params["fname"].toString();
        QString lname = params["lname"].toString();

        if (fname.isEmpty()) fname = emp->getName().getFName();
        if (lname.isEmpty()) lname = emp->getName().getLName();
        emp->setName(UserName(fname, lname));
    }

    QString role = params["role"].toString();

    // create new position if it doesn't currently exist
    EmployeePosition* position = emp->getPositionForRole(role);
    if (!position) {
        position = new EmployeePosition(role, "", WorkTerm("", ""), 0.0, 0, emp->getLeavePerc());
        emp->getPositions().append(position);
    }

    /*Initializes hours*/
    if (params.contains("hours"))
        position->setHours(params["hours"].toInt());

    /*Initalize workterm*/
    if (params.contains("start_term") && params.contains("end_term")) {
        QString startTerm = params["start_term"].toString();
        QString endTerm = params["end_term"].toString();
        position->setTerm(WorkTerm(startTerm, endTerm));
    }

    /*Initialize leave data*/
    if (params.contains("start_leave")) {
        emp->setStartLeave(params["start_leave"].toString());
    }
    if (params.contains("end_leave")) {
        emp->setEndLeave(params["end_leave"].toString());
    }
    if (params.contains("leave_percentage")) {
        emp->setLeavePerc(params["leave_percentage"].toDouble());
    }

    /* Initialize position type */
    if (params.contains("type")) {
        position->setType(params["type"].toString());
    }
}
