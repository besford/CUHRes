#include "employeeorm.h"

CunicsDb& EmployeeOrm::db = CunicsDb::db();

EmployeeOrm::EmployeeOrm()
{

}

/*
 * Function:     all
 * Purpose:      retreives list of all employees from the db
 *
 * return:       QList of employee pointers to all employee objects
 */
QList<Employee*> EmployeeOrm::all()
{
    QList<Employee*> employees;

    /*Query db for employee table*/
    QSqlQuery query = db.request("employees");

    /*Build list of employees*/
    while (query.next())
        employees.append(buildFromQuery(query));

    /*Return list of pointers to employee objects*/
    return employees;
}

/*
 * Function:     filter
 * Purpose:      retreives list of all employees from the db that satisfy a filter
 *
 * in:           QString& filter, a string through which to filter the build of the employee list
 *
 * return:       QList of employee pointers for all employee objects that satisfy the filter.
 */
QList<Employee*> EmployeeOrm::filter(const QString& filter)
{
    QList<Employee*> employees;

    /*Query db for employees that satisfy filter*/
    QSqlQuery query = db.request("employees", filter);

    /*Build list of employees*/
    while (query.next())
        employees.append(buildFromQuery(query));

    /*Return list of pointers to employee objects*/
    return employees;
}

/*
 * Function:     find
 * Purpose:      retreives an employee from the db with a designated employee id
 *
 * in:           int id, the employee id of the desired employee
 *
 * return:       pointer to an employee object with the matching id
 */
QList<Employee*> EmployeeOrm::find(int id)
{
    QList<Employee*> employee;

    /*Query db for employee with id*/
    QSqlQuery query = db.request("employees", "id = " + QString::number(id));

    /*Build employee*/
    while (query.next())
        employee.append(buildFromQuery(query));

    /*Return pointer to employee*/
    return employee;
}

/*
 * Function:     buildFromQuery
 * Purpose:      builds an employee object from an QSqlQuery
 *
 * in:           QSqlQuery& query, Query from which to build an employee object
 *
 * return:       pointer to an employee object built from query
 */
Employee* EmployeeOrm::buildFromQuery(const QSqlQuery& query)
{
     QHash<QString, QVariant> params;

     /*Get employee column indexes*/
     int uidIndex = query.record().indexOf("id");
     int fnameIndex = query.record().indexOf("fname");
     int lnameIndex = query.record().indexOf("lname");
     int leveStartIndex = query.record().indexOf("start_leave");
     int leaveEndIndex = query.record().indexOf("end_leave");
     int leavePercIndex = query.record().indexOf("leave_percentage");

     /*Initalized employee params*/
     params["employee_id"] = query.value(uidIndex);
     params["fname"] = query.value(fnameIndex);
     params["lname"] = query.value(lnameIndex);
     params["start_leave"] = query.value(leveStartIndex);
     params["end_leave"] = query.value(leaveEndIndex);
     params["leave_percentage"] = query.value(leavePercIndex);

     /*Build employee*/
     Employee *employee = new Employee(params);
     buildEmployeePositions(*employee, employee->getPositions());

     /*Return employee*/
     return employee;
 }

/*
 * Function:     buildEmployeePositions
 * Purpose:      builds the roles for a given employee
 *
 * in:           Employee& employee, the employee to build the roles for
 * in:           QList<EmployeePosition*>& employeePositions, the list of employee roles to be built
 */
void EmployeeOrm::buildEmployeePositions(Employee& employee, QList<EmployeePosition*>& employeePositions)
{
    /*Query db for all roles for an employee*/
    QSqlQuery employeeRolesQuery = db.request("employee_roles", "employee_id = " + QString::number(employee.getUID()));

    /*Get column indices for employee_roles*/
    int roleIdIndex = employeeRolesQuery.record().indexOf("role_id");
    int hoursIndex = employeeRolesQuery.record().indexOf("hours");
    int employmentTypeIndex = employeeRolesQuery.record().indexOf("employment_type");
    int startTimeIndex = employeeRolesQuery.record().indexOf("start_term");
    int endTimeIndex = employeeRolesQuery.record().indexOf("end_term");

    /*Build all the roles for the employee*/
    while (employeeRolesQuery.next()) {
        //Initialize params for role
        QString role = employeeRolesQuery.value(roleIdIndex).toString();
        int hours = employeeRolesQuery.value(hoursIndex).toInt();
        QString employmentType = employeeRolesQuery.value(employmentTypeIndex).toString();
        QString startTime = employeeRolesQuery.value(startTimeIndex).toString();
        QString endTime = employeeRolesQuery.value(endTimeIndex).toString();

        //Build work term
        WorkTerm workTerm(startTime, endTime);

        //Query db for role information
        QSqlQuery roleQuery = db.request("roles", "id = '" + role + "'");
        int wageIndex = roleQuery.record().indexOf("wage");
        roleQuery.first();
        double wage = roleQuery.value(wageIndex).toDouble();

        //Build position object and add to employee's roles list
        EmployeePosition *position = new EmployeePosition(role, employmentType, workTerm, wage, hours, employee.getLeavePerc());
        employeePositions.append(position);
    }
}

