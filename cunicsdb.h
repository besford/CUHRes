#ifndef CUNICSDB_H
#define CUNICSDB_H

#include <QtSql>
#include <QHash>

class CunicsDb
{
    public:
        static CunicsDb& db();
        QSqlError initDb();
        QSqlQuery request(const QString&, const QString& = "");
        bool updateResource(const QString&, const QString&, QHash<QString, QVariant> const&);
        bool addResource(QSqlQuery&, const QString&, const QString&, const QHash<QString, QVariant>&);
        bool deleteResource(const QString&, const QString&);
        // Empty definition to prevent instantiating singleton
        CunicsDb(CunicsDb const&);
        void operator=(CunicsDb const&);

    private:
        CunicsDb();
        QSqlError buildDb(QSqlDatabase const&);
        QString sqlQuery(const QString&, const QString&, QList<QString> const&);
        QString sqlDeleteQuery(const QString&, const QString&);
        QString paramsToString(QList<QString> const&, const QString& = "");
        bool execQueryHash(QSqlQuery&, QHash<QString, QVariant> const&);
        bool execUpdateQueryHash(QSqlQuery&, QHash<QString, QVariant> const&);
        QString sqlUpdateQuery(const QString&, const QString&, QList<QString> const&);
        QString updateParamsToString(QList<QString> const&, const QString& = "");
};

#endif // CUNICSDB_H
