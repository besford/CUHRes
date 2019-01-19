#include "cuhresdataprocessor.h"
#include "applyraisescontrol.h"
#include "employeecontrol.h"
#include <QJsonObject>
#include <QJsonValue>


CuhresDataProcessor::CuhresDataProcessor()
{

}

bool CuhresDataProcessor::processData(QJsonDocument doc)
{
    QJsonObject obj = doc.object();
    QJsonValue value = obj.value("action");

    std::string val = value.toString().toStdString();

    if(val.compare("ApplyRaise") == 0)
    {
        bool hasId = obj.contains("id");
        bool hasAmount = obj.contains("amount");
        bool hasIsPercentage = obj.contains("isPercentage");

        if(hasId && hasAmount && hasIsPercentage)
        {
            QJsonValue id = obj.value("id");
            QJsonValue amount = obj.value("amount");
            QJsonValue isPercentage = obj.value("isPercentage");
            ApplyRaisesControl control;
            control.applyRaise(id.toString(), amount.toDouble(), isPercentage.toBool());
            return true;
        }
        return false;
    }

    else if (val.compare("AddEmployee") == 0)
    {
        bool hasFName = obj.contains("fname");
        bool hasLName = obj.contains("lname");

        if (!hasFName || !hasLName)
            return false;

        QHash<QString, QVariant> hash;
        hash["fname"] = obj.value("fname").toString();
        hash["lname"] = obj.value("lname").toString();

        if (obj.contains("start_leave")) {
            hash["start_leave"] = obj.value("start_leave").toString();
        }
        if (obj.contains("end_leave")) {
            hash["end_leave"] = obj.value("end_leave").toString();
        }
        if (obj.contains("leave_percentage")) {
            hash["leave_percentage"] = obj.value("leave_percentage").toDouble();
        }

        Employee* emp = EmployeeControl::addEmployee(hash);

        delete emp;

        return true;
    }
    else if (val.compare("UpdateEmployee") == 0)
    {
        bool hasId = obj.contains("id");
        bool hasRole = obj.contains("role");
        QHash<QString, QVariant> hash;

        if(hasId)
        {
            QJsonValue id = obj.value("id");
            hash.insert("user_id", id.toInt());
            if(obj.contains("fname"))
            {
                QJsonValue fname = obj.value("fname");
                hash.insert("fname", fname.toString());
            }
            if(obj.contains("lname"))
            {
                QJsonValue lname = obj.value("lname");
                hash.insert("lname", lname.toString());
            }
            if(obj.contains("start_leave"))
            {
                QJsonValue start_leave = obj.value("start_leave");
                hash.insert("start_leave", start_leave.toString());
            }
            if(obj.contains("end_leave"))
            {
                QJsonValue end_leave = obj.value("end_leave");
                hash.insert("end_leave", end_leave.toString());
            }
            if (obj.contains("leave_percentage")) {
                hash["leave_percentage"] = obj.value("leave_percentage").toDouble();
            }
            if(hasRole)
            {
                QJsonValue role = obj.value("role");
                hash.insert(("role"), role.toString());

                if(obj.contains("hours"))
                {
                    QJsonValue hours = obj.value("hours");
                    hash.insert("hours", hours.toInt());
                }
                if(obj.contains("start_term"))
                {
                    QJsonValue start_term = obj.value("start_term");
                    hash.insert(("start_term"), start_term.toString());
                }
                if(obj.contains("end_term"))
                {
                    QJsonValue end_term = obj.value("end_term");
                    hash.insert(("end_term"), end_term.toString());
                }
                if(obj.contains("type"))
                {
                    QJsonValue type = obj.value("type");
                    hash.insert("type", type.toString());
                }
            }
            Employee* emp = EmployeeControl::updateEmployee(id.toInt(), hash);

            delete emp;

            return true;
        }

    return false;
    }

    else if (val.compare("DestroyRole") == 0)
    {
        QJsonValue id = obj.value("id");
        QJsonValue role = obj.value("role");

        Employee* emp  = EmployeeControl::destroyRole(id.toInt(), role.toString());

        delete emp;

        return true;
    }

    return false;
}
