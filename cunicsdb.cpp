#include "cunicsdb.h"
#include "cuhresparser.h"

CunicsDb::CunicsDb()
{

}

QSqlQuery CunicsDb::request(const QString& resource, const QString& constraint)
{
    QSqlQuery q;

    QString queryString = "select * from " + resource;
    if (!constraint.isEmpty())
        queryString += " where " + constraint;

    q.prepare(queryString);
    q.exec();

    return q;
}

QSqlError CunicsDb::initDb()
{
    QDir currentDir;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(currentDir.currentPath() + "_cunics.db");
    if (!db.open())
            return db.lastError();

    QStringList tables = db.tables();
    if (tables.isEmpty()) {
        QSqlError buildErrors = buildDb(db);
        CuHRESParser parser;
        parser.parseTransactionFile(":/transactions/init.cunics");
        return buildErrors;
    }

    return db.lastError();
}

QSqlError CunicsDb::buildDb(const QSqlDatabase& db)
{
    QSqlQuery q;

    if (!q.exec(QLatin1String("DROP TABLE IF EXISTS \"users\";")))
        return q.lastError();
    if (!q.exec(QLatin1String("DROP TABLE IF EXISTS \"payroll_specialists\";")))
        return q.lastError();
    if (!q.exec(QLatin1String("DROP TABLE IF EXISTS \"employees\";")))
        return q.lastError();
    if (!q.exec(QLatin1String("DROP TABLE IF EXISTS \"roles\";")))
        return q.lastError();
    if (!q.exec(QLatin1String("DROP TABLE IF EXISTS \"employee_roles\";")))
        return q.lastError();

    if (!q.exec(QLatin1String("CREATE TABLE \"users\" (\"id\" integer PRIMARY KEY AUTOINCREMENT NOT NULL, \"type\" varchar NOT NULL, \"type_id\" integer NOT NULL);")))
        return q.lastError();
    if (!q.exec(QLatin1String("CREATE TABLE \"payroll_specialists\" (\"id\" integer PRIMARY KEY AUTOINCREMENT NOT NULL);")))
        return q.lastError();
    if (!q.exec(QLatin1String("CREATE TABLE \"employees\" (\"id\" integer PRIMARY KEY AUTOINCREMENT NOT NULL, \"fname\" varchar NOT NULL, \"lname\" varchar NOT NULL, \"start_leave\" text, \"end_leave\" text, \"leave_percentage\" double default 100);")))
        return q.lastError();
    if (!q.exec(QLatin1String("CREATE TABLE \"roles\" (\"id\" varchar PRIMARY KEY NOT NULL, \"wage\" double);")))
        return q.lastError();
    if (!q.exec(QLatin1String("CREATE TABLE \"employee_roles\" (\"employee_id\" varchar NOT NULL, \"role_id\" integer NOT NULL, \"hours\" integer NOT NULL, \"employment_type\" varchar NOT NULL, \"start_term\" text, \"end_term\" text, PRIMARY KEY(\"employee_id\", \"role_id\"));")))
        return q.lastError();

    // Build DB records in memory
    // Payroll specialists
    QHash<QString, QVariant> hash;
    hash["type"] = "payroll_specialist";
    hash["type_id"] = "1";
    if (!addResource(q, "insert into", "users", hash))
        return q.lastError();

    hash.clear();
    if (!addResource(q, "insert into", "payroll_specialists", hash))
        return q.lastError();

    // input roles
    hash.clear();
    hash["wage"] = "20";
    hash["id"] = "TA";
    if(!addResource(q, "insert into", "roles", hash))
        return q.lastError();

    hash.clear();
    hash["wage"] = "30";
    hash["id"] = "RA";
    if(!addResource(q, "insert into", "roles", hash))
        return q.lastError();

    hash.clear();
    hash["wage"] = "45";
    hash["id"] = "Faculty";
    if(!addResource(q, "insert into", "roles", hash))
        return q.lastError();

    hash.clear();
    hash["wage"] = "15";
    hash["id"] = "Staff";
    if(!addResource(q, "insert into", "roles", hash))
        return q.lastError();

    return db.lastError();
}

bool CunicsDb::addResource(QSqlQuery& q, const QString& type, const QString& table, const QHash<QString, QVariant>& hash)
{
    if (!q.prepare(sqlQuery(type, table, hash.keys())))
        return false;
    if (!execQueryHash(q, hash))
        return false;

    return true;
}

QString CunicsDb::sqlQuery(const QString& type, const QString& table, const QList<QString>& keys)
{
    QString output = "";
    output.append(type).append(" ").append(table);
    if (keys.isEmpty()) {
        output.append(" default values");
        return output;
    }

    output.append(paramsToString(keys));
    output.append(" values").append(paramsToString(keys, ":"));

    return output;
}

QString CunicsDb::paramsToString(const QList<QString>& keys, const QString& modifier)
{
    QString output = "";

    output.append("(");
    for (QList<QString>::const_iterator e = keys.begin(); e != keys.end(); e++) {
        output.append(modifier).append(*e);
        if (keys.end() - e != 1)
            output.append(", ");
    }

    output.append(")");
    return output;
}

bool CunicsDb::execQueryHash(QSqlQuery& q, const QHash<QString, QVariant> &params)
{
    for (QHash<QString, QVariant>::const_iterator e = params.constBegin(); e != params.constEnd(); e++)
        q.bindValue(":" + e.key(), e.value());

    return q.exec();
}

CunicsDb& CunicsDb::db()
{
    static CunicsDb db;
    return db;
}

QString CunicsDb::updateParamsToString(const QList<QString> &keys, const QString &modifier)
{
    QString output = "";
    for (QList<QString>::const_iterator e = keys.begin(); e != keys.end(); e++) {
        output.append(*e).append("=");
        output.append(modifier).append(*e);
        if (keys.end() - e != 1)
            output.append(", ");
    }
    return output;
}
QString CunicsDb::sqlUpdateQuery(const QString& constraint, const QString& table, const QList<QString> &keys)
{
    QString output = "UPDATE ";
    output.append(table).append(" SET ");
    output.append(updateParamsToString(keys, ":"));
    output.append(" WHERE ").append(constraint);

    return output;
}

QString CunicsDb::sqlDeleteQuery(const QString& constraint, const QString& table)
{
    QString output = "DELETE FROM ";
    output.append(table);
    output.append(" WHERE ").append(constraint);

    return output;
}

bool CunicsDb::execUpdateQueryHash(QSqlQuery& q, QHash<QString, QVariant> const &params)
{
    for (QHash<QString, QVariant>::const_iterator e = params.constBegin(); e != params.constEnd(); e++)
        q.bindValue(":" + e.key(), e.value());

    return q.exec();
}

bool CunicsDb::updateResource(const QString& constraint, const QString& table, const QHash<QString, QVariant>& hash)
{
    QSqlQuery q;

    if (!q.prepare(sqlUpdateQuery(constraint, table, hash.keys())))
        return false;
    if (!execUpdateQueryHash(q, hash))
        return false;

    return true;
}

bool CunicsDb::deleteResource(const QString& constraint, const QString& table)
{
    QSqlQuery q;

    if (!q.prepare(sqlDeleteQuery(constraint, table)))
        return false;

    return q.exec();
}