/*
 * Function:     employeeToParams
 * Purpose:      Stores a given employee's attributes in a provided params hash
 *
 * in:           Empoyee *e, a pointer to the employee from which to retreive the attributes
 * in:           QHash<QString, QVariant> &params, the hash to contain the employee attributes
 */
void EmployeeOrm::employeeToParams(const Employee *e, QHash<QString, QVariant> &params)
{
    const UserName &name = e->getName();
    params["fname"] = QVariant(name.getFName());
    params["lname"] = QVariant(name.getLName());
    params["start_leave"] = QVariant(e->getStartLeave());
    params["end_leave"] = QVariant(e->getEndLeave());
    params["leave_percentage"] = QVariant(e->getLeavePerc());
}

/*
 * Function:     employeePositionToParams
 * Purpose:      Stores a given employee position's attributes in a provided params hash
 *
 * in:           EmployeePosition *position, a pointer to the position from which to retreive the attributes
 * in:           QHash<QString, QVariant> &params, the hash to contain the employee position's attributes
 */
void EmployeeOrm::employeePositionToParams(EmployeePosition *position, QHash<QString, QVariant> &params)
{
    params["hours"] = QVariant(position->getHours());
    params["employment_type"] = QVariant(position->getType());
    const WorkTerm &term = position->getTerm();
    params["start_term"] = QVariant(term.getSDate());
    params["end_term"] = QVariant(term.getEDate());
}

/*
 * Function:     destroyRole
 * Purpose:      destroys a given employee's given role.
 *
 * in:           Employee* employee, the employee for which the role is to be destroyed
 * in:           QString& role, to be deleted from a given employee
 */
void EmployeeOrm::destroyRole(Employee *employee, const QString& role)
{
    /*return if no role exists*/
    if (!employee->getPositionForRole(role))
        return;

    /*Create constraint for role deletion from db*/
    QString roleConstraint = "";
    roleConstraint.append("employee_id = ")
            .append(QString::number((employee->getUID())))
            .append(" AND role_id = '")
            .append(role)
            .append("'");

    /*Query db to delete role*/
    db.deleteResource(roleConstraint, "employee_roles");
}

/*
 * Function:     add
 * Purpose:      add's a given employee to the db
 *
 * in:           Employee* employee, a pointer to the employee to add to db
 *
 * return:       employee id of the added employee
 */
int EmployeeOrm::add(Employee* employee)
{
    /*Hash employee attributes*/
    QHash<QString, QVariant> params;
    employeeToParams(employee, params);

    /*Query db to add employee*/
    QSqlQuery q;
    db.addResource(q, "insert into", "employees", params);
    int employeeId = q.lastInsertId().toInt();

    /* add an associated user record */
    QHash<QString, QVariant> userParams;
    userParams["type"] = "employee";
    userParams["type_id"] = employeeId;
    db.addResource(q, "insert into", "users", userParams);

    /*Return id of added employee*/
    return employeeId;
}

/*
 * Function:     update
 * Purpose:      update's a given employee's imformation in the db
 *
 * in:           Employee* employee, a pointer to the employee to add to db
 */
void EmployeeOrm::update(Employee *employee)
{
    /*Hash employee attributes*/
    QHash<QString, QVariant> params;
    employeeToParams(employee, params);

    /*query db to update employee*/
    QString employeeConstraint = "id = " + QString::number(employee->getUID());
    db.updateResource(employeeConstraint, "employees", params);

    /*Update employee's positions in the db*/
    QList<EmployeePosition*> &positions = employee->getPositions();
    for (QList<EmployeePosition*>::iterator itr = positions.begin(); itr != positions.end(); itr++) {
        /*Hash position*/
        QHash<QString, QVariant> positionParams;
        employeePositionToParams(*itr, positionParams);

        /*if position exists, query for update, else query for add*/
        if (positionExists(employee->getUID(), (*itr)->getRole())) {
            QString key = "";
            key.append("employee_id = ")
                    .append(QString::number((employee->getUID())))
                    .append(" AND role_id = '")
                    .append((*itr)->getRole())
                    .append("'");
            db.updateResource(key, "employee_roles", positionParams);
        } else {
            QSqlQuery q;
            positionParams["employee_id"] = QString::number(employee->getUID());
            positionParams["role_id"] = (*itr)->getRole();
            db.addResource(q, "insert into", "employee_roles", positionParams);
            qWarning() << q.lastError().text();
        }
    }
}

/*
 * Function:     positionExists
 * Purpose:      determines whether an employee posesses a given role
 *
 * in:           int employeeId, the employeeId of the employee being evaluate
 * in:           QString& roleId, the id associated with the role to be evaluated
 *
 * return:       true if position roleId associated with employeeId,
 * return:       false otherwise
 */
bool EmployeeOrm::positionExists(int employeeId, const QString& roleId)
{
    /*Query db for position*/
    QString key = "";
    key.append("employee_id = ")
            .append(QString::number(employeeId))
            .append(" AND role_id = '")
            .append(roleId)
            .append("'");
    QSqlQuery employeeRolesQuery = db.request("employee_roles", key);

    /*Return result of query*/
    return employeeRolesQuery.first();
}
